#pragma once
#include "PreDefined.hpp"

#include <algorithm>

namespace mysort {
    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void bubbleSort(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end) return;

        const auto& comp{ std::get<0>(std::forward_as_tuple(preds...)) };

        _It mark{ std::_Next_iter(_begin) };
        for (_It i = std::_Next_iter(_begin); i != _end; ++i) {
            for (_It j = _begin, itM = mark; itM != _end; ++j, ++itM) {
                if (comp(*std::_Next_iter(j), *j)) {
                    std::iter_swap(j, std::_Next_iter(j));
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

        const auto& comp{ std::get<0>(std::forward_as_tuple(preds...)) };

        _It mark{ std::_Next_iter(_begin) };
        for (_It i = std::_Next_iter(_begin); i != _end; ++i) {
            bool swapped{ false };
            for (_It j = _begin, k = mark; k != _end; ++j, ++k) {
                if (comp(*std::_Next_iter(j), *j)) {
                    std::iter_swap(j, std::_Next_iter(j));
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

        const auto& comp{ std::get<0>(std::forward_as_tuple(preds...)) };

        _It leftBoundary = _begin, rightBoundary = _end;
        while (leftBoundary != rightBoundary) {
            _It lastSwap = leftBoundary;
            for (_It i = leftBoundary; std::_Next_iter(i) != rightBoundary; ++i) {
                if (comp(*std::_Next_iter(i), *i)) {
                    std::iter_swap(i, std::_Next_iter(i));
                    lastSwap = i;
                }
            }

            if (lastSwap == leftBoundary) break;
            rightBoundary = std::_Next_iter(lastSwap);

            if constexpr (std::_Is_ranges_bidi_iter_v<_It>) {
                for (_It j = std::_Prev_iter(rightBoundary); j != leftBoundary; --j) {
                    if (comp(*j, *std::_Prev_iter(j))) {
                        std::iter_swap(std::_Prev_iter(j), j);
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