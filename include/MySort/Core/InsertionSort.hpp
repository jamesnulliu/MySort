#pragma once
#include <iterator>
#include <algorithm>

// [ToDo] This should be written to a config file
#include "MySort/Core/PreDefined.hpp"

namespace mysort {
    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void insertionSort(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end) return;

        const auto& comp{ std::get<0>(std::forward_as_tuple(preds...)) };

        for (_It j = std::next(_begin); j != _end; ++j) {
            auto key{ *j };
            _It i{ _begin };
            for (; i != j && comp(*i, key); ++i) {
            }
            if constexpr (std::bidirectional_iterator<_It>) {
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