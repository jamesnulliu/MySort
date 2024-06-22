#pragma once

#include "MySort/Core/BubbleSort.hpp"
#include "MySort/Core/HeapSort.hpp"
#include "MySort/Core/InsertionSort.hpp"
#include "MySort/Core/MergeSort.hpp"
#include "MySort/Core/QuickSort.hpp"
#include "MySort/Core/SelectionSort.hpp"
#include "MySort/TestPattern/BaseTestPattern.hpp"

namespace testPatterns
{
class BubbleSort : public BaseTestPattern
{
public:
    explicit BubbleSort() : BaseTestPattern("Bubble Sort")
    {
    }

private:
    virtual void sort_impl()
    {
        if constexpr (std::forward_iterator<decltype(m_testData.begin())>) {
            CompareCounter<ELEMENT_TYPE> comp;
            mysort::bubbleSort(m_testData.begin(), m_testData.end(), comp);
            count = comp.getCount();
            comp.resetCount();
        }
    }
};

class BubbleSort_Stop : public BaseTestPattern
{
public:
    explicit BubbleSort_Stop() : BaseTestPattern("Bubble Sort (Stop in Time)")
    {
    }

private:
    virtual void sort_impl()
    {
        if constexpr (std::forward_iterator<decltype(m_testData.begin())>) {
            CompareCounter<ELEMENT_TYPE> comp;
            mysort::bubbleSort_stop(m_testData.begin(), m_testData.end(), comp);
            count = comp.getCount();
            comp.resetCount();
        }
    }
};

class BubbleSort_NarrowBoundary : public BaseTestPattern
{
public:
    explicit BubbleSort_NarrowBoundary() : BaseTestPattern("Bubble Sort (Narrow Boundary)")
    {
    }

private:
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE> comp;
        mysort::bubbleSort_narrowBoundary(m_testData.begin(), m_testData.end(), comp);
        count = comp.getCount();
        comp.resetCount();
    }
};

class InsertionSort : public BaseTestPattern
{
public:
    explicit InsertionSort() : BaseTestPattern("Insertion Sort")
    {
    }

private:
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE> comp;
        mysort::insertionSort(m_testData.begin(), m_testData.end(), comp);
        count = comp.getCount();
        comp.resetCount();
    }
};

class SelectionSort : public BaseTestPattern
{
public:
    explicit SelectionSort() : BaseTestPattern("Selection Sort")
    {
    }
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE> comp;
        mysort::selectionSort(m_testData.begin(), m_testData.end(), comp);
        count = comp.getCount();
        comp.resetCount();
    }
};

class MergeSort : public BaseTestPattern
{
public:
    explicit MergeSort() : BaseTestPattern("Merge Sort (Array)")
    {
    }

private:
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE> comp;
        mysort::mergeSort_arr(m_testData.begin(), m_testData.end(), comp);
        count = comp.getCount();
        comp.resetCount();
    }
};

class MergeSort_Natural : public BaseTestPattern
{
public:
    explicit MergeSort_Natural() : BaseTestPattern("Merge Sort (Natural)")
    {
    }

private:
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE> comp;
        mysort::mergeSort_Natural(m_testData.begin(), m_testData.end(), comp);
        count = comp.getCount();
        comp.resetCount();
    }
};

class QuickSort_Lomuto : public BaseTestPattern
{
public:
    explicit QuickSort_Lomuto() : BaseTestPattern("Quick Sort (Lomuto)")
    {
    }

private:
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE> comp;
        mysort::quickSort_Lomuto(m_testData.begin(), m_testData.end(), comp);
        count = comp.getCount();
        comp.resetCount();
    }
};

class QuickSort_Lomuto_TailRecOpt : public BaseTestPattern
{
public:
    explicit QuickSort_Lomuto_TailRecOpt() : BaseTestPattern("Quick Sort (Lomuto, TailRecOpt)")
    {
    }

private:
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE> comp;
        mysort::quickSort_Lomuto_tailRec(m_testData.begin(), m_testData.end(), comp);
        count = comp.getCount();
        comp.resetCount();
    }
};

class QuickSort_Lomuto_Rand : public BaseTestPattern
{
public:
    explicit QuickSort_Lomuto_Rand() : BaseTestPattern("Quick Sort (Lomuto, Rand)")
    {
    }
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE> comp;
        mysort::quickSort_Lomuto_rand(m_testData.begin(), m_testData.end(), comp);
        count = comp.getCount();
        comp.resetCount();
    }
};

class QuickSort_Lomuto_Rand_Duplicated : public BaseTestPattern
{
public:
    explicit QuickSort_Lomuto_Rand_Duplicated()
        : BaseTestPattern("Quick Sort (Lomuto, Rand, Duplicated)")
    {
    }
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE, std::less<>> comp;
        CompareCounter<ELEMENT_TYPE, std::equal_to<>> equal;
        mysort::quickSort_Lomuto_rand_duplicated(m_testData.begin(), m_testData.end(),
                                                 std::tuple(comp, equal));
        count = comp.getCount();
        count += equal.getCount();
        comp.resetCount();
        equal.resetCount();
    }
};

class QuickSort_Lomuto_Rand_Duplicated_Insertion : public BaseTestPattern
{
public:
    explicit QuickSort_Lomuto_Rand_Duplicated_Insertion()
        : BaseTestPattern("Quick Sort (Lomuto, Rand, Duplicated, Insertion)")
    {
    }

private:
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE, std::less<>> comp;
        CompareCounter<ELEMENT_TYPE, std::equal_to<>> equal;
        mysort::quickSort_Lomuto_rand_duplicated_insertion(m_testData.begin(), m_testData.end(),
                                                           std::tuple(comp, equal));
        count = comp.getCount();
        count += equal.getCount();
        comp.resetCount();
        equal.resetCount();
    }
};

class QuickSort_Hoare : public BaseTestPattern
{
public:
    explicit QuickSort_Hoare() : BaseTestPattern("Quick Sort (Hoare)")
    {
    }

private:
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE> comp;
        mysort::quickSort_Hoare(m_testData.begin(), m_testData.end(), comp);
        count = comp.getCount();
        comp.resetCount();
    }
};

class QuickSort_Hoare_rand : public BaseTestPattern
{
public:
    explicit QuickSort_Hoare_rand() : BaseTestPattern("Quick Sort (Hoare, Rand)")
    {
    }

private:
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE> comp;
        mysort::quickSort_Hoare_rand(m_testData.begin(), m_testData.end(), comp);
        count = comp.getCount();
        comp.resetCount();
    }
};

class QuickSort_Hoare_insertion : public BaseTestPattern
{
public:
    explicit QuickSort_Hoare_insertion() : BaseTestPattern("Quick Sort (Hoare, Rand, Insertion)")
    {
    }

private:
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE> comp;
        mysort::quickSort_Hoare_insertion(m_testData.begin(), m_testData.end(), comp);
        count = comp.getCount();
        comp.resetCount();
    }
};

class HeapSort : public BaseTestPattern
{
public:
    explicit HeapSort() : BaseTestPattern("Heap Sort")
    {
    }

private:
    virtual void sort_impl()
    {
        CompareCounter<ELEMENT_TYPE> comp;
        mysort::heapSort(m_testData.begin(), m_testData.end(), comp);
        count = comp.getCount();
        comp.resetCount();
    }
};
}  // namespace testPatterns