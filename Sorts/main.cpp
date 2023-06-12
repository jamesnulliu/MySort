#include "Tests/TestPatterns.hpp"
int main()
{
    testPatterns::generateData();
    testPatterns::BubbleSort().test();
    testPatterns::BubbleSort_Stop().test();
    testPatterns::InsertionSort().test();
    testPatterns::SelectionSort().test();
    testPatterns::MergeSort().test();
    testPatterns::QuickSort_Lomuto().test();
    testPatterns::QuickSort_Lomuto_TailRecOpt().test();
    // Remain Fix ¡ý
    ////testPatterns::QuickSort_Lomuto_Rand().test();
    testPatterns::QuickSort_Lomuto_Rand_Duplicated().test();
    testPatterns::QuickSort_Lomuto_Rand_Duplicated_Insertion().test();
    testPatterns::QuickSort_Hoare().test();
    testPatterns::QuickSort_Hoare_Rand().test();
    testPatterns::QuickSort_Hoare_Rand_Insertion().test();
}