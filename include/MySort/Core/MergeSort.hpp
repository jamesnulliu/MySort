#pragma once
#include <algorithm>
#include <limits>
#include <vector>

#include "MySort/Core/PreDefined.hpp"

namespace mysort
{
// =================================================================================================
// Merge Sort (Array is used to store subseqs)
// -------------------------------------------------------------------------------------------------
/**
 * @brief Merge two sorted subseqs to origin seq {_beginA .. _endB}.
 *        The input iterators must be forward iterators.
 * 
 * @param _beginA  Begin of the first subseq.
 * @param _endA  End of the first subseq.
 * @param _endB  End of the second subseq.
 * @param _pred  Comparison predicate.
 */
template <class _It, class _Pr = std::less<>>
    requires std::forward_iterator<_It>
void _merge_arr(_It _beginA, _It _endA, _It _endB, const _Pr& _pred = {})
{
    auto MIN = std::numeric_limits<std::iter_value_t<_It>>::lowest();
    auto MAX = std::numeric_limits<std::iter_value_t<_It>>::max();

    auto END = _pred(MIN, MAX) ? MAX : MIN;

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
        if (_pred(subA[i], subB[j])) {
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

/**
 * @brief Merge Sort (Array is Used to Store Subseqs) - O(nlogn).
 *        The input iterators must be forward iterators.
 * 
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred  Comparison predicate.
 */
template <class _It, class _Pr = std::less<>>
void mergeSort_arr(_It _begin, _It _end, const _Pr& _pred = {})
{
    if constexpr (!std::forward_iterator<_It>) {
        YWARNING("Merge Sort (Array) requires forward iterator. Skip sorting.");
    } else {
        if (std::next(_begin) == _end)
            return;
        _It mid = std::next(_begin, std::distance(_begin, _end) / 2);
        mergeSort_arr(_begin, mid, _pred);
        mergeSort_arr(mid, _end, _pred);
        _merge_arr(_begin, mid, _end, _pred);
    }
}
// =================================================================================================

// =================================================================================================
// Merge Sort (Natural Merge Sort)
// -------------------------------------------------------------------------------------------------
/**
 * @brief  Merge Sort (Natural Merge Sort) - O(nlogn).
 *         The input iterators must be bidirectional iterators.
 * 
 * @param _begin  Begin of the sequence.
 * @param _end  End of the sequence.
 * @param _pred Comparison predicate.
 */
template <class _It, class _Pr = std::less<>>
void mergeSort_Natural(_It _begin, _It _end, const _Pr& _pred = {})
{
    if constexpr (!std::bidirectional_iterator<_It>) {
        YWARNING("Merge Sort (Natural) requires bidirectional iterator. Skip sorting.");
    } else {
        if (std::distance(_begin, _end) <= 1)
            return;

        std::vector<_It> runs;
        runs.push_back(_begin);

        _It current = _begin;
        while (current != _end) {
            _It next = std::next(current);
            if (next == _end || _pred(*next, *current)) {
                runs.push_back(next);
            }
            current = next;
        }

        while (runs.size() > 2) {
            std::vector<_It> new_runs;
            for (size_t i = 0; i < runs.size() - 1; i += 2) {
                _It start = runs[i];
                _It mid = runs[i + 1];
                _It end = (i + 2 < runs.size()) ? runs[i + 2] : _end;
                std::inplace_merge(start, mid, end, _pred);
                new_runs.push_back(start);
            }
            if (runs.size() % 2 == 1) {
                new_runs.push_back(runs.back());
            }
            runs = std::move(new_runs);
        }

        if (runs.size() == 2) {
            std::inplace_merge(runs[0], runs[1], _end, _pred);
        }
    }
}
// =================================================================================================
}  // namespace mysort