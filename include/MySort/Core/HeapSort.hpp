#pragma once
#include <algorithm>
#include <iterator>

namespace mysort
{
template <class _It, class _Pr = std::less<>>
void heapSort(_It _begin, _It _end, const _Pr _pred = {})
{
    if constexpr (!std::random_access_iterator<_It>) {
        YWARNING("Heap Sort requires random access iterator. Skip sorting.");
    } else {
        if (_begin == _end)
            return;

        std::make_heap(_begin, _end, _pred);
        for (_It i = std::prev(_end); i != _begin; --i) {
            std::pop_heap(_begin, std::next(i), _pred);
        }
    }
}
}  // namespace mysort