#pragma once
#include "PreDefined.hpp"
#include "../Tools/Random.hpp"
#include "InsertionSort.hpp"
#include <algorithm>

namespace mysort {
    // Partition the array {seq[first : last]} into 2 (possibly empty) subarrays
    // | {seq[fisrtIndex : q - 1]} and {seq[q + 1 : last]}, such that each element of
    // | {seq[first : q - 1]} <=(or >=) {seq[q]} and, in turn, {seq[q]} <=(or >=) each
    // | element of {seq[q+1 : last]}
    // [*] Following partition always chooses the last element to be {[q]}
    template<class _RandIt, class _Pr>
    indext _partition_Lomuto(_RandIt seq, indext first, indext last, const _Pr& comp)
    {
        auto x = *(seq + last); // The chosen pivot
        indext i = first - 1;
        indext j = first;
        for (; j <= last - 1; ++j) {
            if (comp(*(seq + j), x)) {
                ++i;
                std::iter_swap(seq + i, seq + j);
            }
        }
        ++i;
        std::iter_swap(seq + i, seq + last);
        return i;
    }

    template<class _RandIt, class _Pr = std::less<void>>
    void QuickSort_Lomuto(_RandIt seq, indext first, indext last, const _Pr& comp = {})
    {
        if (first >= last) return;
        // Always choose the last (or the first) element as pivot
        // If the seq is already sorted (or reverse-sorted),
        // | the complexity rises to O(n^2)
        indext p = _partition_Lomuto(seq, first, last, comp);
        QuickSort_Lomuto(seq, first, p - 1, comp);
        QuickSort_Lomuto(seq, p + 1, last, comp);
    }

    // Tail-Recursive Optimization of {quickSort_Lomuto()}
    template<class _RandIt, class _Pr = std::less<void>>
    void QuickSort_TailRecOpt_Lomuto(_RandIt seq, indext first, indext last, const _Pr& comp = {})
    {
        while (first < last) {
            indext p = _partition_Lomuto(seq, first, last, comp);
            QuickSort_TailRecOpt_Lomuto(seq, first, p - 1, comp);
            first = p + 1;
        }
    }

    // Partition the array {seq[first : last]} into 2 (possibly empty) subarrays
    // | {seq[fisrtIndex : q - 1]} and {seq[q + 1 : last]}, such that each element of
    // | {seq[first : q - 1]} <=(or >=) {seq[q]} and, in turn, {seq[q]} <=(or >=) each
    // | element of {seq[q+1 : last]}
    // [*] Index {q} is chosen randomly, with the method: Median-of-3 Partition
    template<class _RandIt, class _Pr>
    indext _partition_Lomuto_rand(_RandIt seq, indext first, indext last, const _Pr& comp)
    {
        // Get 3 index randomly in range of [first, last]:
        Rand_Uniform<indext> randGenerator;
        std::vector<indext> vec = randGenerator.generateVec(3, first, last);
        // Choose the median of the 3 randomly chosen elems:
        indext mid = // index of the median
            (comp(*(seq + vec[0]), *(seq + vec[1])) && comp(*(seq + vec[1]), *(seq + vec[2]))) ? vec[1]    // comp(A,B) and comp(B,C) => B is median
            : (comp(*(seq + vec[1]), *(seq + vec[0])) && comp(*(seq + vec[0]), *(seq + vec[2]))) ? vec[0]  // comp(B,A) and comp(A,C) => A is median
            : vec[2];                                                                  // otherwise               => C is median
        std::iter_swap(seq + last, seq + mid);
        return _partition_Lomuto_rand(seq, first, last, comp);
    }

    template<class _RandIt, class _Pr = std::less<void>>
    void QuickSort_Lomuto_rand(_RandIt seq, indext first, indext last, const _Pr& comp = {})
    {
        if (first >= last) return;
        // If the pivot is choosen randomly, the algorithm does not rely on the input seq
        // As a result, the time complexity remains O(nlgn) when the seq is sorted
        // But if all the elements are the same, the complexitiy is still O(n^2)
        indext p = _partition_Lomuto_rand(seq, first, last, comp);
        QuickSort_Lomuto_rand(seq, first, p - 1, comp);
        QuickSort_Lomuto_rand(seq, p + 1, last, comp);
    }

    // Partition the array {seq[first : last]} into 3 subarrays:
    // | elems in {seq[m : n]} all equal to the pivot;
    // | elems in {seq[first : m-1]} all less(or larger) than the pivot;
    // | elems in {seq[n+1 : last]} all larger(or less) than the pivot
    // [*] Index of pivot is chosen randomly, with the method: Median-of-3 Partition
    // [*] Repitition optimized.
    template<class _RandIt, class _Pr1, class _Pr2>
    indext* _partition_Lomuto_rand_duplicated(_RandIt seq, indext first, indext last, const _Pr1& comp, const _Pr2& equal)
    {
        // Get 3 index randomly in range of [first, last]:
        Rand_Uniform<indext> randGenerator;
        std::vector<indext> vec = randGenerator.generateVec(3, first, last);
        // Choose the median of the 3 randomly chosen elems:
        indext mid = // index of the median
            (comp(*(seq + vec[0]), *(seq + vec[1])) && comp(*(seq + vec[1]), *(seq + vec[2]))) ? vec[1]    // comp(A,B) and comp(B,C) => B is median
            : (comp(*(seq + vec[1]), *(seq + vec[0])) && comp(*(seq + vec[0]), *(seq + vec[2]))) ? vec[0]  // comp(B,A) and comp(A,C) => A is median
            : vec[2];                                                                  // otherwise               => C is median
        std::iter_swap(seq + last, seq + mid);
        auto x = *(seq + last); // The pivot

        indext eqLeft = first - 1;
        indext i = first - 1;
        indext j = first;

        for (; j <= last - 1; ++j) {
            if (comp(*(seq + j), x)) {
                ++i;
                std::iter_swap(seq + i, seq + j);
                ++eqLeft;
                if (eqLeft != i) {
                    std::iter_swap(seq + eqLeft, seq + i);
                }
            } else if (equal(*(seq + j), x)) {
                ++i;
                std::iter_swap(seq + i, seq + j);
            }
        }
        ++i;
        std::iter_swap(seq + i, seq + last);
        ++eqLeft;
        return (new indext[2]{ eqLeft, i });
    }

    template<class _RandIt, class _Pr1 = std::less<void>, class _Pr2 = std::equal_to<void>>
    void QuickSort_Lomuto_rand_duplicated(_RandIt seq, indext first, indext last, const _Pr1& comp = {}, const _Pr2& equal = {})
    {
        if (first >= last) return;
        // See comments of function {Paritition_rand_duplicated_Lomuto()}
        indext* p = _partition_Lomuto_rand_duplicated(seq, first, last, comp, equal);
        QuickSort_Lomuto_rand_duplicated(seq, first, p[0] - 1, comp, equal);
        QuickSort_Lomuto_rand_duplicated(seq, p[1] + 1, last, comp, equal);
        delete p;
    }

    template<class _RandIt, class _Pr1 = std::less<void>, class _Pr2 = std::equal_to<void>>
    void QuickSort_Lomuto_rand_duplicated_insertion(_RandIt seq, indext first, indext last, const _Pr1& comp = {}, const _Pr2& equal = {}, sizet cut = 10LL)
    {
        if (first >= last) return;
        // Use insertion sort if the length is shorter than {cut}
        if (last - first + 1LL == cut) {
            InsertionSort(seq, first, last, comp);
            return;
        }
        indext* p = _partition_Lomuto_rand_duplicated(seq, first, last, comp, equal);
        QuickSort_Lomuto_rand_duplicated_insertion(seq, first, p[0] - 1, comp, equal, cut);
        QuickSort_Lomuto_rand_duplicated_insertion(seq, p[1] + 1, last, comp, equal, cut);
    }

    // Partition the array to 2 subarrays, any element in {seq[first : j]} is smaller (or larger)
    // | than any in {seq[j+1 : last]}
    // Hoare's scheme is more efficient than Lomuto's partition scheme because it does three times fewer
    // | swaps on average, and it creates efficient partitions even when all values are equal
    // [*] The pivot's final location is not necessarily at the index that was returned
    // [*] If input array is already sorted, complexity will also degrade to O(n^2)
    template<class _RandIt, class _Pr1, class _Pr2>
    indext _partition_Hoare(_RandIt seq, indext first, indext last, const _Pr1& comp1, const _Pr2& comp2)
    {
        auto x = *(seq + first);
        indext i = first - 1;
        indext j = last + 1;
        while (true) {
            do { --j; } while (comp2(*(seq + j), x));
            do { ++i; } while (comp1(*(seq + i), x));
            if (i < j) {
                std::iter_swap(seq + i, seq + j);
            } else {
                // Any element in {seq[first : j]} is smaller than any in {seq[j+1 : last]}.
                return j;
            }
        }
    }

    // Hoare's primitive quick sort is basically the fastest if the input scale is large, with the least use of swap.
    template<class _RandIt, class _Pr1 = std::less<void>, class _Pr2 = std::greater<void>>
    void QuickSort_Hoare(_RandIt seq, indext first, indext last, const _Pr1& comp1 = {}, const _Pr2 comp2 = {}) {
        if (first >= last) return;
        indext p = _partition_Hoare(seq, first, last, comp1, comp2);
        QuickSort_Hoare(seq, first, p, comp1, comp2);
        QuickSort_Hoare(seq, p + 1, last, comp1, comp2);
    }

    // Partition the array to 2 subarrays, any element in {seq[first : j]} is smaller (or larger)
    // | than any in {seq[j+1 : last]}
    // Hoare's scheme is more efficient than Lomuto's partition scheme because it does three times fewer
    // | swaps on average, and it creates efficient partitions even when all values are equal
    // [*] The pivot's final location is not necessarily at the index that was returned
    // [*] Pivot is chosen randomly, with the method: Median-of-3 Partition
    template<class _RandIt, class _Pr1, class _Pr2>
    indext _partition_Hoare_rand(_RandIt seq, indext first, indext last, const _Pr1& comp1, const _Pr2& comp2)
    {
        // Get 3 index randomly in range of [first, last]:
        Rand_Uniform<indext> randGenerator;
        std::vector<indext> vec = randGenerator.generateVec(3, first, last);
        // Choose the median of the 3 randomly chosen elems:
        indext mid = // index of the median
            (comp1(*(seq + vec[0]), *(seq + vec[1])) && comp1(*(seq + vec[1]), *(seq + vec[2]))) ? vec[1]    // comp(A,B) and comp(B,C) => B is median
            : (comp1(*(seq + vec[1]), *(seq + vec[0])) && comp1(*(seq + vec[0]), *(seq + vec[2]))) ? vec[0]  // comp(B,A) and comp(A,C) => A is median
            : vec[2];                                                                  // otherwise               => C is median
        std::iter_swap(seq + first, seq + mid);

        auto x = *(seq + first);
        indext i = first - 1;
        indext j = last + 1;
        while (true) {
            do { --j; } while (comp2(*(seq + j), x));
            do { ++i; } while (comp1(*(seq + i), x));
            if (i < j) {
                std::iter_swap(seq + i, seq + j);
            } else {
                // Any element in {seq[first : j]} is smaller than any in {seq[j+1 : last]}
                return j;
            }
        }
    }

    template<class _RandIt, class _Pr1 = std::less<void>, class _Pr2 = std::greater<void>>
    void QuickSort_Hoare_rand(_RandIt seq, indext first, indext last, const _Pr1& comp1 = {}, const _Pr2 comp2 = {}) {
        if (first >= last) return;
        indext p = _partition_Hoare_rand(seq, first, last, comp1, comp2);
        QuickSort_Hoare_rand(seq, first, p, comp1, comp2);
        QuickSort_Hoare_rand(seq, p + 1, last, comp1, comp2);
    }

    template<class _RandIt, class _Pr1 = std::less<void>, class _Pr2 = std::greater<void>>
    void QuickSort_Hoare_rand_insertion(_RandIt seq, indext first, indext last, const _Pr1& comp1 = {}, const _Pr2 comp2 = {}, sizet cut = 10LL) {
        if (first >= last) return;
        if (last - first + 1LL == cut) {
            InsertionSort(seq, first, last, comp1);
            return;
        }
        indext p = _partition_Hoare_rand(seq, first, last, comp1, comp2);
        QuickSort_Hoare_rand_insertion(seq, first, p, comp1, comp2);
        QuickSort_Hoare_rand_insertion(seq, p + 1, last, comp1, comp2);
    }
}