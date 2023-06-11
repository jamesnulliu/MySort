#pragma once
#include <climits>
#include <vector>

namespace testPatterns {
    using TEST_ELEMENT_TYPE = int;

    void generateData(std::vector<TEST_ELEMENT_TYPE>* dataPtr = nullptr);
    void bubble_sort();
    void insertion_sort();
    void selection_sort();
    void merge_sort();
    void quick_sort_Hoare();
    void quick_sort_Hoare_rand();
    void quick_sort_Hoare_rand_insertion();
    void quick_sort_Lomuto();
    void quick_sort_Lomuto_tailRecOpt();
    void quick_sort_Lomuto_rand();
    void quick_sort_Lomuto_rand_duplicated();
    void quick_sort_Lomuto_rand_duplicated_insertion();
}