#pragma once
#include <algorithm>
#include "../Tools/Random.hpp"
#include <any>

template<class _It>
concept Iterator_Can_Index = requires(_It iter, uint64_t i) {
    {iter[i]} -> std::same_as<decltype(*iter)>;
};

template<class _It>
concept Iterator_Can_Add_N = requires(_It iter, uint64_t i) {
    {iter + i}->std::same_as<_It>;
};

template<class _It>
concept Iterator_Can_Sub_N = requires(_It iter, uint64_t i) {
    {iter - i}->std::same_as<_It>;
};

template<class _It>
concept Iterator_Can_PlusPlus = requires(_It iter) {
    {++iter}->std::same_as<_It&>;
    {iter++}->std::same_as<_It>;
};

template<class _It>
concept Iterator_Can_MinusMinus = requires(_It iter) {
    {--iter}->std::same_as<_It&>;
    {iter--}->std::same_as<_It>;
};

class MySort
{
public:
public:

    enum class SORT_METHOD
    {
        BUBBLE, BUBBLE_STOP, BUBBLE_LASTSWAP
    };

    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void bubbleSort(_It _begin, _It _end, const _Pr& comp = {})
    {
        if (_begin == _end) return;
        for (auto i = _begin + 1; i != _end; ++i) {
            for (auto j = _begin; j + 1 < _end; ++j) {
                if (comp(*(j + 1), *j)) {
                    std::iter_swap(j, j + 1);
                }
            }
        }
    }

    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void bubbleSort_stop(_It _begin, _It _end, const _Pr& comp = {})
    {
        if (_begin == _end) return;
        bool swapped = false;
        for (auto i = _begin + 1; i != _end; ++i) {
            for (auto j = _begin; j + 1 != _end; ++j) {
                if (comp(*(j + 1), *j)) {
                    std::iter_swap(j, j + 1);
                    swapped = true;
                }
            }
            if (swapped == false) return;
            swapped = false;
        }
    }

    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void bubbleSort__endSwap(_It _begin, _It _end, const _Pr& comp = {})
    {
        if (_begin == _end) return;
        _It boundary = _end;
        while (boundary != _begin) {
            _It _endSwap{};
            for (auto j = _begin; j + 1 != boundary; ++j) {
                if (comp(*(j + 1), *j)) {
                    std::iter_swap(j, j + 1);
                    _endSwap = j;
                }
            }
            boundary = _endSwap + 1;
        }
    }

    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void bubbleSort_deLastSwap(_It _begin, _It _end, const _Pr& comp = {}) {
        if (_begin == _end) return;
        _It leftBoundary{ _begin }, rightBoundary{ _end }, _endSwap{};
        while (leftBoundary != rightBoundary) {
            _endSwap = leftBoundary;
            for (auto j = leftBoundary; j != rightBoundary; ++j) {
                if (comp(*(j + 1), *j)) {
                    std::iter_swap(j, j + 1);
                    _endSwap = j;
                }
            }
            if (_endSwap == leftBoundary) break;
            rightBoundary = _endSwap + 1;
            for (itB = leftBoundary; itB + 1 != rightBoundary; ++itB) {
                if (comp(*(itB + 1), *itB)) {
                    std::iter_swap(itB, itB + 1);
                    _endSwap = itB + 2;
                }
            }
            leftBoundary = _endSwap;
        }
    }

    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void insertionSort(_It _begin, _It _end, const _Pr& comp = {})
    {
        if (_begin == _end) return;
        for (_It j = _begin; j + 1 != _end; ++j) {
            _It i = _begin;
            while (i != j && !comp(*i, *j)) {
                std::iter_swap(i + 1, i);
                ++i;
            }
        }
    }

    template<class _It, class _Pr>
        requires std::forward_iterator<_It>
    void _merge_array(_It _beginA, _It _endA, _It _endB, const _Pr& comp)
    {
        auto MIN = std::numeric_limits<decltype(*_beginA)>::lowest();
        auto MAX = std::numeric_limits<decltype(*_beginA)>::max();

        auto END = comp(MIN, MAX) ? MAX : MIN;

        uint64_t sizeSubA = std::distance(_beginA, _endB) + 1ULL;
        uint64_t sizeSubB = std::distance(_endA, _endB) + 1ULL;

        // Create 2 subseqs
        auto subA = new typename std::remove_reference<decltype(*_beginA)>::type[sizeSubA];
        std::copy(_beginA, _endA, subA);
        subA[sizeSubA - 1] = END;
        auto subB = new typename std::remove_reference<decltype(*seq)>::type[sizeSubB];
        std::copy(seq + _endA + 1, seq + _endB + 1, subB);
        subB[sizeSubB - 1] = END;

        // Merge two subseqs to origin seq {_beginA .. _endB}:
        auto iter = _beginA;
        uint64_t i = 0ULL, j = 0ULL;
        while (iter != _endB) {
            if (i == sizeSubA || j == sizeSubB)  break;
            if (comp(subA[i], subB[j])) {
                *(iter) = subA[i];
                ++i;
            } else {
                *(iter) = subB[j];
                ++j;
            }
            ++iter;
        }

        delete[] subA;
        delete[] subB;
    }

    template<class _It, class _Pr = std::less<void>>
    void mergeSort_array(_It _begin, _It _end, const _Pr& comp = {})
    {
        if (_begin == _end) return;
        auto mid = (_begin + _end) / 2;
        mergeSort_array(_begin, mid, comp);
        mergeSort_array(mid + 1, _end, comp);
        _merge_array(_begin, mid, _end, comp);
    }

    template<class _It, class _Pr>
        requires std::forward_iterator<_It>
    _It _partition_Lomuto(_It _begin, _It _end, const _Pr& comp)
    {
        if (_begin == _end) return _begin;
        auto x = *_begin;  // The pivot
        _It itA = _begin;
        _It itB = _begin + 1;
        for (; itB != _end; ++itB) {
            if (comp(*itB, x)) {
                ++itA;
                std::iter_swap(itA, itB);
            }
        }
        std::iter_swap(itA, _begin);
        return itA;
    }

    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto(_It _begin, _It _end, const _Pr& comp = {})
    {
        if (_begin == _end) return;
        _It p = _partition_Lomuto(_begin, _end, comp);
        quickSort_Lomuto(_begin, p, comp);
        quickSort_Lomuto(p + 1, _end, comp);
    }

    // Tail-Recursive Optimization
    template<class _It, class _Pr = std::less<void>>
        requires std::forward_iterator<_It>
    void quickSort_Lomuto_tailRecOpt(_It _begin, _It _end, const _Pr& comp = {})
    {
        while (_begin != _end) {
            _It p = _partition_Lomuto(_begin, _end, comp);
            quickSort_Lomuto_tailRecOpt(_begin, p, comp);
            _begin = ++p;
        }
    }

    template<class _It, class _Pr>
        requires std::random_access_iterator<_It>
    _It _partition_Lomuto_rand(_It _begin, _It _end, const _Pr& comp)
    {
        if (_begin == _end) return _begin;
        std::vector<uint64_t> vec = Rand_Uniform<uint64_t>().generateVec(3, 0, std::distance(_begin, _end));
        uint64_t mid =
            (comp(*(_begin + vec[0]), *(_begin + vec[1])) && comp(*(_begin + vec[1]), *(_begin + vec[2]))) ? vec[1]
            : (comp(*(_begin + vec[1]), *(_begin + vec[0])) && comp(*(_begin + vec[0]), *(_begin + vec[2]))) ? vec[0]
            : vec[2];
        std::iter_swap(_begin, _begin + mid);
        return _partition_Lomuto(_begin, _end, comp);
    }

    template<class _It, class _Pr = std::less<void>>
        requires std::random_access_iterator<_It>
    void quickSort_Lomuto_rand(_It _begin, _It _end, const _Pr& comp = {})
    {
        if (_begin == _end) return;
        _It p = _partition_Lomuto_rand(_begin, _end, comp);
        quickSort_Lomuto_rand(_begin, p, comp);
        quickSort_Lomuto_rand(p + 1, _end, comp);
    }

    template<class _It, class... _Prs>
        requires std::random_access_iterator<_It>
    uint64_t* _partition_Lomuto_rand_duplicated(_It _begin, _It _end, const _Prs&... _predicates)
    {
        if (_begin == _end) return new uint64_t[2]{ _begin, _end };

        auto preds = std::make_tuple(_predicates...);
        auto comp = std::get<0>(preds);
        auto equal = std::get<1>(preds);

        std::vector<uint64_t> vec = Rand_Uniform<uint64_t>().generateVec(3, 0, std::distance(_begin, _end));
        uint64_t mid =
            (comp(*(_begin + vec[0]), *(_begin + vec[1])) && comp(*(_begin + vec[1]), *(_begin + vec[2]))) ? vec[1]
            : (comp(*(_begin + vec[1]), *(_begin + vec[0])) && comp(*(_begin + vec[0]), *(_begin + vec[2]))) ? vec[0]
            : vec[2];
        std::iter_swap(_begin, _begin + mid);
        auto x = *(_begin + _end); // The pivot

        _It eqLeft = _begin;
        _It itA = _begin;
        _It itB = _begin + 1;

        for (; itB != _end; ++itB) {
            if (comp(*(itB), x)) {
                ++itA;
                std::iter_swap(itA, itB);
                ++eqLeft;
                if (eqLeft != itA) {
                    std::iter_swap(eqLeft, itA);
                }
            } else if (equal(*(itB), x)) {
                ++itA;
                std::iter_swap(itA, itB);
            }
        }

        std::iter_swap(itA, _end);
        ++eqLeft;
        return (new uint64_t[2]{ eqLeft, itA });
    }

    template<class _It, class... _Prs>
        requires std::random_access_iterator<_It>
    void quickSort_Lomuto_rand_duplicated(_It _begin, _It _end, const _Prs&... _predicates)
    {
        if (_begin == _end) return;
        uint64_t* p = _partition_Lomuto_rand_duplicated(_begin, _end, _predicates);
        quickSort_Lomuto_rand_duplicated(_begin, p[0], _predicates);
        quickSort_Lomuto_rand_duplicated(p[1] + 1, _end, _predicates);
        delete p;
    }

    template<class _It, class... _Prs>
        requires std::random_access_iterator<_It>
    void quickSort_Lomuto_rand_duplicated_insertion(_It _begin, _It _end, const _Prs&... _predicates)
    {
        if (_begin == _end) return;
        if (_end - _begin + 1LL == m_insertionCut) {
            insertionSort(_begin, _end, comp);
            return;
        }
        uint64_t* p = _partition_Lomuto_rand_duplicated(_begin, _end, _predicates);
        quickSort_Lomuto_rand_duplicated_insertion(_begin, p[0], _predicates);
        quickSort_Lomuto_rand_duplicated_insertion(p[1] + 1, _end, _predicates);
        delete p;
    }

    template<class _It, class... _Prs>
        requires Iterator_Can_PlusPlus<_It>&& Iterator_Can_MinusMinus<_It>
    _It _partition_Hoare(_It _begin, _It _end, const _Prs&... _predicators)
    {
        auto comp = std::get<0>(_predicators);
        auto pivot = *(_begin);
        _It i = --_begin;
        _It j = _end;
        while (true) {
            do { --j } while (comp(pivot, *j));
            do { ++i } while (comp(*i, pivot));
            if (i < j) {
                std::iter_swap(i, j);
            } else {
                // Any element in {seq[_begin : j+1)} is smaller than any in {seq[j+1 : _end)}.
                return j;
            }
        }
    }

    template<class _It, class... _Prs>
        requires Iterator_Can_PlusPlus<_It>&& Iterator_Can_MinusMinus<_It>
    void quickSort_Hoare(_It _begin, _It _end, const _Prs&... _predicators) {
        if (_begin >= _end) return;
        _It p = _partition_Hoare(_begin, _end, _predicators);
        ++p;
        quickSort_Hoare(seq, _begin, p, comp1, comp2);
        quickSort_Hoare(seq, p, _end, comp1, comp2);
    }

    template<class _It, class _Pr1, class _Pr2>
    indext _partition_Hoare_rand(_It seq, indext _begin, indext _end, const _Pr1& comp1, const _Pr2& comp2)
    {
        Rand_Uniform<indext> randGenerator;
        std::vector<indext> vec = randGenerator.generateVec(3, (double)_begin, (double)_end);
        indext mid =
            (comp1(*(seq + vec[0]), *(seq + vec[1])) && comp1(*(seq + vec[1]), *(seq + vec[2]))) ? vec[1]
            : (comp1(*(seq + vec[1]), *(seq + vec[0])) && comp1(*(seq + vec[0]), *(seq + vec[2]))) ? vec[0]
            : vec[2];
        std::iter_swap(seq + _begin, seq + mid);

        auto x = *(seq + _begin);
        indext itA = _begin - 1;
        indext itB = _end + 1;
        while (true) {
            do { --itB; } while (comp2(*(seq + itB), x));
            do { ++itA; } while (comp1(*(seq + itA), x));
            if (itA < itB) {
                std::iter_swap(seq + itA, seq + itB);
            } else {
                // Any element in {seq[_begin : j]} is smaller than any in {seq[j+1 .. _end)}
                return itB;
            }
        }
    }

    template<class _It, class _Pr1 = std::less<void>, class _Pr2 = std::greater<void>>
    void QuickSort_Hoare_Rand(_It seq, indext _begin, indext _end, const _Pr1& comp1 = {}, const _Pr2 comp2 = {}) {
        if (_begin >= _end) return;
        indext p = _partition_Hoare_rand(seq, _begin, _end, comp1, comp2);
        QuickSort_Hoare_Rand(seq, _begin, p, comp1, comp2);
        QuickSort_Hoare_Rand(seq, p + 1, _end, comp1, comp2);
    }

    template<class _It, class _Pr1 = std::less<void>, class _Pr2 = std::greater<void>>
    void QuickSort_Hoare_Rand_Insertion(_It seq, indext _begin, indext _end, const _Pr1& comp1 = {}, const _Pr2 comp2 = {}, sizet cut = 10LL) {
        if (_begin >= _end) return;
        if (_end - _begin + 1LL == cut) {
            InsertionSort(seq, _begin, _end, comp1);
            return;
        }
        indext p = _partition_Hoare_rand(seq, _begin, _end, comp1, comp2);
        QuickSort_Hoare_Rand_Insertion(seq, _begin, p, comp1, comp2);
        QuickSort_Hoare_Rand_Insertion(seq, p + 1, _end, comp1, comp2);
    }

private:
    uint64_t m_insertionCut{ 10 };
};
