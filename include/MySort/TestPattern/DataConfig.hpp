#pragma once
#include <cstdint>
#include <forward_list>
#include <iostream>
#include <limits>
#include <list>
#include <vector>

// Check this example struct if you want to define your own element type.
#include "MySort/TestPattern/ExampleStruct.hpp"

namespace testPatterns
{
enum class GenMethod : uint8_t
{
    NORMAL_DIST,      // Normal distribution
    UNIFORM_DIST,     // Uniform distribution
    ORDERED,          // Ordered sequence
    REVERSE_ORDERED,  // Reverse-ordered sequence
    SAME,             // All elements are the same
    OUTER             // Outer created data
};

using ELEMENT_TYPE = ExampleStruct;
using CONTAINER_TYPE = std::vector<ELEMENT_TYPE>;

constexpr auto MIN = std::numeric_limits<ELEMENT_TYPE>::lowest();
constexpr auto MAX = std::numeric_limits<ELEMENT_TYPE>::max();

// constexpr std::size_t NUM_OF_ELEM_TO_GENERATE = 40000ULL;
extern std::size_t NUM_OF_ELEM_TO_GENERATE;
constexpr GenMethod GENERATE_METHOD = GenMethod::OUTER;

// Normal distribution params
constexpr double ND_MEAN = 0.0;
constexpr double ND_SIGMA = 50.0;

// Uniform distribution params
constexpr double UD_MIN = -1000;
constexpr double UD_MAX = 1000;

// Change this function if your container has a specific way to construct with a vector.
inline CONTAINER_TYPE constructContainer(const std::vector<testPatterns::ELEMENT_TYPE>& vec)
{
    return testPatterns::CONTAINER_TYPE(vec.begin(), vec.end());
}

/**
 * @brief  Generate data in a specific way.
 * @note  This function is used when `GENERATE_METHOD` is `GenMethod::OUTER`.
 *        If `GENERATE_METHOD` is not `GenMethod::OUTER`, you may need to comment out the function 
 *        body to pass the compilation check.
 * @return std::vector<ELEMENT_TYPE> 
 */
inline std::vector<ELEMENT_TYPE> OuterGenMethod()
{
    std::vector<ELEMENT_TYPE> vec;
    for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
        vec.emplace_back(0, i);
    }
    return vec;
}
}  // namespace testPatterns
