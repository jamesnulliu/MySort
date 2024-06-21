#pragma once
#include <algorithm>
#include <tuple>
#include <utility>

#include "MySort/Core/Concept.hpp"
#include "MySort/Core/InsertionSort.hpp"
#include "MySort/Core/PreDefined.hpp"
#include "MySort/Core/Utilities.hpp"

namespace mysort
{
// TODO:
//   If {_begin} equals {_end} or the next iterator of {_begin} equals {_end},
//   some partition functions may go wrong.
//   Additional control flow is needed.

// =================================================================================================
// Quick Sort with Hoare Partition
// -------------------------------------------------------------------------------------------------
/**
 * @brief  Partition the sequence using Lomuto's partition scheme.
 *         The input iterators must be forward iterators.
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred  Comparison predicate.
 */
template <class _It, class _Pr = std::less<>>
    requires std::forward_iterator<_It>
_It _partition_Lomuto(_It _begin, _It _end, const _Pr& _pred = {})
{
    auto pivot = *_begin;
    _It i = _begin;
    _It j = std::next(_begin);
    for (; j != _end; ++j) {
        if (_pred(*j, pivot)) {
            ++i;
            std::iter_swap(i, j);
        }
    }
    std::iter_swap(i, _begin);
    return i;
}

/**
 * @brief  Quick Sort with Lomuto Partition - O(nlogn).
 *         The input iterators must be forward iterators.
 */
template <class _It, class _Pr = std::less<>>
void quickSort_Lomuto(_It, _It, const _Pr& = {})
{
    YWARNING("Quick Sort (Lomuto) requires forward iterator. Skip sorting.");
}

/**
 * @brief  Quick Sort with Lomuto Partition - O(nlogn).
 *         The input iterators must be forward iterators.
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred  Comparison predicate.
 */
template <class _It, class _Pr = std::less<>>
    requires std::forward_iterator<_It>
void quickSort_Lomuto(_It _begin, _It _end, const _Pr& _pred = {})
{
    if (_begin == _end || std::next(_begin) == _end)
        return;
    _It pivot = _partition_Lomuto(_begin, _end, _pred);
    quickSort_Lomuto(_begin, pivot, _pred);
    quickSort_Lomuto(++pivot, _end, _pred);
}

/**
 * @brief  Quick Sort with Lomuto Partition, Tail Recursive Optimization - O(nlogn).
 *         The input iterators must be forward iterators.
 */
template <class _It, class _Pr = std::less<>>
void quickSort_Lomuto_tailRec(_It, _It, const _Pr& = {})
{
    YWARNING("Quick Sort (Lomuto, Tail Rec) requires forward iterator. Skip sorting.");
}

/**
 * @brief  Quick Sort with Lomuto Partition, Tail Recursive Optimization - O(nlogn).
 *         The input iterators must be forward iterators.
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred  Comparison predicate.
 */
template <class _It, class _Pr = std::less<>>
    requires std::forward_iterator<_It>
void quickSort_Lomuto_tailRec(_It _begin, _It _end, const _Pr& _pred = {})
{
    while (_begin != _end && std::next(_begin) != _end) {
        _It pivot = _partition_Lomuto(_begin, _end, _pred);
        quickSort_Lomuto_tailRec(_begin, pivot, _pred);
        _begin = ++pivot;
    }
}

/**
 * @brief  Partition the sequence using Lomuto's partition scheme and random pivot.
 *         The input iterators must be forward iterators.
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred  Comparison predicate.
 */
template <class _It, class _Pr = std::less<>>
    requires std::forward_iterator<_It>
_It _partition_Lomuto_rand(_It _begin, _It _end, const _Pr& _pred = {})
{
    _It mid = midOfRandom3(_begin, _end, _pred);
    std::iter_swap(_begin, mid);
    return _partition_Lomuto(_begin, _end, _pred);
}

/**
 * @brief  Quick Sort with Lomuto Partition, Random Pivot - O(nlogn).
 *         The input iterators must be forward iterators.
 */
template <class _It, class _Pr = std::less<>>
void quickSort_Lomuto_rand(_It, _It, const _Pr& = {})
{
    YWARNING("Quick Sort (Lomuto, Rand) requires forward iterator. Skip sorting.");
}

/**
 * @brief  Quick Sort with Lomuto Partition, Random Pivot - O(nlogn).
 *         The input iterators must be forward iterators.
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred  Comparison predicate.
 */
template <class _It, class _Pr = std::less<>>
    requires std::forward_iterator<_It>
void quickSort_Lomuto_rand(_It _begin, _It _end, const _Pr& _pred = {})
{
    if (_begin == _end || std::next(_begin) == _end)
        return;
    _It pivot{_partition_Lomuto_rand(_begin, _end, _pred)};
    quickSort_Lomuto_rand(_begin, pivot, _pred);
    quickSort_Lomuto_rand(++pivot, _end, _pred);
}

/**
 * @brief  Partition the sequence using Lomuto's partition scheme, random pivot, and optimized
 *         for contiguous duplicated elements.
 *         The input iterators must be forward iterators.
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred  Must provide a tuple of predicate where the first element is the comparison
 *               predicate and the second element is the equality predicate.
 */
template <class _It, class _Pr = std::tuple<std::less<>, std::equal_to<>>>
    requires std::forward_iterator<_It> && IsTuple<_Pr>
std::pair<_It, _It> _partition_Lomuto_rand_duplicated(_It _begin, _It _end, const _Pr& _pred = {})
{
    auto [comp, equal_to] = _pred;

    _It mid = midOfRandom3(_begin, _end, comp);
    std::iter_swap(_begin, mid);
    auto pivot = *_begin;

    _It eqPrev = _begin;
    _It eqEnd = std::next(_begin);
    _It iter = std::next(_begin);

    for (; iter != _end; ++iter) {
        if (equal_to(*iter, pivot)) {
            std::iter_swap(eqEnd, iter);
            ++eqEnd;
        } else if (comp(*iter, pivot)) {
            std::iter_swap(eqEnd, iter);
            _It eqFirst{std::next(eqPrev)};
            if (eqFirst != eqEnd) {
                std::iter_swap(eqEnd, eqFirst);
            }
            ++eqPrev, ++eqEnd;
        }
    }

    std::iter_swap(_begin, eqPrev);

    return {++eqPrev, eqEnd};
}

/**
 * @brief Quick Sort with Lomuto Partition, Random Pivot, and Optimized for Contiguous Duplicated
 *        Elements - O(nlogn).
 *        The input iterators must be forward iterators.
 */
template <class _It, class _Pr = std::tuple<std::less<>, std::equal_to<>>>
    requires IsTuple<_Pr>
void quickSort_Lomuto_rand_duplicated(_It, _It, const _Pr& = {})
{
    YWARNING("Quick Sort (Lomuto, Rand, Duplicated) requires forward iterator. Skip sorting.");
}

/**
 * @brief  Quick Sort with Lomuto Partition, Random Pivot, and Optimized for Contiguous Duplicated
 *         Elements - O(nlogn).
 *         The input iterators must be forward iterators.
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred  Must provide a tuple of predicate where the first element is the comparison
 *               predicate and the second element is the equality predicate.
 */
template <class _It, class _Pr = std::tuple<std::less<>, std::equal_to<>>>
    requires std::forward_iterator<_It> && IsTuple<_Pr>
void quickSort_Lomuto_rand_duplicated(_It _begin, _It _end, const _Pr& _pred = {})
{
    if (_begin == _end || std::next(_begin) == _end)
        return;

    auto [eqBegin, eqEnd] = _partition_Lomuto_rand_duplicated(_begin, _end, _pred);
    quickSort_Lomuto_rand_duplicated(_begin, eqBegin, _pred);
    quickSort_Lomuto_rand_duplicated(eqEnd, _end, _pred);
}

/**
 * @brief  Quick Sort with Lomuto Partition, Random Pivot, Optimized for Contiguous Duplicated
 *         Elements, and Using Insertion Sort - O(nlogn).
 *         The input iterators must be forward iterators.
 */
template <class _It, class _Pr = std::tuple<std::less<>, std::equal_to<>>>
    requires IsTuple<_Pr>
void quickSort_Lomuto_rand_duplicated_insertion(_It, _It, const _Pr& = {})
{
    YWARNING("Quick Sort (Lomuto, Rand, Duplicated, Insertion) requires forward iterator. Skip "
             "sorting.");
}

/**
 * @brief  Quick Sort with Lomuto Partition, Random Pivot, Optimized for Contiguous Duplicated
 *         Elements, and Using Insertion Sort - O(nlogn).
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred  Must provide a tuple of predicate where the first element is the comparison
 *               predicate and the second element is the equality predicate.
 */
template <class _It, class _Pr = std::tuple<std::less<>, std::equal_to<>>>
    requires std::forward_iterator<_It> && IsTuple<_Pr>
void quickSort_Lomuto_rand_duplicated_insertion(_It _begin, _It _end, const _Pr& _pred = {})
{
    if (_begin == _end || std::next(_begin) == _end)
        return;
    auto [comp, equal_to] = _pred;
    if (std::distance(_begin, _end) + 1ULL == INSERTION_CUT) {
        insertionSort(_begin, _end, comp);
        return;
    }
    auto [eqBegin, eqEnd] = _partition_Lomuto_rand_duplicated(_begin, _end, _pred);
    quickSort_Lomuto_rand_duplicated_insertion(_begin, eqBegin, _pred);
    quickSort_Lomuto_rand_duplicated_insertion(eqEnd, _end, _pred);
}

// =================================================================================================
// Quick Sort with Hoare Partition
// -------------------------------------------------------------------------------------------------
/**
 * @brief  Partition the sequence using Hoare's partition scheme.
 *         The input iterators must be bidirectional iterators.
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred  Comparison predicate.
 */
template <class _It, class _Pr = std::less<>>
    requires std::bidirectional_iterator<_It>
_It _partition_Hoare(_It _begin, _It _end, const _Pr& _pred = {})
{
    auto pivot = *_begin;
    _It i = _begin;
    _It j = std::prev(_end);
    int64_t size = std::distance(_begin, _end) - 1;
    int64_t cnt = 0;

    while (true) {
        while (_pred(*i, pivot)) {
            ++i, ++cnt;
        }
        while (_pred(pivot, *j)) {
            --j, ++cnt;
        }
        if (cnt >= size) {
            return ++j;
        }
        std::iter_swap(i, j);
        ++i, --j, cnt += 2;
    }
    throw("Unexpected Error: You should not be here.");
    return _end;
}

/**
 * @brief  Quick Sort with Hoare Partition - O(nlogn).
 *         The input iterators must be bidirectional iterators.
 */
template <class _It, class _Pr = std::less<>>
void quickSort_Hoare(_It, _It, const _Pr& = {})
{
    YWARNING("Quick Sort (Hoare) requires bidirectional iterator. Skip sorting.");
}

/**
 * @brief  Quick Sort with Hoare Partition - O(nlogn).
 *         The input iterators must be bidirectional iterators.
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred  Comparison predicate.
 */
template <class _It, class _Pr = std::less<>>
    requires std::bidirectional_iterator<_It>
void quickSort_Hoare(_It _begin, _It _end, const _Pr& _pred = {})
{
    if (_begin == _end || std::next(_begin) == _end)
        return;
    _It p = _partition_Hoare(_begin, _end, _pred);
    quickSort_Hoare(_begin, p, _pred);
    quickSort_Hoare(p, _end, _pred);
}

/**
 * @brief  Quick Sort with Hoare Partition, Random Pivot - O(nlogn).
 *         The input iterators must be bidirectional iterators.
 */
template <class _It, class _Pr = std::less<>>
void quickSort_Hoare_rand(_It _begin, _It _end, const _Pr& _pred = {})
{
    YWARNING("Quick Sort (Hoare, Rand) requires bidirectional iterator. Skip sorting.");
}

/**
 * @brief  Quick Sort with Hoare Partition, Random Pivot - O(nlogn).
 *         The input iterators must be bidirectional iterators.
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred  Comparison predicate.
 */
template <class _It, class _Pr = std::less<>>
    requires std::bidirectional_iterator<_It>
void quickSort_Hoare_rand(_It _begin, _It _end, const _Pr& _pred = {})
{
    if (_begin == _end || std::next(_begin) == _end)
        return;
    _It mid = midOfRandom3(_begin, _end, _pred);
    std::iter_swap(_begin, mid);
    _It p = _partition_Hoare(_begin, _end, _pred);
    quickSort_Hoare_rand(_begin, p, _pred);
    quickSort_Hoare_rand(p, _end, _pred);
}

/**
 * @brief Quick Sort with Hoare Partition, Using Insertion Sort - O(nlogn).
 *        The input iterators must be bidirectional iterators.
 */
template <class _It, class _Pr = std::less<>>
void quickSort_Hoare_insertion(_It, _It, const _Pr& = {})
{
    YWARNING("Quick Sort (Hoare, Insertion) requires bidirectional iterator. Skip sorting.");
}

/**
 * @brief Quick Sort with Hoare Partition, Using Insertion Sort - O(nlogn).
 *        The input iterators must be bidirectional iterators.
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred  Comparison predicate.
 */
template <class _It, class _Pr = std::less<>>
    requires std::bidirectional_iterator<_It>
void quickSort_Hoare_insertion(_It _begin, _It _end, const _Pr& _pred = {})
{
    if (_begin == _end || std::next(_begin) == _end)
        return;
    if (std::distance(_begin, _end) == INSERTION_CUT) {
        insertionSort(_begin, _end, _pred);
        return;
    }
    _It pivot{_partition_Hoare(_begin, _end, _pred)};
    quickSort_Hoare_insertion(_begin, pivot, _pred);
    quickSort_Hoare_insertion(pivot, _end, _pred);
}
// =================================================================================================
}  // namespace mysort