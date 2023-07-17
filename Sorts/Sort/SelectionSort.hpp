#pragma once
#include "PreDefined.hpp"
#include <algorithm>

namespace mysort {
    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void selectionSort(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end) return;

        const auto& comp{ std::get<0>(std::forward_as_tuple(preds...)) };

        for (_It i = _begin; std::_Next_iter(i) != _end; ++i) {
            _It selected = i;
            for (_It j = std::_Next_iter(i); j != _end; ++j) {
                if (comp(*j, *selected)) {
                    selected = j;
                }
            }
            if (selected != i) {
                std::iter_swap(selected, i);
            }
        }
    }

    template<class _It>
        requires std::forward_iterator<_It>
    void selectionSort(_It _begin, _It _end) {
        selectionSort(_begin, _end, std::less<>{});
    }
}