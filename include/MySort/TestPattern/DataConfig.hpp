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

using ELEMENT_TYPE = int;
using CONTAINER_TYPE = std::forward_list<ELEMENT_TYPE>;

constexpr auto MIN = std::numeric_limits<testPatterns::ELEMENT_TYPE>::lowest();
constexpr auto MAX = std::numeric_limits<testPatterns::ELEMENT_TYPE>::max();

// constexpr std::size_t NUM_OF_ELEM_TO_GENERATE = 40000ULL;
extern std::size_t NUM_OF_ELEM_TO_GENERATE;
constexpr GenMethod GENERATE_METHOD = GenMethod::NORMAL_DIST;

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
}  // namespace testPatterns
