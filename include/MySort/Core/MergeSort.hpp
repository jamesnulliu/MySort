#pragma once
#include <algorithm>
#include <limits>
#include <vector>

// [ToDo] This should be written to a config file
#include "MySort/Core/PreDefined.hpp"

namespace mysort
{
template <class _It, class... _Prs>
    requires std::random_access_iterator<_It>
void _merge_arr(_It _beginA, _It _endA, _It _endB, const _Prs&... preds)
{
    auto MIN = std::numeric_limits<std::iter_value_t<_It>>::lowest();
    auto MAX = std::numeric_limits<std::iter_value_t<_It>>::max();

    const auto& comp = std::get<0>(std::forward_as_tuple(preds...));
    auto END = comp(MIN, MAX) ? MAX : MIN;

    // Create 2 subseqs
    uint64_t sizeSubA = std::distance(_beginA, _endA) + 1ULL;
    auto subA = new std::iter_value_t<_It>[sizeSubA] {};
    std::copy(_beginA, _endA, subA);
    subA[sizeSubA - 1] = END;
    uint64_t sizeSubB = std::distance(_endA, _endB) + 1ULL;
    auto subB = new std::iter_value_t<_It>[sizeSubB] {};
    std::copy(_endA, _endB, subB);
    subB[sizeSubB - 1] = END;

    // Merge two subseqs to origin seq {_beginA .. _endB}:
    auto iter = _beginA;
    uint64_t i = 0ULL, j = 0ULL;
    while (iter != _endB) {
        if (i == sizeSubA || j == sizeSubB)
            break;
        if (comp(subA[i], subB[j])) {
            *iter = subA[i];
            ++i;
        } else {
            *iter = subB[j];
            ++j;
        }
        ++iter;
    }

    delete[] subA;
    delete[] subB;
}

template <class _It, class... _Prs>
    requires std::random_access_iterator<_It>
void mergeSort_arr(_It _begin, _It _end, const _Prs&... preds)
{
    if (std::next(_begin) == _end)
        return;
    _It mid = std::next(_begin, std::distance(_begin, _end) / 2);
    mergeSort_arr(_begin, mid, preds...);
    mergeSort_arr(mid, _end, preds...);
    _merge_arr(_begin, mid, _end, preds...);
}

template <class _It>
    requires std::random_access_iterator<_It>
void mergeSort_arr(_It _begin, _It _end)
{
    mergeSort_arr(_begin, _end, std::less<>{});
}
}  // namespace mysort