#pragma once
#include <Yutils/Random.hpp>
#include <concepts>
#include <vector>

#include "MySort/TestPattern/DataConfig.hpp"

namespace testPatterns
{
template <typename T>
std::vector<T> genNormalDistVec()
{
    return yutils::RandNormal<ELEMENT_TYPE>{}.generateVec(NUM_OF_ELEM_TO_GENERATE, ND_MEAN,
                                                          ND_SIGMA);
}

template <typename T>
std::vector<T> genUniformDistVec()
{
    return yutils::RandUniform<ELEMENT_TYPE>{}.generateVec(NUM_OF_ELEM_TO_GENERATE, UD_MIN, UD_MAX);
}

template <typename T>
std::vector<T> genOrderedVec()
{
    if constexpr (std::is_arithmetic_v<T>) {
        std::vector<T> vec;
        for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
            vec.push_back(
                T((std::numeric_limits<T>::lowest() + std::numeric_limits<T>::max()) / 2) + T(i));
        }
        return vec;
    } else {
        YWARNING("The given type: {} is not arithmetic. "
                 "Generating the same elements for Ordered Vec. "
                 "It is recommended to specialize the function for the given type.",
                 typeid(T).name());
        std::vector<T> vec;
        for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
            vec.push_back(T());
        }
        return vec;
    }
}

template <typename T>
std::vector<T> genReverseOrderedVec()
{
    if constexpr (std::is_arithmetic_v<T>) {
        std::vector<T> vec;
        for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
            vec.push_back(
                T((std::numeric_limits<T>::lowest() + std::numeric_limits<T>::max()) / 2) - T(i));
        }
        return vec;
    } else {
        YWARNING("The given type: {} is not arithmetic. "
                 "Generating the same elements for Reverse Ordered Vec. "
                 "It is recommended to specialize the function for the given type.",
                 typeid(T).name());
        std::vector<T> vec;
        for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
            vec.push_back(T());
        }
        return vec;
    }
}

template <typename T>
std::vector<T> genSameVec()
{
    return std::vector<T>(NUM_OF_ELEM_TO_GENERATE);
}

template <typename T>
std::vector<T> outerGenMethod()
{
    std::vector<T> vec;
    for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
        vec.push_back(T());
    }
    return vec;
}

template <typename T>
    requires std::is_same_v<T, ExampleStruct>
inline std::vector<T> outerGenMethod()
{
    std::vector<T> vec;
    for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
        vec.push_back(T(0, i));
    }
    return vec;
}
}  // namespace testPatterns