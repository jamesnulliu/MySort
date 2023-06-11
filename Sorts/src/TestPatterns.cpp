#include "../Tools/Random.hpp"
#include "../Tools/TimeCounter.hpp"

#include "../Sort/BubbleSort.hpp"
#include "../Sort/InsertionSort.hpp"
#include "../Sort/MergeSort.hpp"
#include "../Sort/QuickSort.hpp"
#include "../Sort/SelectionSort.hpp"
#include "TestPatterns.hpp"

#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <functional>

namespace testPatterns {
    constexpr auto MIN = std::numeric_limits<TEST_ELEMENT_TYPE>::lowest();
    constexpr auto MAX = std::numeric_limits<TEST_ELEMENT_TYPE>::max();

    std::vector<TEST_ELEMENT_TYPE> originData, sortedData;
    bool GENERATED = false;

    TimeCounter counter;
    std::vector<std::vector<TEST_ELEMENT_TYPE>> testGroup;

    void generateData(std::vector<TEST_ELEMENT_TYPE>* dataPtr)
    {
        if (dataPtr != nullptr) {
            originData = *dataPtr;
        } else {
            originData = Rand_Normal<TEST_ELEMENT_TYPE>{}.generateVec(2000, 0, 10);
            ////originData = Rand_Uniform<TEST_ELEMENT_TYPE>{}.generateVec(2000, -1000, 1000);
        }
        DistributeVisualizer<TEST_ELEMENT_TYPE>{}(originData);
        testGroup = std::vector<decltype(originData)>(15, originData);
        sortedData = originData;
        counter.init();
        counter.startCounting();
        std::ranges::sort(sortedData);
        counter.endCounting();
        std::cout << "[std::sort]\n"
            << " >>> Time cost: " << counter.msecond() << "ms" << std::endl;
        GENERATED = true;
    }

    void bubble_sort()
    {
        if (!GENERATED) throw "[ERR] Use {generateData()} to sort {sortedData} first!";
        counter.init();
        counter.startCounting();
        mysort::BubbleSort(testGroup[0].begin(), 0, testGroup[0].size() - 1);
        counter.endCounting();
        bool flag = true;
        for (mysort::indext i = 0; i < (mysort::sizet)sortedData.size(); ++i) {
            if (testGroup[0][i] != sortedData[i]) {
                flag = false;
            }
        }
        std::cout << "[Bubble Sort]\n"
            << " >>> Time cost: " << counter.msecond() << "ms\n"
            << " >>> Result: " << (flag ? "Correct" : "Wrong") << std::endl;
    }

    void insertion_sort()
    {
        if (!GENERATED) throw "[ERR] Use {generateData()} to sort {sortedData} first!";
        counter.init();
        counter.startCounting();
        mysort::InsertionSort(testGroup[1].begin(), 0, testGroup[1].size() - 1);
        counter.endCounting();
        bool flag = true;
        for (mysort::indext i = 0; i < (mysort::sizet)sortedData.size(); ++i) {
            if (testGroup[1][i] != sortedData[i]) {
                flag = false;
            }
        }
        std::cout << "[Insertion Sort]\n"
            << " >>> Time cost: " << counter.msecond() << "ms\n"
            << " >>> Result: " << (flag ? "Correct" : "Wrong") << std::endl;
    }

    void selection_sort()
    {
        if (!GENERATED) throw "[ERR] Use {generateData()} to sort {sortedData} first!";
        counter.init();
        counter.startCounting();
        mysort::SelectionSort(testGroup[2].begin(), 0, testGroup[2].size() - 1);
        counter.endCounting();
        bool flag = true;
        for (mysort::indext i = 0; i < (mysort::sizet)sortedData.size(); ++i) {
            if (testGroup[2][i] != sortedData[i]) {
                flag = false;
            }
        }
        std::cout << "[Selection Sort]\n"
            << " >>> Time cost: " << counter.msecond() << "ms\n"
            << " >>> Result: " << (flag ? "Correct" : "Wrong") << std::endl;
    }

    void merge_sort()
    {
        if (!GENERATED) throw "[ERR] Use {generateData()} to sort {sortedData} first!";
        counter.init();
        counter.startCounting();
        mysort::MergeSort(testGroup[3].begin(), 0, testGroup[3].size() - 1, MIN, MAX);
        counter.endCounting();
        bool flag = true;
        for (mysort::indext i = 0; i < (mysort::sizet)sortedData.size(); ++i) {
            if (testGroup[3][i] != sortedData[i]) {
                flag = false;
            }
        }
        std::cout << "[Merge Sort]\n"
            << " >>> Time cost: " << counter.msecond() << "ms\n"
            << "Result: " << (flag ? "Correct" : "Wrong") << std::endl;
    }

    void quick_sort_Hoare()
    {
        if (!GENERATED) throw "[ERR] Use {generateData()} to sort {sortedData} first!";
        counter.init();
        counter.startCounting();
        mysort::QuickSort_Hoare(testGroup[4].begin(), 0, testGroup[4].size() - 1);
        counter.endCounting();
        bool flag = true;
        for (mysort::indext i = 0; i < (mysort::sizet)sortedData.size(); ++i) {
            if (testGroup[4][i] != sortedData[i]) {
                flag = false;
            }
        }
        std::cout << "[Quick Sort]\n -by Hoare\n"
            << " >>> Time cost: " << counter.msecond() << "ms\n"
            << " >>> Result: " << (flag ? "Correct" : "Wrong") << std::endl;
    }

    void quick_sort_Hoare_rand()
    {
        if (!GENERATED) throw "[ERR] Use {generateData()} to sort {sortedData} first!";
        counter.init();
        counter.startCounting();
        mysort::QuickSort_Hoare_rand(testGroup[5].begin(), 0, testGroup[5].size() - 1);
        counter.endCounting();
        bool flag = true;
        for (mysort::indext i = 0; i < (mysort::sizet)sortedData.size(); ++i) {
            if (testGroup[5][i] != sortedData[i]) {
                flag = false;
            }
        }
        std::cout << "[Quick Sort]\n -by Hoare\n -randomly choose piovt\n"
            << " >>> Time cost: " << counter.msecond() << "ms\n"
            << " >>> Result: " << (flag ? "Correct" : "Wrong")
            << std::endl;
    }

    void quick_sort_Hoare_rand_insertion()
    {
        if (!GENERATED) throw "[ERR] Use {generateData()} to sort {sortedData} first!";
        counter.init();
        counter.startCounting();
        mysort::QuickSort_Hoare_rand_insertion(testGroup[6].begin(), 0, testGroup[6].size() - 1);
        counter.endCounting();
        bool flag = true;
        for (mysort::indext i = 0; i < (mysort::sizet)sortedData.size(); ++i) {
            if (testGroup[6][i] != sortedData[i]) {
                flag = false;
            }
        }
        std::cout << "[Quick Sort]\n -by Hoare\n -randomly choose piovt\n -use insertion sort if less than 10 elements\n"
            << " >>> Time cost: " << counter.msecond() << "ms" << std::endl;
        std::cout << " >>> Result: " << (flag ? "Correct" : "Wrong") << std::endl;
    }

    void quick_sort_Lomuto()
    {
        if (!GENERATED) throw "[ERR] Use {generateData()} to sort {sortedData} first!";
        counter.init();
        counter.startCounting();
        mysort::QuickSort_Lomuto(testGroup[7].begin(), 0, testGroup[7].size() - 1);
        counter.endCounting();
        bool flag = true;
        for (mysort::indext i = 0; i < (mysort::sizet)sortedData.size(); ++i) {
            if (testGroup[7][i] != sortedData[i]) {
                flag = false;
            }
        }
        std::cout << "[Quick Sort]\n -by Lomuto\n"
            << " >>> Time cost: " << counter.msecond() << "ms" << std::endl;
        std::cout << " >>> Result: " << (flag ? "Correct" : "Wrong") << std::endl;
    }

    void quick_sort_Lomuto_tailRecOpt()
    {
        if (!GENERATED) throw "[ERR] Use {generateData()} to sort {sortedData} first!";
        counter.init();
        counter.startCounting();
        mysort::QuickSort_TailRecOpt_Lomuto(testGroup[8].begin(), 0, testGroup[8].size() - 1);
        counter.endCounting();
        bool flag = true;
        for (mysort::indext i = 0; i < (mysort::sizet)sortedData.size(); ++i) {
            if (testGroup[8][i] != sortedData[i]) {
                flag = false;
            }
        }
        std::cout << "[Quick Sort]\n -by Lomuto\n -tail recersive optimization\n"
            << " >>> Time cost: " << counter.msecond() << "ms" << std::endl;
        std::cout << " >>> Result: " << (flag ? "Correct" : "Wrong") << std::endl;
    }

    void quick_sort_Lomuto_rand()
    {
        if (!GENERATED) throw "[ERR] Use {generateData()} to sort {sortedData} first!";
        counter.init();
        counter.startCounting();
        mysort::QuickSort_Lomuto_rand(testGroup[9].begin(), 0, testGroup[9].size() - 1);
        counter.endCounting();
        bool flag = true;
        for (mysort::indext i = 0; i < (mysort::sizet)sortedData.size(); ++i) {
            if (testGroup[9][i] != sortedData[i]) {
                flag = false;
            }
        }
        std::cout << "[Quick Sort]\n -by Lomuto\n -ramdomly choose pivot\n"
            << " >>> Time cost: " << counter.msecond() << "ms" << std::endl;
        std::cout << " >>> Result: " << (flag ? "Correct" : "Wrong") << std::endl;
    }

    void quick_sort_Lomuto_rand_duplicated()
    {
        if (!GENERATED) throw "[ERR] Use {generateData()} to sort {sortedData} first!";
        counter.init();
        counter.startCounting();
        mysort::QuickSort_Lomuto_rand_duplicated(testGroup[10].begin(), 0, testGroup[10].size() - 1);
        counter.endCounting();
        bool flag = true;
        for (mysort::indext i = 0; i < (mysort::sizet)sortedData.size(); ++i) {
            if (testGroup[10][i] != sortedData[i]) {
                flag = false;
            }
        }
        std::cout << "[Quick Sort]\n -by Lomuto\n -ramdomly choose pivot\n -handle duplicated sequence\n"
            << " >>> Time cost: " << counter.msecond() << "ms" << std::endl;
        std::cout << " >>> Result: " << (flag ? "Correct" : "Wrong") << std::endl;
    }

    void quick_sort_Lomuto_rand_duplicated_insertion()
    {
        if (!GENERATED) throw "[ERR] Use {generateData()} to sort {sortedData} first!";
        counter.init();
        counter.startCounting();
        mysort::QuickSort_Lomuto_rand_duplicated_insertion(testGroup[11].begin(), 0, testGroup[11].size() - 1);
        counter.endCounting();
        bool flag = true;
        for (mysort::indext i = 0; i < (mysort::sizet)sortedData.size(); ++i) {
            if (testGroup[11][i] != sortedData[i]) {
                flag = false;
            }
        }
        std::cout << "[Quick Sort]\n -by Lomuto\n -ramdomly choose pivot\n -handle duplicated sequence\n -use insertion sort if less than 10 elements\n"
            << " >>> Time cost: " << counter.msecond() << "ms" << std::endl;
        std::cout << " >>> Result: " << (flag ? "Correct" : "Wrong") << std::endl;
    }
}