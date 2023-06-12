#pragma once
#include <vector>

namespace testPatterns {
    enum class GenMethod : uint8_t
    {
        NORMAL_DIST, // Normal distribution
        UNIFORM_DIST // Uniform distribution
    };

    // Change here if you want other test data ================================
    using TEST_ELEMENT_TYPE = int;
    constexpr uint16_t NUM_OF_ELEM_TO_GENERATE = 2000;
    constexpr GenMethod GENERATE_METHOD = GenMethod::UNIFORM_DIST;
    // ========================================================================

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