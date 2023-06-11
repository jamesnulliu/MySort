#include "TestPatterns.hpp"

int main()
{
    std::vector<testPatterns::TEST_ELEMENT_TYPE> vec(1000, 9);
    ////testPatterns::generateData(&vec);
    testPatterns::generateData();
    testPatterns::bubble_sort();
    testPatterns::insertion_sort();
    testPatterns::selection_sort();
    testPatterns::merge_sort();
    testPatterns::quick_sort_Hoare();
    testPatterns::quick_sort_Hoare_rand();
    testPatterns::quick_sort_Hoare_rand_insertion();
    testPatterns::quick_sort_Lomuto();
    testPatterns::quick_sort_Lomuto_tailRecOpt();
    testPatterns::quick_sort_Lomuto_rand_duplicated();
    testPatterns::quick_sort_Lomuto_rand_duplicated_insertion();
}