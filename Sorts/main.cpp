#include "TestsPatterns/TestPatterns.hpp"
#include "DataConfig.hpp"
#include <forward_list>

testPatterns::CONTAINER_TYPE testPatterns::constructContainer(const std::vector<testPatterns::ELEMENT_TYPE>& vec)
{
    return testPatterns::CONTAINER_TYPE(vec.begin(), vec.end());
}

int main() {
    testPatterns::generateData();
    ////testPatterns::BubbleSort().test();  // Pass
    ////testPatterns::BubbleSort_Stop().test();  // Pass
    ////testPatterns::BubbleSort_NarrowBoundary().test();  //Pass
    ////testPatterns::InsertionSort().test();  // Pass
    ////testPatterns::SelectionSort().test();  // Pass
    ////testPatterns::MergeSort().test();  // Pass
    testPatterns::QuickSort_Lomuto().test();  // Pass
    testPatterns::QuickSort_Lomuto_TailRecOpt().test();  // Pass
    testPatterns::QuickSort_Lomuto_Rand().test();  // Pass
    testPatterns::QuickSort_Lomuto_Rand_Duplicated().test();
    testPatterns::QuickSort_Lomuto_Rand_Duplicated_Insertion().test();
    testPatterns::QuickSort_Hoare().test();
    testPatterns::QuickSort_Hoare_rand().test();
    testPatterns::QuickSort_Hoare_insertion().test();
}