#pragma once
#include <algorithm>
#include <iterator>

#include "MySort/Core/PreDefined.hpp"

namespace mysort
{
template <class _It, class _Pr = std::less<>>
void insertionSort(_It _begin, _It _end, const _Pr& _pred = {})
{
    YWARNING("Insertion Sort requires forward iterator. Skip sorting.");
}

template <class _It, class _Pr = std::less<>>
    requires std::forward_iterator<_It>
void insertionSort(_It _begin, _It _end, const _Pr& _pred = {})
{
    if (_begin == _end)
        return;

    for (_It j = std::next(_begin); j != _end; ++j) {
        auto key{*j};
        _It i{_begin};
        for (; i != j && _pred(*i, key); ++i) {
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
}  // namespace mysort