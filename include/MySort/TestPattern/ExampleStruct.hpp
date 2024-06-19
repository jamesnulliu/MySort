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
 *    - operator==() (The rhs is the same type)
 * 
 * 2. Overload the `to_string()` function in the `std` namespace to convert your data structure to 
 *    a string.
 * 
 * 3. Specialize the `std::numeric_limits` template in the `std` namespace to provide the minimum
 *    and maximum values of your data structure.
 * 
 * 4. Specialize the `yutils::RandUniform` and `yutils::RandNormal` templates in the `yutils`.
 *    After specialization, the static members `_rd`, `m_engine`, and `m_distribution` must be 
 *    defined in a source file instead of a header file.
 */

#pragma once
#include <format>
#include <limits>
#include <string>
#include <Yutils/Random.hpp>

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
    return std::format("({}, {})", x.data, x.position);
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

namespace yutils
{

template <>
class RandUniform<testPatterns::ExampleStruct>
{
public:
    using _ValTy = testPatterns::ExampleStruct;
    explicit RandUniform() = default;
    RandUniform& operator()(const RandUniform&) = delete;

public:
    inline _ValTy operator()(double min, double max) const
    {
        if (m_distribution == nullptr || m_distribution->min() != min ||
            m_distribution->max() != max) {
            m_distribution = new std::uniform_real_distribution<double>(min, max);
        }
        return _ValTy(m_distribution->operator()(m_engine), 0);
    }

    inline _ValTy operator()() const
    {
        return _ValTy(m_distribution->operator()(m_engine), 0);
    }

    inline void setParams(double min, double max) const
    {
        if (m_distribution == nullptr || m_distribution->min() != min ||
            m_distribution->max() != max) {
            m_distribution = new std::uniform_real_distribution<double>(min, max);
        }
    }

    std::vector<_ValTy> generateVec(std::size_t size, double min, double max,
                                    const std::string& saveLocation = "") const
    {
        std::vector<_ValTy> vec;
        std::uniform_real_distribution<double> distribution(min, max);
        std::ofstream outFile(saveLocation);
        for (std::size_t i = 0; i < size; ++i) {
            vec.emplace_back(distribution(m_engine), i);
            if (outFile.is_open()) {
                outFile << vec.back().data << ",";
            }
        }
        if (outFile.is_open()) {
            outFile.seekp(-1, std::ios_base::end);
            outFile.put(' ');
            outFile.close();
        }
        return vec;
    }

private:
    // These static members are defined in "src/TestPattern/ExampleStruct.cpp".
    static std::random_device _rd;
    static thread_local std::default_random_engine m_engine;
    static std::uniform_real_distribution<double>* m_distribution;
};

template <>
class RandNormal<testPatterns::ExampleStruct>
{
public:
    using _ValTy = testPatterns::ExampleStruct;
    explicit RandNormal() = default;
    RandNormal& operator()(const RandNormal&) = delete;

public:
    inline _ValTy operator()(double mean, double stddev) const
    {
        if (m_distribution == nullptr || m_distribution->mean() != mean ||
            m_distribution->stddev() != stddev) {
            m_distribution = new std::normal_distribution<double>(mean, stddev);
        }
        return _ValTy(m_distribution->operator()(m_engine), 0);
    }

    std::vector<_ValTy> generateVec(std::size_t size, double mean, double stddev,
                                    const std::string& saveLocation = "") const
    {
        std::vector<_ValTy> vec;
        std::normal_distribution<double> distribution(mean, stddev);
        std::ofstream outFile(saveLocation);
        for (std::size_t i = 0; i < size; ++i) {
            vec.emplace_back(distribution(m_engine), i);
            if (outFile.is_open()) {
                outFile << vec.back().data << ",";
            }
        }
        if (outFile.is_open()) {
            outFile.seekp(-1, std::ios_base::end);
            outFile.put(' ');
            outFile.close();
        }
        return vec;
    }

private:
    // These static members are defined in "src/TestPattern/ExampleStruct.cpp".
    static std::random_device _rd;
    static thread_local std::default_random_engine m_engine;
    static std::normal_distribution<double>* m_distribution;
};
}  // namespace yutils