/**
 * In this file we will provide an example of using your own data structure as the element type.
 * You should follow these steps to make your data structure acceptable by the test framework:
 *
 * 1. Define your data structure in a header file.
 *    Include this file in "MySort/TestPattern/DataConfig.hpp".
 *    Replace the `ELEMENT_TYPE` in "MySort/TestPattern/DataConfig.hpp" with your data structure.
 *    Your data structure must have the following operators:
 *    - operator=() (The rhs is the same type)
 *    - operator<() (The rhs is the same type)
 *    - operator>() (The rhs is the same type)
 *    - operator==() (The rhs is the same type)
 *
 * 2. Overload the `to_string()` function in the `std` namespace to convert your data structure to
 *    a string.
 *
 * 3. Specialize the `std::numeric_limits` template in the `std` namespace to provide the minimum
 *    and maximum values of your data structure.
 *
 */

#pragma once
#include <Yutils/Random.hpp>
#include <format>
#include <limits>
#include <string>

namespace testPatterns
{
struct ExampleStruct
{
public:
    using DataType = double;
    DataType data;
    std::size_t position;

public:
    ExampleStruct& operator=(const ExampleStruct& x)
    {
        data = x.data;
        position = x.position;
        return *this;
    }
    bool operator<(const ExampleStruct& x) const
    {
        return data < x.data;
    }
    bool operator>(const ExampleStruct& x) const
    {
        return data > x.data;
    }
    bool operator==(const ExampleStruct& x) const
    {
        return data == x.data;
    }
};
}  // namespace testPatterns

namespace std
{
inline string to_string(const testPatterns::ExampleStruct& x)
{
    return std::format("({:.3f}, {})", x.data, x.position);
}

template <>
class numeric_limits<testPatterns::ExampleStruct>
{
private:
    using ExampleStruct = testPatterns::ExampleStruct;

public:
    static constexpr ExampleStruct lowest() noexcept
    {
        return {std::numeric_limits<ExampleStruct::DataType>::lowest(), 0};
    }

    static constexpr ExampleStruct max() noexcept
    {
        return {std::numeric_limits<ExampleStruct::DataType>::max(), 0};
    }
};
}  // namespace std