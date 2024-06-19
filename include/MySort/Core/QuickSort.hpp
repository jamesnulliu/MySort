#pragma once
#include <algorithm>
#include <utility>
#include <tuple>

#include "MySort/Core/Utilities.hpp"
#include "MySort/Core/InsertionSort.hpp"
// [ToDo] This should be written to a config file
#include "MySort/Core/PreDefined.hpp"

namespace mysort {
    // TODO:
    //   If {_begin} equals {_end} or the next iterator of {_begin} equals {_end},
    //   some partition functions may go wrong.
    //   Additional control flow is needed.

    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    _It _partition_Lomuto(_It _begin, _It _end, const _Prs&... preds)
    {
        const auto& comp = std::get<0>(std::forward_as_tuple(preds...));
        auto pivot = *_begin;
        _It i = _begin;
        _It j = std::next(_begin);
        for (; j != _end; ++j) {
            if (comp(*j, pivot)) {
                ++i;
                std::iter_swap(i, j);
            }
        }
        std::iter_swap(i, _begin);
        return i;
    }

    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end || std::next(_begin) == _end) return;
        _It pivot = _partition_Lomuto(_begin, _end, preds...);
        quickSort_Lomuto(_begin, pivot, preds...);
        quickSort_Lomuto(++pivot, _end, preds...);
    }

    template<class _It>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto(_It _begin, _It _end)
    {
        quickSort_Lomuto(_begin, _end, std::less<>{});
    }

    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto_tailRec(_It _begin, _It _end, const _Prs&... preds)
    {
        while (_begin != _end && std::next(_begin) != _end) {
            _It pivot = _partition_Lomuto(_begin, _end, preds...);
            quickSort_Lomuto_tailRec(_begin, pivot, preds...);
            _begin = ++pivot;
        }
    }

    template<class _It>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto_tailRec(_It _begin, _It _end)
    {
        quickSort_Lomuto_tailRec(_begin, _end, std::less<>{});
    }

    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    _It _partition_Lomuto_rand(_It _begin, _It _end, const _Prs&... preds)
    {
        _It mid = midOfRandom3(_begin, _end, std::get<0>(std::forward_as_tuple(preds...)));
        std::iter_swap(_begin, mid);
        return _partition_Lomuto(_begin, _end, preds...);
    }

    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto_rand(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end || std::next(_begin) == _end) return;
        _It pivot{ _partition_Lomuto_rand(_begin, _end, preds...) };
        quickSort_Lomuto_rand(_begin, pivot, preds...);
        quickSort_Lomuto_rand(++pivot, _end, preds...);
    }

    template<class _It>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto_rand(_It _begin, _It _end)
    {
        quickSort_Lomuto_rand(_begin, _end, std::less<>{});
    }

    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    std::pair<_It, _It> _partition_Lomuto_rand_duplicated(_It _begin, _It _end, const _Prs&... preds)
    {
        auto comp = std::get<0>(std::forward_as_tuple(preds...));
        auto equal_to = std::get<1>(std::forward_as_tuple(preds...));

        _It mid = midOfRandom3(_begin, _end, comp);
        std::iter_swap(_begin, mid);
        auto pivot = *_begin;

        _It eqPrev = _begin;
        _It eqEnd = std::next(_begin);
        _It iter = std::next(_begin);

        for (; iter != _end; ++iter) {
            if (equal_to(*iter, pivot)) {
                std::iter_swap(eqEnd, iter);
                ++eqEnd;
            } else if (comp(*iter, pivot)) {
                std::iter_swap(eqEnd, iter);
                _It eqFirst{ std::next(eqPrev) };
                if (eqFirst != eqEnd) {
                    std::iter_swap(eqEnd, eqFirst);
                }
                ++eqPrev, ++eqEnd;
            }
        }

        std::iter_swap(_begin, eqPrev);

        return { ++eqPrev, eqEnd };
    }

    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto_rand_duplicated(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end || std::next(_begin) == _end) return;

        auto [eqBegin, eqEnd] = _partition_Lomuto_rand_duplicated(_begin, _end, preds...);
        quickSort_Lomuto_rand_duplicated(_begin, eqBegin, preds...);
        quickSort_Lomuto_rand_duplicated(eqEnd, _end, preds...);
    }

    template<class _It, class _Pr>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto_rand_duplicated(_It _begin, _It _end, const _Pr& comp)
    {
        quickSort_Lomuto_rand_duplicated(_begin, _end, comp, std::equal_to<>{});
    }

    template<class _It>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto_rand_duplicated(_It _begin, _It _end)
    {
        quickSort_Lomuto_rand_duplicated(_begin, _end, std::less<>{});
    }

    template<class _It, class... _Prs>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto_rand_duplicated_insertion(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end || std::next(_begin) == _end) return;
        if (std::distance(_begin, _end) + 1ULL == INSERTION_CUT) {
            insertionSort(_begin, _end, preds...);
            return;
        }
        auto [eqBegin, eqEnd] = _partition_Lomuto_rand_duplicated(_begin, _end, preds...);
        quickSort_Lomuto_rand_duplicated_insertion(_begin, eqBegin, preds...);
        quickSort_Lomuto_rand_duplicated_insertion(eqEnd, _end, preds...);
    }

    template<class _It, class _Pr>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto_rand_duplicated_insertion(_It _begin, _It _end, const _Pr& comp)
    {
        quickSort_Lomuto_rand_duplicated_insertion(_begin, _end, comp, std::equal_to<>{});
    }

    template<class _It>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto_rand_duplicated_insertion(_It _begin, _It _end)
    {
        quickSort_Lomuto_rand_duplicated_insertion(_begin, _end, std::less<>{});
    }

    template<class _It, class... _Prs>
        requires std::bidirectional_iterator<_It>
    _It _partition_Hoare(_It _begin, _It _end, const _Prs&... preds)
    {
        const auto& comp{ std::get<0>(std::forward_as_tuple(preds...)) };
        auto pivot = *_begin;
        _It i = _begin;
        _It j = std::prev(_end);
        int64_t size = std::distance(_begin, _end) - 1;
        int64_t cnt = 0;

        while (true) {
            while (comp(*i, pivot)) {
                ++i, ++cnt;
            }
            while (comp(pivot, *j)) {
                --j, ++cnt;
            }
            if (cnt >= size) {
                return ++j;
            }
            std::iter_swap(i, j);
            ++i, --j, cnt += 2;
        }
        throw("Unexpected Error: You should not be here.");
        return _end;
    }

    template<class _It, class... _Prs>
        requires std::bidirectional_iterator<_It>
    void quickSort_Hoare(_It _begin, _It _end, const _Prs&... preds) {
        if (_begin == _end || std::next(_begin) == _end) return;
        _It p = _partition_Hoare(_begin, _end, preds...);
        quickSort_Hoare(_begin, p, preds...);
        quickSort_Hoare(p, _end, preds...);
    }

    template<class _It, class... _Prs>
        requires std::bidirectional_iterator<_It>
    void quickSort_Hoare(_It _begin, _It _end)
    {
        quickSort_Hoare(_begin, _end, std::less<>{});
    }

    template<class _It, class... _Prs>
        requires std::bidirectional_iterator<_It>
    void quickSort_Hoare_rand(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end || std::next(_begin) == _end) return;
        const auto& comp = std::get<0>(std::forward_as_tuple(preds...));
        _It mid = midOfRandom3(_begin, _end, comp);
        std::iter_swap(_begin, mid);
        _It p = _partition_Hoare(_begin, _end, preds...);
        quickSort_Hoare_rand(_begin, p, preds...);
        quickSort_Hoare_rand(p, _end, preds...);
    }

    template<class _It, class... _Prs>
        requires std::bidirectional_iterator<_It>
    void quickSort_Hoare_rand(_It _begin, _It _end)
    {
        quickSort_Hoare_rand(_begin, _end, std::less<>{});
    }

    template<class _It, class... _Prs>
        requires std::bidirectional_iterator<_It>
    void quickSort_Hoare_insertion(_It _begin, _It _end, const _Prs&... preds)
    {
        if (_begin == _end || std::next(_begin) == _end) return;
        if (std::distance(_begin, _end) == INSERTION_CUT) {
            insertionSort(_begin, _end, preds...);
            return;
        }
        _It pivot{ _partition_Hoare(_begin, _end, preds...) };
        quickSort_Hoare_insertion(_begin, pivot, preds...);
        quickSort_Hoare_insertion(pivot, _end, preds...);
    }

    template<class _It>
        requires std::bidirectional_iterator<_It>
    void quickSort_Hoare_insertion(_It _begin, _It _end)
    {
        quickSort_Hoare_insertion(_begin, _end, std::less<>{});
    }
}