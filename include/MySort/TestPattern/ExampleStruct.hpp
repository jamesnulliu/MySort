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
 *    - operator-() (The rhs is the same type)
 *    - operator+() (The rhs is the same type)
 *    - operator/() (The rhs is an integer)
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
    ExampleStruct operator-(const ExampleStruct& x) const
    {
        return {data - x.data, 0};
    }
    ExampleStruct operator+(const ExampleStruct& x) const
    {
        return {data + x.data, 0};
    }
    ExampleStruct operator/(int x) const
    {
        return {data / x, 0};
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

template <>
class DistributionVisualizer<testPatterns::ExampleStruct>
{
public:
    using _ValTy = testPatterns::ExampleStruct;
    explicit DistributionVisualizer() = default;
    DistributionVisualizer& operator=(const DistributionVisualizer&) = delete;

public:
    /**
     * @brief Visualizes the distribution of a vector of random numbers.
     *
     * @param randVec The vector of random numbers.
     * @param binNum The number of bins to divide the range of the random numbers.
     * @param maxStarNum The maximum number of stars to print in each bin.
     */
    void operator()(const std::vector<_ValTy>& randVec, const std::size_t binNum = 10,
                    const std::size_t maxStarNum = 15) const
    {
        if (randVec.empty())
            return;
        _ValTy minElem = *(std::min_element(randVec.begin(), randVec.end()));
        _ValTy maxElem = *(std::max_element(randVec.begin(), randVec.end()));
        double range = maxElem.data - minElem.data;

        if (range == 0) {
            std::cout << "All the elements are: " << maxElem.data << std::endl;
            return;
        }

        double average = 0.0;
        for (auto val : randVec) {
            average += val.data;
        }
        std::vector<std::size_t> bins(binNum);

        std::cout << std::format("min: {} max: {} average: {}\n", minElem.data, maxElem.data,
                                 average);

        for (const auto& val : randVec) {
            std::size_t bin =
                static_cast<std::size_t>(double(val.data - minElem.data) / range * binNum);
            if (bin == bins.size()) {
                bin -= 1;
            }
            ++bins[bin];
        }
        std::size_t maxS = *(std::max_element(bins.begin(), bins.end()));
        double resizer = double(maxS) / maxStarNum;
        for (auto& val : bins) {
            val = std::size_t(ceil(val / resizer));
        }
        for (std::size_t i = 0; i < bins.size(); ++i) {
            std::cout << i << ": ";
            for (std::size_t j = 0; j < bins[i]; ++j) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
        return;
    }
};

}  // namespace yutils