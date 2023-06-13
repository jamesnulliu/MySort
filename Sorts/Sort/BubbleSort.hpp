#pragma once
#include "PreDefined.hpp"

#include <algorithm>

namespace mysort
{
    template<class _RandIt, class _Pr = std::less<void>>
    void BubbleSort(_RandIt seq, indext first, indext last, const _Pr& comp = {}) {
        sizet size = last - first + 1;
        for (indext i = 1; i < size; ++i) {
            for (indext j = 0; j < size - i; ++j) {
                if (comp(*(seq + j + 1), *(seq + j))) {
                    std::iter_swap(seq + j, seq + j + 1);
                }
            }
        }
    }

    template<class _RandIt, class _Pr = std::less<void>>
    void BubbleSort_Stop(_RandIt seq, indext first, indext last, const _Pr& comp = {}) {
        sizet size = last - first + 1;
        bool swapped = false;
        for (indext i = 1; i < size; ++i) {
            for (indext j = 0; j < size - i; ++j) {
                if (comp(*(seq + j + 1), *(seq + j))) {
                    std::iter_swap(seq + j, seq + j + 1);
                    swapped = true;
                }
            }
            if (swapped == false) return;
            swapped = false;
        }
    }

    template<class _RandIt, class _Pr = std::less<void>>
    void BubbleSort_LastSwap(_RandIt seq, indext first, indext last, const _Pr& comp = {}) {
        sizet boundary = last - first;
        while (boundary > 0) {
            indext lastSwap = 0;
            for (indext j = 0; j < boundary; ++j) {
                if (comp(*(seq + j + 1), *(seq + j))) {
                    std::iter_swap(seq + j, seq + j + 1);
                    lastSwap = j;
                }
            }
            boundary = lastSwap;
        }
    }

    template<class _RandIt, class _Pr = std::less<void>>
    void BubbleSort_Bidirectional_LastSwap(_RandIt seq, indext first, indext last, const _Pr& comp = {}) {
        sizet leftBoundary = 0, rightBoundary = last - first;
        while (leftBoundary < rightBoundary) {
            indext lastSwap = leftBoundary;
            for (indext j = leftBoundary; j < rightBoundary; ++j) {
                if (comp(*(seq + j + 1), *(seq + j))) {
                    std::iter_swap(seq + j, seq + j + 1);
                    lastSwap = j;
                }
            }
            if (lastSwap == leftBoundary) { break; }
            rightBoundary = lastSwap;
            for (indext j = rightBoundary; j > leftBoundary; --j) {
                if (comp(*(seq + j), *(seq + j - 1))) {
                    std::iter_swap(seq + j - 1, seq + j);
                    lastSwap = j;
                }
            }
            leftBoundary = lastSwap;
        }
    }
}