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

        _It mark = _begin + 1;
        for (_It i = _begin + 1; i != _end; ++i) {
            for (_It j = _begin, k = mark; k != _end; ++j, ++k) {
                if (comp(*(j + 1), *j)) {
                    std::iter_swap(j, j + 1);
                }
            }
            ++mark;
        }
    }

    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void bubbleSort_stop(_It _begin, _It _end, const _Pr& comp = {})
    {
        if (_begin == _end) return;

        _It mark = _begin + 1;
        for (_It i = _begin + 1; i != _end; ++i) {
            bool swapped = false;
            for (_It j = _begin, k = mark; k != _end; ++j, ++k) {
                if (comp(*(j + 1), *j)) {
                    std::iter_swap(j, j + 1);
                    swapped = true;
                }
            }
            if (swapped == false) return;
            ++mark;
        }
    }

    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void bubbleSort_narrowBoundary(_It _begin, _It _end, const _Pr& comp = {})
    {
        if (_begin == _end) return;

        _It leftBoundary = _begin, rightBoundary = _end;
        while (leftBoundary != rightBoundary) {
            _It lastSwap = leftBoundary;
            for (_It i = leftBoundary; i + 1 != rightBoundary; ++i) {
                if (comp(*(i + 1), *i)) {
                    std::iter_swap(i, i + 1);
                    lastSwap = i;
                }
            }

            if (lastSwap == leftBoundary) break;
            rightBoundary = lastSwap + 1;

            if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, typename std::iterator_traits<_It>::iterator_category>) {
                for (_It j = rightBoundary - 1; j != leftBoundary; --j) {
                    if (comp(*j, *(j - 1))) {
                        std::iter_swap(j - 1, j);
                        lastSwap = j;
                    }
                }
                leftBoundary = lastSwap;
            }
        }
    }

    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void selectionSort(_It _begin, _It _end, const _Pr & comp = {})
    {
        for (_It i = _begin; i + 1 != _end; ++i) {
            _It selected = i;
            for (_It j = i + 1; j != _end; ++j) {
                if (comp(*j, *selected)) {
                    selected = j;
                }
            }
            if (selected != i) {
                std::iter_swap(selected, i);
            }
        }
    }
};
