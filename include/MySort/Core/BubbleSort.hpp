#pragma once
#include <algorithm>
#include <iterator>

#include "MySort/Core/PreDefined.hpp"

namespace mysort
{
template <class _It, class _Pr = std::less<>>
void bubbleSort(_It _begin, _It _end, const _Pr& _pred = {})
{
    if constexpr (!std::forward_iterator<_It>) {
        YWARNING("Bubble Sort requires forward iterator. Skip sorting.");
    } else {
        if (_begin == _end)
            return;
        _It mark = std::next(_begin);
        for (_It i = std::next(_begin); i != _end; ++i) {
            for (_It j = _begin, itM = mark; itM != _end; ++j, ++itM) {
                if (_pred(*std::next(j), *j)) {
                    std::iter_swap(j, std::next(j));
                }
            }
            ++mark;
        }
    }
}

template <class _It, class _Pr = std::less<>>
void bubbleSort_stop(_It _begin, _It _end, const _Pr& _pred = {})
{
    if constexpr (!std::forward_iterator<_It>) {
        YWARNING("Bubble Sort (Stop) requires forward iterator. Skip sorting.");
    } else {
        if (_begin == _end)
            return;

        _It mark = std::next(_begin);
        for (_It i = std::next(_begin); i != _end; ++i) {
            bool swapped = false;
            for (_It j = _begin, k = mark; k != _end; ++j, ++k) {
                if (_pred(*std::next(j), *j)) {
                    std::iter_swap(j, std::next(j));
                    swapped = true;
                }
            }
            if (swapped == false)
                return;
            ++mark;
        }
    }
}

template <class _It, class _Pr = std::less<>>
void bubbleSort_narrowBoundary(_It _begin, _It _end, const _Pr& _pred = {})
{
    if constexpr (!std::forward_iterator<_It>) {
        YWARNING("Bubble Sort (Narrow Boundary) requires forward iterator. Skip sorting.");
    } else {
        // If no element to sort, return.
        if (_begin == _end) {
            return;
        }
        _It leftBoundary = _begin, rightBoundary = _end;
        while (leftBoundary != rightBoundary) {
            _It lastSwap = leftBoundary;
            for (_It i = leftBoundary; std::next(i) != rightBoundary; ++i) {
                if (_pred(*std::next(i), *i)) {
                    std::iter_swap(i, std::next(i));
                    lastSwap = i;
                }
            }
            // If no swap happened, it means the array is already sorted.
            if (lastSwap == leftBoundary) {
                break;
            }
            rightBoundary = std::next(lastSwap);
            if constexpr (std::bidirectional_iterator<_It>) {

                for (_It j = std::prev(rightBoundary); j != leftBoundary; --j) {
                    if (_pred(*j, *std::prev(j))) {
                        std::iter_swap(std::prev(j), j);
                        lastSwap = j;
                    }
                }
                leftBoundary = lastSwap;
            }
        }
    }
}
}  // namespace mysort