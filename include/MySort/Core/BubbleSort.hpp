#pragma once
#include <algorithm>
#include <iterator>

// [ToDo] This should be written to a config file
#include "MySort/Core/PreDefined.hpp"

namespace mysort {
    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void bubbleSort(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end) return;

        const auto& comp = std::get<0>(std::forward_as_tuple(preds...));

        _It mark = std::next(_begin);
        for (_It i = std::next(_begin); i != _end; ++i) {
            for (_It j = _begin, itM = mark; itM != _end; ++j, ++itM) {
                if (comp(*std::next(j), *j)) {
                    std::iter_swap(j, std::next(j));
                }
            }
            ++mark;
        }
    }

    template<class _It>
        requires std::forward_iterator<_It>
    void bubbleSort(_It _begin, _It _end) {
        bubbleSort(_begin, _end, std::less<>{});
    }

    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void bubbleSort_stop(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end) return;

        const auto& comp = std::get<0>(std::forward_as_tuple(preds...));

        _It mark = std::next(_begin);
        for (_It i = std::next(_begin); i != _end; ++i) {
            bool swapped = false;
            for (_It j = _begin, k = mark; k != _end; ++j, ++k) {
                if (comp(*std::next(j), *j)) {
                    std::iter_swap(j, std::next(j));
                    swapped = true;
                }
            }
            if (swapped == false) return;
            ++mark;
        }
    }

    template<class _It>
        requires std::forward_iterator<_It>
    void bubbleSort_stop(_It _begin, _It _end)
    {
        bubbleSort_stop(_begin, _end, std::less<>{});
    }

    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void bubbleSort_narrowBoundary(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end) return;

        const auto& comp = std::get<0>(std::forward_as_tuple(preds...));

        _It leftBoundary = _begin, rightBoundary = _end;
        while (leftBoundary != rightBoundary) {
            _It lastSwap = leftBoundary;
            for (_It i = leftBoundary; std::next(i) != rightBoundary; ++i) {
                if (comp(*std::next(i), *i)) {
                    std::iter_swap(i, std::next(i));
                    lastSwap = i;
                }
            }

            if (lastSwap == leftBoundary) break;
            rightBoundary = std::next(lastSwap);

            if constexpr (std::bidirectional_iterator<_It>) {
                for (_It j = std::prev(rightBoundary); j != leftBoundary; --j) {
                    if (comp(*j, *std::prev(j))) {
                        std::iter_swap(std::prev(j), j);
                        lastSwap = j;
                    }
                }
            }
            leftBoundary = lastSwap;
        }
    }

    template<class _It>
        requires std::forward_iterator<_It>
    void bubbleSort_narrowBoundary(_It _begin, _It _ends)
    {
        bubbleSort_narrowBoundary(_begin, _ends, std::less<>{});
    }
}