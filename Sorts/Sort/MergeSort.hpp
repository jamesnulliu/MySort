#pragma once
#include "PreDefined.hpp"
#include <algorithm>
#include <vector>

namespace mysort {
    template<class _RandIt, class _Pr>
    void _merge(_RandIt seq, indext subAFirst, indext subALast, indext subBLast, const auto MIN, const auto MAX, const _Pr& comp)
    {
        // {END} is set at the end of each subarray.
        auto END = comp(MIN, MAX) ? MAX : MIN;

        sizet sizeSubA = subALast - subAFirst + 2;
        sizet sizeSubB = subBLast - subALast + 1;

        auto subA = new typename std::remove_reference<decltype(*seq)>::type[sizeSubA];
        std::copy(seq + subAFirst, seq + subALast + 1, subA);
        subA[sizeSubA - 1] = END;

        auto subB = new typename std::remove_reference<decltype(*seq)>::type[sizeSubB];
        std::copy(seq + subALast + 1, seq + subBLast + 1, subB);
        subB[sizeSubB - 1] = END;

        // Merge two subsequences to origin {seq[subAFirst : subBLast]}:
        for (indext k = subAFirst, i = 0, j = 0; k <= subBLast; ++k) {
            if (i >= sizeSubA || j >= sizeSubB) return;
            // Merge:
            if (comp(subA[i], subB[j])) {
                *(seq + k) = subA[i]; ++i;
            } else {
                *(seq + k) = subB[j]; ++j;
            }
        }

        delete[] subA;
        delete[] subB;
    }

    template<class _RandIt, class _Pr = std::less<void>>
    void MergeSort(_RandIt seq, indext first, indext last, const auto MIN, const auto MAX, const _Pr& comp = {})
    {
        if (first >= last) return;
        indext mid = (first + last) / 2;
        MergeSort(seq, first, mid, MAX, MIN, comp);
        MergeSort(seq, mid + 1, last, MAX, MIN, comp);
        _merge(seq, first, mid, last, MAX, MIN, comp);
    }
}