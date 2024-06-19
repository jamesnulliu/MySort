/**
 * @copyright Copyright (c) 2021 Orson Peters <orsonpeters@gmail.com>
 */

#pragma once
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iterator>
#include <type_traits>
#include <utility>

namespace mysort
{
namespace pdqsort_detail
{
enum
{
    // Partitions below this size are sorted using insertion sort.
    insertion_sort_threshold = 24,

    // Partitions above this size use Tukey's ninther to select the pivot.
    ninther_threshold = 128,

    // When we detect an already sorted partition, attempt an insertion sort that allows this
    // amount of element moves before giving up.
    partial_insertion_sort_limit = 8,

    // Must be multiple of 8 due to loop unrolling, and < 256 to fit in unsigned char.
    block_size = 64,

    // Cacheline size, assumes power of two.
    cacheline_size = 64
};

template <class T>
struct is_default_compare : std::false_type
{
};
template <class T>
struct is_default_compare<std::less<T>> : std::true_type
{
};
template <class T>
struct is_default_compare<std::greater<T>> : std::true_type
{
};

// Returns floor(log2(n)), assumes n > 0.
template <class T>
inline int log2(T n)
{
    int log = 0;
    while (n >>= 1)
        ++log;
    return log;
}

// Sorts [begin, end) using insertion sort with the given comparison function.
template <class _It, class _Pr = std::less<>>
inline void insertion_sort(_It begin, _It end, const _Pr& _pred = {})
{
    typedef typename std::iterator_traits<_It>::value_type T;
    if (begin == end)
        return;

    for (_It cur = begin + 1; cur != end; ++cur) {
        _It sift = cur;
        _It sift_1 = cur - 1;

        // Compare first so we can avoid 2 moves for an element already positioned correctly.
        if (_pred(*sift, *sift_1)) {
            T tmp = std::move(*sift);

            do {
                *sift-- = std::move(*sift_1);
            } while (sift != begin && _pred(tmp, *--sift_1));

            *sift = std::move(tmp);
        }
    }
}

// Sorts [begin, end) using insertion sort with the given comparison function. Assumes
// *(begin - 1) is an element smaller than or equal to any element in [begin, end).
template <class _It, class _Pr = std::less<>>
inline void unguarded_insertion_sort(_It begin, _It end, const _Pr& _pred = {})
{
    typedef typename std::iterator_traits<_It>::value_type T;
    if (begin == end)
        return;

    for (_It cur = begin + 1; cur != end; ++cur) {
        _It sift = cur;
        _It sift_1 = cur - 1;

        // Compare first so we can avoid 2 moves for an element already positioned correctly.
        if (_pred(*sift, *sift_1)) {
            T tmp = std::move(*sift);

            do {
                *sift-- = std::move(*sift_1);
            } while (_pred(tmp, *--sift_1));

            *sift = std::move(tmp);
        }
    }
}

// Attempts to use insertion sort on [begin, end). Will return false if more than
// partial_insertion_sort_limit elements were moved, and abort sorting. Otherwise it will
// successfully sort and return true.
template <class _It, class _Pr = std::less<>>
inline bool partial_insertion_sort(_It begin, _It end, const _Pr& _pred = {})
{
    typedef typename std::iterator_traits<_It>::value_type T;
    if (begin == end)
        return true;

    std::size_t limit = 0;
    for (_It cur = begin + 1; cur != end; ++cur) {
        _It sift = cur;
        _It sift_1 = cur - 1;

        // Compare first so we can avoid 2 moves for an element already positioned correctly.
        if (_pred(*sift, *sift_1)) {
            T tmp = std::move(*sift);

            do {
                *sift-- = std::move(*sift_1);
            } while (sift != begin && _pred(tmp, *--sift_1));

            *sift = std::move(tmp);
            limit += cur - sift;
        }

        if (limit > partial_insertion_sort_limit)
            return false;
    }

    return true;
}

template <class _It, class _Pr = std::less<>>
inline void sort2(_It a, _It b, const _Pr& _pred = {})
{
    if (_pred(*b, *a))
        std::iter_swap(a, b);
}

// Sorts the elements *a, *b and *c using comparison function comp.
template <class _It, class _Pr = std::less<>>
inline void sort3(_It a, _It b, _It c, const _Pr& _pred = {})
{
    sort2(a, b, _pred);
    sort2(b, c, _pred);
    sort2(a, b, _pred);
}

template <class T>
T* align_cacheline(T* p)
{
#if defined(UINTPTR_MAX)
    std::uintptr_t ip = reinterpret_cast<std::uintptr_t>(p);
#else
    std::size_t ip = reinterpret_cast<std::size_t>(p);
#endif
    ip = (ip + cacheline_size - 1) & -cacheline_size;
    return reinterpret_cast<T*>(ip);
}

template <class _It>
inline void swap_offsets(_It first, _It last, unsigned char* offsets_l, unsigned char* offsets_r,
                         size_t num, bool use_swaps)
{
    typedef typename std::iterator_traits<_It>::value_type T;
    if (use_swaps) {
        // This case is needed for the descending distribution, where we need
        // to have proper swapping for pdqsort to remain O(n).
        for (size_t i = 0; i < num; ++i) {
            std::iter_swap(first + offsets_l[i], last - offsets_r[i]);
        }
    } else if (num > 0) {
        _It l = first + offsets_l[0];
        _It r = last - offsets_r[0];
        T tmp(std::move(*l));
        *l = std::move(*r);
        for (size_t i = 1; i < num; ++i) {
            l = first + offsets_l[i];
            *r = std::move(*l);
            r = last - offsets_r[i];
            *l = std::move(*r);
        }
        *r = std::move(tmp);
    }
}

// Partitions [begin, end) around pivot *begin using comparison function comp. Elements equal
// to the pivot are put in the right-hand partition. Returns the position of the pivot after
// partitioning and whether the passed sequence already was correctly partitioned. Assumes the
// pivot is a median of at least 3 elements and that [begin, end) is at least
// insertion_sort_threshold long. Uses branchless partitioning.
template <class _It, class _Pr = std::less<>>
inline std::pair<_It, bool> partition_right_branchless(_It begin, _It end, const _Pr& _pred = {})
{
    typedef typename std::iterator_traits<_It>::value_type T;

    // Move pivot into local for speed.
    T pivot(std::move(*begin));
    _It first = begin;
    _It last = end;

    // Find the first element greater than or equal than the pivot (the median of 3 guarantees
    // this exists).
    while (_pred(*++first, pivot))
        ;

    // Find the first element strictly smaller than the pivot. We have to guard this search if
    // there was no element before *first.
    if (first - 1 == begin)
        while (first < last && !_pred(*--last, pivot))
            ;
    else
        while (!_pred(*--last, pivot))
            ;

    // If the first pair of elements that should be swapped to partition are the same element,
    // the passed in sequence already was correctly partitioned.
    bool already_partitioned = first >= last;
    if (!already_partitioned) {
        std::iter_swap(first, last);
        ++first;

        // The following branchless partitioning is derived from "BlockQuicksort: How Branch
        // Mispredictions don’t affect Quicksort" by Stefan Edelkamp and Armin Weiss, but
        // heavily micro-optimized.
        unsigned char offsets_l_storage[block_size + cacheline_size];
        unsigned char offsets_r_storage[block_size + cacheline_size];
        unsigned char* offsets_l = align_cacheline(offsets_l_storage);
        unsigned char* offsets_r = align_cacheline(offsets_r_storage);

        _It offsets_l_base = first;
        _It offsets_r_base = last;
        size_t num_l, num_r, start_l, start_r;
        num_l = num_r = start_l = start_r = 0;

        while (first < last) {
            // Fill up offset blocks with elements that are on the wrong side.
            // First we determine how much elements are considered for each offset block.
            size_t num_unknown = last - first;
            size_t left_split = num_l == 0 ? (num_r == 0 ? num_unknown / 2 : num_unknown) : 0;
            size_t right_split = num_r == 0 ? (num_unknown - left_split) : 0;

            // Fill the offset blocks.
            if (left_split >= block_size) {
                for (size_t i = 0; i < block_size;) {
                    offsets_l[num_l] = i++;
                    num_l += !_pred(*first, pivot);
                    ++first;
                    offsets_l[num_l] = i++;
                    num_l += !_pred(*first, pivot);
                    ++first;
                    offsets_l[num_l] = i++;
                    num_l += !_pred(*first, pivot);
                    ++first;
                    offsets_l[num_l] = i++;
                    num_l += !_pred(*first, pivot);
                    ++first;
                    offsets_l[num_l] = i++;
                    num_l += !_pred(*first, pivot);
                    ++first;
                    offsets_l[num_l] = i++;
                    num_l += !_pred(*first, pivot);
                    ++first;
                    offsets_l[num_l] = i++;
                    num_l += !_pred(*first, pivot);
                    ++first;
                    offsets_l[num_l] = i++;
                    num_l += !_pred(*first, pivot);
                    ++first;
                }
            } else {
                for (size_t i = 0; i < left_split;) {
                    offsets_l[num_l] = i++;
                    num_l += !_pred(*first, pivot);
                    ++first;
                }
            }

            if (right_split >= block_size) {
                for (size_t i = 0; i < block_size;) {
                    offsets_r[num_r] = ++i;
                    num_r += _pred(*--last, pivot);
                    offsets_r[num_r] = ++i;
                    num_r += _pred(*--last, pivot);
                    offsets_r[num_r] = ++i;
                    num_r += _pred(*--last, pivot);
                    offsets_r[num_r] = ++i;
                    num_r += _pred(*--last, pivot);
                    offsets_r[num_r] = ++i;
                    num_r += _pred(*--last, pivot);
                    offsets_r[num_r] = ++i;
                    num_r += _pred(*--last, pivot);
                    offsets_r[num_r] = ++i;
                    num_r += _pred(*--last, pivot);
                    offsets_r[num_r] = ++i;
                    num_r += _pred(*--last, pivot);
                }
            } else {
                for (size_t i = 0; i < right_split;) {
                    offsets_r[num_r] = ++i;
                    num_r += _pred(*--last, pivot);
                }
            }

            // Swap elements and update block sizes and first/last boundaries.
            size_t num = std::min(num_l, num_r);
            swap_offsets(offsets_l_base, offsets_r_base, offsets_l + start_l, offsets_r + start_r,
                         num, num_l == num_r);
            num_l -= num;
            num_r -= num;
            start_l += num;
            start_r += num;

            if (num_l == 0) {
                start_l = 0;
                offsets_l_base = first;
            }

            if (num_r == 0) {
                start_r = 0;
                offsets_r_base = last;
            }
        }

        // We have now fully identified [first, last)'s proper position. Swap the last elements.
        if (num_l) {
            offsets_l += start_l;
            while (num_l--)
                std::iter_swap(offsets_l_base + offsets_l[num_l], --last);
            first = last;
        }
        if (num_r) {
            offsets_r += start_r;
            while (num_r--)
                std::iter_swap(offsets_r_base - offsets_r[num_r], first), ++first;
            last = first;
        }
    }

    // Put the pivot in the right place.
    _It pivot_pos = first - 1;
    *begin = std::move(*pivot_pos);
    *pivot_pos = std::move(pivot);

    return std::make_pair(pivot_pos, already_partitioned);
}

// Partitions [begin, end) around pivot *begin using comparison function comp. Elements equal
// to the pivot are put in the right-hand partition. Returns the position of the pivot after
// partitioning and whether the passed sequence already was correctly partitioned. Assumes the
// pivot is a median of at least 3 elements and that [begin, end) is at least
// insertion_sort_threshold long.
template <class _It, class _Pr = std::less<>>
inline std::pair<_It, bool> partition_right(_It begin, _It end, const _Pr& _pred = {})
{
    typedef typename std::iterator_traits<_It>::value_type T;

    // Move pivot into local for speed.
    T pivot(std::move(*begin));

    _It first = begin;
    _It last = end;

    // Find the first element greater than or equal than the pivot (the median of 3 guarantees
    // this exists).
    while (_pred(*++first, pivot))
        ;

    // Find the first element strictly smaller than the pivot. We have to guard this search if
    // there was no element before *first.
    if (first - 1 == begin)
        while (first < last && !_pred(*--last, pivot))
            ;
    else
        while (!_pred(*--last, pivot))
            ;

    // If the first pair of elements that should be swapped to partition are the same element,
    // the passed in sequence already was correctly partitioned.
    bool already_partitioned = first >= last;

    // Keep swapping pairs of elements that are on the wrong side of the pivot. Previously
    // swapped pairs guard the searches, which is why the first iteration is special-cased
    // above.
    while (first < last) {
        std::iter_swap(first, last);
        while (_pred(*++first, pivot))
            ;
        while (!_pred(*--last, pivot))
            ;
    }

    // Put the pivot in the right place.
    _It pivot_pos = first - 1;
    *begin = std::move(*pivot_pos);
    *pivot_pos = std::move(pivot);

    return std::make_pair(pivot_pos, already_partitioned);
}

// Similar function to the one above, except elements equal to the pivot are put to the left of
// the pivot and it doesn't check or return if the passed sequence already was partitioned.
// Since this is rarely used (the many equal case), and in that case pdqsort already has O(n)
// performance, no block quicksort is applied here for simplicity.
template <class _It, class _Pr = std::less<>>
inline _It partition_left(_It begin, _It end, const _Pr& _pred = {})
{
    typedef typename std::iterator_traits<_It>::value_type T;

    T pivot(std::move(*begin));
    _It first = begin;
    _It last = end;

    while (_pred(pivot, *--last))
        ;

    if (last + 1 == end)
        while (first < last && !_pred(pivot, *++first))
            ;
    else
        while (!_pred(pivot, *++first))
            ;

    while (first < last) {
        std::iter_swap(first, last);
        while (_pred(pivot, *--last))
            ;
        while (!_pred(pivot, *++first))
            ;
    }

    _It pivot_pos = last;
    *begin = std::move(*pivot_pos);
    *pivot_pos = std::move(pivot);

    return pivot_pos;
}

template <class _It, class _Pr = std::less<>, bool Branchless>
inline void pdqSort_loop(_It begin, _It end, const _Pr& _pred = {}, int bad_allowed = 0,
                         bool leftmost = true)
{
    typedef typename std::iterator_traits<_It>::difference_type diff_t;

    // Use a while loop for tail recursion elimination.
    while (true) {
        diff_t size = end - begin;

        // Insertion sort is faster for small arrays.
        if (size < insertion_sort_threshold) {
            if (leftmost)
                insertion_sort(begin, end, _pred);
            else
                unguarded_insertion_sort(begin, end, _pred);
            return;
        }

        // Choose pivot as median of 3 or pseudomedian of 9.
        diff_t s2 = size / 2;
        if (size > ninther_threshold) {
            sort3(begin, begin + s2, end - 1, _pred);
            sort3(begin + 1, begin + (s2 - 1), end - 2, _pred);
            sort3(begin + 2, begin + (s2 + 1), end - 3, _pred);
            sort3(begin + (s2 - 1), begin + s2, begin + (s2 + 1), _pred);
            std::iter_swap(begin, begin + s2);
        } else
            sort3(begin + s2, begin, end - 1, _pred);

        // If *(begin - 1) is the end of the right partition of a previous partition operation
        // there is no element in [begin, end) that is smaller than *(begin - 1). Then if our
        // pivot compares equal to *(begin - 1) we change strategy, putting equal elements in
        // the left partition, greater elements in the right partition. We do not have to
        // recurse on the left partition, since it's sorted (all equal).
        if (!leftmost && !_pred(*(begin - 1), *begin)) {
            begin = partition_left(begin, end, _pred) + 1;
            continue;
        }

        // Partition and get results.
        std::pair<_It, bool> part_result = Branchless
                                               ? partition_right_branchless(begin, end, _pred)
                                               : partition_right(begin, end, _pred);
        _It pivot_pos = part_result.first;
        bool already_partitioned = part_result.second;

        // Check for a highly unbalanced partition.
        diff_t l_size = pivot_pos - begin;
        diff_t r_size = end - (pivot_pos + 1);
        bool highly_unbalanced = l_size < size / 8 || r_size < size / 8;

        // If we got a highly unbalanced partition we shuffle elements to break many patterns.
        if (highly_unbalanced) {
            // If we had too many bad partitions, switch to heapsort to guarantee O(n log n).
            if (--bad_allowed == 0) {
                std::make_heap(begin, end, _pred);
                std::sort_heap(begin, end, _pred);
                return;
            }

            if (l_size >= insertion_sort_threshold) {
                std::iter_swap(begin, begin + l_size / 4);
                std::iter_swap(pivot_pos - 1, pivot_pos - l_size / 4);

                if (l_size > ninther_threshold) {
                    std::iter_swap(begin + 1, begin + (l_size / 4 + 1));
                    std::iter_swap(begin + 2, begin + (l_size / 4 + 2));
                    std::iter_swap(pivot_pos - 2, pivot_pos - (l_size / 4 + 1));
                    std::iter_swap(pivot_pos - 3, pivot_pos - (l_size / 4 + 2));
                }
            }

            if (r_size >= insertion_sort_threshold) {
                std::iter_swap(pivot_pos + 1, pivot_pos + (1 + r_size / 4));
                std::iter_swap(end - 1, end - r_size / 4);

                if (r_size > ninther_threshold) {
                    std::iter_swap(pivot_pos + 2, pivot_pos + (2 + r_size / 4));
                    std::iter_swap(pivot_pos + 3, pivot_pos + (3 + r_size / 4));
                    std::iter_swap(end - 2, end - (1 + r_size / 4));
                    std::iter_swap(end - 3, end - (2 + r_size / 4));
                }
            }
        } else {
            // If we were decently balanced and we tried to sort an already partitioned
            // sequence try to use insertion sort.
            if (already_partitioned && partial_insertion_sort(begin, pivot_pos, _pred) &&
                partial_insertion_sort(pivot_pos + 1, end, _pred))
                return;
        }

        // Sort the left partition first using recursion and do tail recursion elimination for
        // the right-hand partition.
        pdqSort_loop<_It, _Pr, Branchless>(begin, pivot_pos, _pred, bad_allowed, leftmost);
        begin = pivot_pos + 1;
        leftmost = false;
    }
}
}  // namespace pdqsort_detail

template <class _It, class _Pr = std::less<>>
void pdqSort(_It begin, _It end, const _Pr& _pred = {})
{
    if constexpr (!std::random_access_iterator<_It>) {
        YWARNING("Pattern-Defeating Quicksort requires random access iterator. Skip sorting.");
    } else {
        if (begin == end)
            return;

        pdqsort_detail::pdqSort_loop<
            _It, _Pr,
            pdqsort_detail::is_default_compare<typename std::decay<_Pr>::type>::value &&
                std::is_arithmetic<typename std::iterator_traits<_It>::value_type>::value>(
            begin, end, _pred, pdqsort_detail::log2(end - begin));
    }
}

template <class _It, class _Pr = std::less<>>
void pdqSort_branchless(_It begin, _It end, const _Pr& _pred = {})
{
    if constexpr (!std::random_access_iterator<_It>) {
        YWARNING("Pattern-Defeating Quicksort branchless requires random access iterator. Skip "
                 "sorting.");
    } else {
        if (begin == end)
            return;
        pdqsort_detail::pdqSort_loop<_It, _Pr, true>(begin, end, _pred,
                                                     pdqsort_detail::log2(end - begin));
    }
}
}  // namespace mysort