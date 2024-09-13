#pragma once
#include <functional>
#include <iterator>

#include "MySort/Core/PreDefined.hpp"

namespace mysort
{
template <class _It, class _Pr = std::less<>>
void stdSort(_It _begin, _It _end, const _Pr& _pred = {})
{
    if constexpr (!std::random_access_iterator<_It>) {
        globalLogger->warn("std::sort requires random access iterator. Skip sorting.");
    } else {
        if (_begin == _end) {
            return;
        }
        std::sort(_begin, _end, _pred);
    }
}

template <class _It, class _Pr = std::less<>>
void stdStableSort(_It _begin, _It _end, const _Pr& _pred = {})
{
    if constexpr (!std::random_access_iterator<_It>) {
        globalLogger->warn(
            "std::ranges::stable_sort requires random access iterator. Skip sorting.");
    } else {
        if (_begin == _end) {
            return;
        }
        std::stable_sort(_begin, _end, _pred);
    }
}
}  // namespace mysort