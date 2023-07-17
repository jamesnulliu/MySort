#pragma once
#include "PreDefined.hpp"

#include <algorithm>

namespace mysort {
    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void insertionSort(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end) return;

        const auto& comp{ std::get<0>(std::forward_as_tuple(preds...)) };

        for (_It j = std::_Next_iter(_begin); j != _end; ++j) {
            auto key{ *j };
            _It i{ _begin };
            for (; i != j && comp(*i, key); ++i) {
            }
            if constexpr (std::_Is_ranges_bidi_iter_v<_It>) {
                std::copy_backward(i, j, std::next(j, 1));
            } else {
                for (_It k = i; k != j; ++k) {
                    std::iter_swap(k, j);
                }
            }
            *i = key;
        }
    }

    template<class _It>
        requires std::forward_iterator<_It>
    void insertionSort(_It _begin, _It _end)
    {
        insertionSort(_begin, _end, std::less<>{});
    }
}