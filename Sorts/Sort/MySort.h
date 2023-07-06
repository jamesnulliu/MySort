#pragma once
#include <algorithm>

class MySort
{
public:

    enum class SORT_METHOD
    {
        BUBBLE, BUBBLE_STOP, BUBBLE_LASTSWAP
    };

    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void bubbleSort(_It _begin, _It _end, const _Pr& comp = {})
    {
        if (_begin == _end) return;
        for (auto i = _begin + 1; i != _end; ++i) {
            for (auto j = _begin; j + 1 < _end; ++j) {
                if (comp(*(j + 1), *j)) {
                    std::iter_swap(j, j + 1);
                }
            }
        }
    }

    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void bubbleSort_stop(_It _begin, _It _end, const _Pr& comp = {})
    {
        if (_begin == _end) return;
        bool swapped = false;
        for (auto i = _begin + 1; i != _end; ++i) {
            for (auto j = _begin; j + 1 != _end; ++j) {
                if (comp(*(j + 1), *j)) {
                    std::iter_swap(j, j + 1);
                    swapped = true;
                }
            }
            if (swapped == false) return;
            swapped = false;
        }
    }

    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void bubbleSort_lastSwap(_It _begin, _It _end, const _Pr& comp = {})
    {
        if (_begin == _end) return;
        _It boundary = _end;
        while (boundary != _begin) {
            _It lastSwap{};
            for (auto j = _begin; j + 1 != boundary; ++j) {
                if (comp(*(j + 1), *j)) {
                    std::iter_swap(j, j + 1);
                    lastSwap = j;
                }
            }
            boundary = lastSwap + 1;
        }
    }

    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void bubbleSort_deLastSwap(_It _begin, _It _end, const _Pr& comp = {}) {
        if (_begin == _end) return;
        _It leftBoundary{ _begin }, rightBoundary{ _end }, lastSwap{};
        while (leftBoundary != rightBoundary) {
            lastSwap = leftBoundary;
            for (auto j = leftBoundary; j != rightBoundary; ++j) {
                if (comp(*(j + 1), *j)) {
                    std::iter_swap(j, j + 1);
                    lastSwap = j;
                }
            }
            if (lastSwap == leftBoundary) break;
            rightBoundary = lastSwap + 1;
            for (j = leftBoundary; j + 1 != rightBoundary; ++j) {
                if (comp(*(j + 1), *j)) {
                    std::iter_swap(j, j + 1);
                    lastSwap = j + 2;
                }
            }
            leftBoundary = lastSwap;
        }
        ////sizet leftBoundary = 0, rightBoundary = last - first;
        ////while (leftBoundary < rightBoundary) {
        ////    indext lastSwap = leftBoundary;
        ////    for (indext j = leftBoundary; j < rightBoundary; ++j) {
        ////        if (comp(*(seq + j + 1), *(seq + j))) {
        ////            std::iter_swap(seq + j, seq + j + 1);
        ////            lastSwap = j;
        ////        }
        ////    }
        ////    if (lastSwap == leftBoundary) { break; }
        ////    rightBoundary = lastSwap;
        ////    for (indext j = rightBoundary; j > leftBoundary; --j) {
        ////        if (comp(*(seq + j), *(seq + j - 1))) {
        ////            std::iter_swap(seq + j - 1, seq + j);
        ////            lastSwap = j;
        ////        }
        ////    }
        ////    leftBoundary = lastSwap;
        ////}
    }
};
