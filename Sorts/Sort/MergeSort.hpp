#pragma once
#include "PreDefined.hpp"
#include <algorithm>
#include <vector>
#include <limits>

namespace mysort {
    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void _merge_arr(_It _beginA, _It _endA, _It _endB, const _Prs&... preds)
    {
        auto MIN{ std::numeric_limits<std::remove_reference_t<decltype(*_beginA)>>::lowest() };
        auto MAX{ std::numeric_limits<std::remove_reference_t<decltype(*_beginA)>>::max() };

        const auto& comp{ std::get<0>(std::forward_as_tuple(preds...)) };
        auto END{ comp(MIN, MAX) ? MAX : MIN };

        // Create 2 subseqs
        uint64_t sizeSubA{ std::distance(_beginA, _endA) + 1ULL };
        auto subA{ new typename std::remove_reference<decltype(*_beginA)>::type[sizeSubA]{} };
        std::copy(_beginA, _endA, subA);
        subA[sizeSubA - 1] = END;
        uint64_t sizeSubB{ std::distance(_endA, _endB) + 1ULL };
        auto subB{ new typename std::remove_reference<decltype(*_beginA)>::type[sizeSubB]{} };
        std::copy(_endA, _endB, subB);
        subB[sizeSubB - 1] = END;

        // Merge two subseqs to origin seq {_beginA .. _endB}:
        auto iter{ _beginA };
        uint64_t i{ 0ULL }, j{ 0ULL };
        while (iter != _endB) {
            if (i == sizeSubA || j == sizeSubB)  break;
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

    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void mergeSort_arr(_It _begin, _It _end, const _Prs&... preds)
    {
        if (std::_Next_iter(_begin) == _end) return;
        _It mid = std::next(_begin, std::distance(_begin, _end) / 2);
        mergeSort_arr(_begin, mid, preds...);
        mergeSort_arr(mid, _end, preds...);
        _merge_arr(_begin, mid, _end, preds...);
    }

    template<class _It>
        requires std::forward_iterator<_It>
    void mergeSort_arr(_It _begin, _It _end)
    {
        mergeSort_arr(_begin, _end, std::less<>{});
    }
}