#pragma once

#include "BaseTestPattern.hpp"

#include "../Sort/BubbleSort.hpp"
#include "../Sort/InsertionSort.hpp"
#include "../Sort/MergeSort.hpp"
#include "../Sort/QuickSort.hpp"
#include "../Sort/SelectionSort.hpp"

namespace testPatterns
{
    class BubbleSort : public BaseTestPattern
    {
    public:
        explicit BubbleSort() : BaseTestPattern("[Bubble Sort]") {}
    private:
        virtual void sort_impl() {
            mysort::BubbleSort(m_testData.begin(), 0, m_testData.size() - 1);
        }
    };

    class BubbleSort_Stop : public BaseTestPattern
    {
    public:
        explicit BubbleSort_Stop() : BaseTestPattern("[Bubble Sort] --stop_in_time") {}
    private:
        virtual void sort_impl() {
            mysort::BubbleSort_Stop(m_testData.begin(), 0, m_testData.size() - 1);
        }
    };

    class BubbleSort_LastSwap : public BaseTestPattern
    {
    public:
        explicit BubbleSort_LastSwap() : BaseTestPattern("[Bubble Sort] --narrow the range of iteration") {}
    private:
        virtual void sort_impl() {
            mysort::BubbleSort_LastSwap(m_testData.begin(), 0, m_testData.size() - 1);
        }
    };

    class InsertionSort : public BaseTestPattern
    {
    public:
        explicit InsertionSort() : BaseTestPattern("[Insertion Sort]") {}
    private:
        virtual void sort_impl() {
            mysort::InsertionSort(m_testData.begin(), 0, m_testData.size() - 1);
        }
    };

    class SelectionSort : public BaseTestPattern
    {
    public:
        explicit SelectionSort() : BaseTestPattern("[Selection Sort]") {}
        virtual void sort_impl() {
            mysort::SelectionSort(m_testData.begin(), 0, m_testData.size() - 1);
        }
    };

    class MergeSort : public BaseTestPattern
    {
    public:
        explicit MergeSort() : BaseTestPattern("[Merge Sort]") {}
    private:
        virtual void sort_impl() {
            mysort::MergeSort(m_testData.begin(), 0, m_testData.size() - 1, testPatterns::MIN, testPatterns::MAX);
        }
    };

    class QuickSort_Lomuto : public BaseTestPattern
    {
    public:
        explicit QuickSort_Lomuto() : BaseTestPattern("[Quick Sort] --Lomuto") {}
    private:
        virtual void sort_impl() {
            mysort::QuickSort_Lomuto(m_testData.begin(), 0, m_testData.size() - 1);
        }
    };

    class QuickSort_Lomuto_TailRecOpt : public BaseTestPattern
    {
    public:
        explicit QuickSort_Lomuto_TailRecOpt() : BaseTestPattern("[Quick Sort] --Lomuto, tail_recursion_optimization") {}
    private:
        virtual void sort_impl() {
            mysort::QuickSort_Lomuto_TailRecOpt(m_testData.begin(), 0, m_testData.size() - 1);
        }
    };

    class QuickSort_Lomuto_Rand : public BaseTestPattern
    {
    public:
        explicit QuickSort_Lomuto_Rand() : BaseTestPattern("[Quick Sort] --Lomuto, rand") {}
        virtual void sort_impl() {
            mysort::QuickSort_Lomuto_Rand(m_testData.begin(), 0, m_testData.size() - 1);
        }
    };

    class QuickSort_Lomuto_Rand_Duplicated : public BaseTestPattern
    {
    public:
        explicit QuickSort_Lomuto_Rand_Duplicated() : BaseTestPattern("[Quick Sort] --Lomuto, rand, duplicated_opt") {}
        virtual void sort_impl() {
            mysort::QuickSort_Lomuto_Rand_Duplicated(m_testData.begin(), 0, m_testData.size() - 1);
        }
    };

    class QuickSort_Lomuto_Rand_Duplicated_Insertion : public BaseTestPattern
    {
    public:
        explicit QuickSort_Lomuto_Rand_Duplicated_Insertion() : BaseTestPattern("[Quick Sort] --Lomuto, rand, duplicated_opt, insertion_sort") {}
    private:
        virtual void sort_impl() {
            mysort::QuickSort_Lomuto_Rand_Duplicated_Insertion(m_testData.begin(), 0, m_testData.size() - 1);
        }
    };

    class QuickSort_Hoare : public BaseTestPattern
    {
    public:
        explicit QuickSort_Hoare() : BaseTestPattern("[Quick Sort] --Hoare") {}
    private:
        virtual void sort_impl() {
            mysort::QuickSort_Hoare(m_testData.begin(), 0, m_testData.size() - 1);
        }
    };

    class QuickSort_Hoare_Rand : public BaseTestPattern
    {
    public:
        explicit QuickSort_Hoare_Rand() : BaseTestPattern("[Quick Sort] --Hoare, rand") {}
    private:
        virtual void sort_impl() {
            mysort::QuickSort_Hoare_Rand(m_testData.begin(), 0, m_testData.size() - 1);
        }
    };

    class QuickSort_Hoare_Rand_Insertion : public BaseTestPattern
    {
    public:
        explicit QuickSort_Hoare_Rand_Insertion() : BaseTestPattern("[Quick Sort] --Hoare, rand, insertion_sort") {}
    private:
        virtual void sort_impl() {
            mysort::QuickSort_Hoare_Rand_Insertion(m_testData.begin(), 0, m_testData.size() - 1);
        }
    };
}