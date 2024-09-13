#pragma once
#include <cstdint>
#include <forward_list>
#include <iostream>
#include <limits>
#include <list>
#include <vector>

// Check this example struct if you want to define your own element type.
#include "MySort/TestPattern/ExampleStruct.hpp"

namespace yutils::testPatterns
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

// constexpr std::size_t NUM_OF_ELEM_TO_GENERATE = 40000ULL;
extern std::size_t NUM_OF_ELEM_TO_GENERATE;
constexpr GenMethod GENERATE_METHOD = GenMethod::NORMAL_DIST;

// Normal distribution params
constexpr double ND_MEAN = 0.0;
constexpr double ND_SIGMA = 50.0;

// Uniform distribution params
constexpr double UD_MIN = -1000;
constexpr double UD_MAX = 1000;

constexpr std::size_t MIN_STR_LEN = 8;   // Minimum string length
constexpr std::size_t MAX_STR_LEN = 16;  // Maximum string length

/**
 * @brief  Construct a container from a vector.
 *
 * @param vec  The vector to be converted to a container.
 * @return CONTAINER_TYPE
 * @note  Change this function if your container type has a different way to construct from a
 *        vector. In most cases, you can leave it as it is.
 */
inline CONTAINER_TYPE constructContainer(const std::vector<testPatterns::ELEMENT_TYPE>& vec)
{
    return testPatterns::CONTAINER_TYPE(vec.begin(), vec.end());
}
}  // namespace yutils::testPatterns

// =================================================================================================
// Make std::string acceptable by the test framework
// -------------------------------------------------------------------------------------------------
namespace std
{
inline std::string to_string(const std::string& x)
{
    return x;
}

/**
 * @brief  Specialize the `std::numeric_limits` template to provide the minimum and maximum values
 *         of `std::string`.
 *
 * @note  This is dangerous because the `std::string` has no minimum and maximum values.
 *        Comment out this specialization if you don't want to use `std::string` as the element
 *        type.
 */
template <>
class numeric_limits<std::string>
{
public:
    static constexpr std::string lowest() noexcept
    {
        return "";
    }
    static constexpr std::string max() noexcept
    {
        return std::string(yutils::testPatterns::MAX_STR_LEN + 1, char(127));
    }
};
}  // namespace std
// =================================================================================================
