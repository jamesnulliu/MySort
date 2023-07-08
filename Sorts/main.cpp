#include "TestsPatterns/TestPatterns.hpp"
#include <forward_list>

int main() {
    std::forward_list<int>::iterator
        testPatterns::generateData();
    testPatterns::BubbleSort().test();
    testPatterns::BubbleSort_Stop().test();
    testPatterns::BubbleSort_LastSwap().test();
    testPatterns::InsertionSort().test();
    testPatterns::SelectionSort().test();
    testPatterns::MergeSort().test();
    testPatterns::quickSort_Lomuto().test();
    testPatterns::quickSort_Lomuto_tailRecOpt().test();
    testPatterns::QuickSort_Lomuto_Rand().test();
    testPatterns::quickSort_Lomuto_rand_duplicated().test();
    testPatterns::QuickSort_Lomuto_Rand_Duplicated_Insertion().test();
    testPatterns::quickSort_Hoare().test();
    testPatterns::QuickSort_Hoare_Rand().test();
    testPatterns::QuickSort_Hoare_Rand_Insertion().test();
}