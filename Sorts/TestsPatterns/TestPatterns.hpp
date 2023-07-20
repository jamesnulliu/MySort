#pragma once

#include "BaseTestPattern.hpp"

#include "../Sort/BubbleSort.hpp"
#include "../Sort/InsertionSort.hpp"
#include "../Sort/MergeSort.hpp"
#include "../Sort/QuickSort.hpp"
#include "../Sort/SelectionSort.hpp"

namespace testPatterns {
    class BubbleSort : public BaseTestPattern
    {
    public:
        explicit BubbleSort() : BaseTestPattern("[Bubble Sort]") {}
    private:
        virtual void sort_impl()
        {
            mysort::bubbleSort(m_testData.begin(), m_testData.end());
        }
    };

    class BubbleSort_Stop : public BaseTestPattern
    {
    public:
        explicit BubbleSort_Stop() : BaseTestPattern("[Bubble Sort Stop in Time]") {}
    private:
        virtual void sort_impl()
        {
            mysort::bubbleSort_stop(m_testData.begin(), m_testData.end());
        }
    };

    class BubbleSort_NarrowBoundary : public BaseTestPattern
    {
    public:
        explicit BubbleSort_NarrowBoundary() : BaseTestPattern("[Bubble Sort Narrow Boundary]") {}
    private:
        virtual void sort_impl()
        {
            mysort::bubbleSort_narrowBoundary(m_testData.begin(), m_testData.end());
        }
    };

    class InsertionSort : public BaseTestPattern
    {
    public:
        explicit InsertionSort() : BaseTestPattern("[Insertion Sort]") {}
    private:
        virtual void sort_impl()
        {
            mysort::insertionSort(m_testData.begin(), m_testData.end());
        }
    };

    class SelectionSort : public BaseTestPattern
    {
    public:
        explicit SelectionSort() : BaseTestPattern("[Selection Sort]") {}
        virtual void sort_impl()
        {
            mysort::selectionSort(m_testData.begin(), m_testData.end());
        }
    };

    class MergeSort : public BaseTestPattern
    {
    public:
        explicit MergeSort() : BaseTestPattern("[Merge Sort]") {}
    private:
        virtual void sort_impl() {
            mysort::mergeSort_arr(m_testData.begin(), m_testData.end());
        }
    };

    class QuickSort_Lomuto : public BaseTestPattern
    {
    public:
        explicit QuickSort_Lomuto() : BaseTestPattern("[Quick Sort] --Lomuto") {}
    private:
        virtual void sort_impl() {
            mysort::quickSort_Lomuto(m_testData.begin(), m_testData.end());
        }
    };

    class QuickSort_Lomuto_TailRecOpt : public BaseTestPattern
    {
    public:
        explicit QuickSort_Lomuto_TailRecOpt() : BaseTestPattern("[Quick Sort] --Lomuto, tail_recursion_opt") {}
    private:
        virtual void sort_impl() {
            mysort::quickSort_Lomuto_tailRec(m_testData.begin(), m_testData.end());
        }
    };

    class QuickSort_Lomuto_Rand : public BaseTestPattern
    {
    public:
        explicit QuickSort_Lomuto_Rand() : BaseTestPattern("[Quick Sort] --Lomuto, rand") {}
        virtual void sort_impl() {
            mysort::quickSort_Lomuto_rand(m_testData.begin(), m_testData.end());
        }
    };

    class QuickSort_Lomuto_Rand_Duplicated : public BaseTestPattern
    {
    public:
        explicit QuickSort_Lomuto_Rand_Duplicated() : BaseTestPattern("[Quick Sort] --Lomuto, rand, duplicated_opt") {}
        virtual void sort_impl() {
            mysort::quickSort_Lomuto_rand_duplicated(m_testData.begin(), m_testData.end());
        }
    };

    class QuickSort_Lomuto_Rand_Duplicated_Insertion : public BaseTestPattern
    {
    public:
        explicit QuickSort_Lomuto_Rand_Duplicated_Insertion() : BaseTestPattern("[Quick Sort] --Lomuto, rand, duplicated_opt, insertion_sort") {}
    private:
        virtual void sort_impl() {
            mysort::quickSort_Lomuto_rand_duplicated_insertion(m_testData.begin(), m_testData.end());
        }
    };

    class QuickSort_Hoare : public BaseTestPattern
    {
    public:
        explicit QuickSort_Hoare() : BaseTestPattern("[Quick Sort] --Hoare") {}
    private:
        virtual void sort_impl() {
            mysort::quickSort_Hoare(m_testData.begin(), m_testData.end());
        }
    };

    class QuickSort_Hoare_rand : public BaseTestPattern
    {
    public:
        explicit QuickSort_Hoare_rand() : BaseTestPattern("[Quick Sort] --Hoare, rand") {}
    private:
        virtual void sort_impl()
        {
            mysort::quickSort_Hoare_rand(m_testData.begin(), m_testData.end());
        }
    };

    class QuickSort_Hoare_insertion : public BaseTestPattern
    {
    public:
        explicit QuickSort_Hoare_insertion() : BaseTestPattern("[Quick Sort] --Hoare, rand, insertion_sort") {}
    private:
        virtual void sort_impl() {
            mysort::quickSort_Hoare_insertion(m_testData.begin(), m_testData.end());
        }
    };
}