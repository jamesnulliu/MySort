#pragma once
#include <algorithm>
#include <iterator>
namespace mysort {
    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void heapSort(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end) return;

        const auto& comp{ std::get<0>(std::forward_as_tuple(preds...)) };

        std::make_heap(_begin, _end, comp);
        for (_It i = std::prev(_end); i != _begin; --i) {
            std::pop_heap(_begin, std::next(i), comp);
        }
    }
    template<class _It>
        requires std::forward_iterator<_It>
    void heapSort(_It _begin, _It _end)
    {
        heapSort(_begin, _end, std::less<>{});
    }
}