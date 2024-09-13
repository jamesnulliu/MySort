/**
 * This file includes all the functions to generate test patterns for the sorting algorithms.
 * There are 6 types of generate methods, corresponding to 5 types of generate functions:
 *
 *   1. genNormalDistVec(): Generate a vector with elements following a normal distribution.
 *   2. genUniformDistVec(): Generate a vector with elements following a uniform distribution.
 *   3. genOrderedVec(): Generate a vector with elements in ascending order.
 *   4. genReverseOrderedVec(): Generate a vector with elements in descending order.
 *   5. genSameVec(): Generate a vector with the same elements.
 *   6. outerGenMethod(): Generate a vector with the same elements.
 *
 * If you want to generate a vector with a custom data structure, you should specialize those
 * functions.
 *
 * @note It is strongly recommended to specialize the functions IN THIS FILE. DO NOT SPECIALIZE
 *       THE FUNCTIONS IN DATA STRUCTURE HEADER FILES because cyclic dependencies may occur.
 */

#pragma once
#include <Yutils/Random.hpp>
#include <concepts>
#include <vector>

#include "MySort/Core/PreDefined.hpp"
#include "MySort/TestPattern/DataConfig.hpp"

namespace yutils::testPatterns
{
template <typename T>
std::vector<T> genNormalDistVec()
{
    if constexpr (std::is_arithmetic_v<T>) {
        return yutils::RandNormal<T>{}.generateVec(NUM_OF_ELEM_TO_GENERATE, ND_MEAN, ND_SIGMA);
    } else {
        mysort::globalLogger->warn(
            "The given type: {} is not supported. "
            "Generating the same elements for Normal Vec. "
            "It is recommended to specialize the function for the given type.",
            typeid(T).name());
        return std::vector<T>(NUM_OF_ELEM_TO_GENERATE);
    }
}

template <typename T>
std::vector<T> genUniformDistVec()
{
    if constexpr (std::is_arithmetic_v<T>) {
        return yutils::RandUniform<T>{}.generateVec(NUM_OF_ELEM_TO_GENERATE, UD_MIN, UD_MAX);
    } else {
        mysort::globalLogger->warn(
            "The given type: {} is not supported. "
            "Generating the same elements for Uniform Vec. "
            "It is recommended to specialize the function for the given type.",
            typeid(T).name());
        return std::vector<T>(NUM_OF_ELEM_TO_GENERATE);
    }
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
        mysort::globalLogger->warn(
            "The given type: {} is not arithmetic. "
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
        mysort::globalLogger->warn(
            "The given type: {} is not arithmetic. "
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

// =================================================================================================
// Specialization for std::string
// -------------------------------------------------------------------------------------------------
template <typename T>
    requires std::same_as<T, std::string>
std::vector<T> genNormalDistVec()
{
    std::vector<T> vec;
    auto normalDist = yutils::RandNormal<int>{};
    auto uniformDist = yutils::RandUniform<int>{};
    for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
        std::string str;
        std::size_t len = uniformDist.generate(MIN_STR_LEN, MAX_STR_LEN);
        for (std::size_t j = 0; j < len; ++j) {
            char ch = '!' + ::abs(normalDist.generate(ND_MEAN, ND_SIGMA)) % 93;
            str.push_back(ch);
        }
        vec.push_back(str);
    }
    return vec;
}

template <typename T>
    requires std::same_as<T, std::string>
std::vector<T> genUniformDistVec()
{
    std::vector<T> vec;
    auto uniformDist = yutils::RandUniform<int>{};
    for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
        std::string str;
        std::size_t len = uniformDist.generate(MIN_STR_LEN, MAX_STR_LEN);
        for (std::size_t j = 0; j < len; ++j) {
            char ch = '!' + uniformDist.generate(0, 93);
            str.push_back(ch);
        }
        vec.push_back(str);
    }
    return vec;
}

template <typename T>
    requires std::same_as<T, std::string>
std::vector<T> genOrderedVec()
{
    std::vector<T> vec;
    for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
        char ch = 'A';
        std::size_t num = i;
        vec.push_back(std::string(num, ch));
    }
    return vec;
}

template <typename T>
    requires std::same_as<T, std::string>
std::vector<T> genReverseOrderedVec()
{
    std::vector<T> vec;
    for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
        char ch = 'A';
        std::size_t num = NUM_OF_ELEM_TO_GENERATE - i;
        vec.push_back(std::string(num, ch));
    }
    return vec;
}
// =================================================================================================

// =================================================================================================
// Example: Specialization for ExampleStruct
// -------------------------------------------------------------------------------------------------
template <typename T>
    requires std::same_as<T, ExampleStruct>
std::vector<T> genNormalDistVec()
{
    std::vector<T> vec;
    auto normalDist = yutils::RandNormal<double>{};
    for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
        vec.emplace_back(normalDist.generate(ND_MEAN, ND_SIGMA), i);
    }
    return vec;
}

template <typename T>
    requires std::same_as<T, ExampleStruct>
std::vector<T> genUniformDistVec()
{
    std::vector<T> vec;
    auto uniformDist = yutils::RandUniform<double>{};
    for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
        vec.emplace_back(uniformDist.generate(UD_MIN, UD_MAX), i);
    }
    return vec;
}

template <typename T>
    requires std::same_as<T, ExampleStruct>
std::vector<T> genOrderedVec()
{
    std::vector<T> vec;
    for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
        vec.emplace_back(i, i);
    }
    return vec;
}

template <typename T>
    requires std::same_as<T, ExampleStruct>
std::vector<T> genReverseOrderedVec()
{
    std::vector<T> vec;
    for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
        vec.emplace_back(NUM_OF_ELEM_TO_GENERATE - i, i);
    }
    return vec;
}

template <typename T>
    requires std::same_as<T, ExampleStruct>
std::vector<T> genSameVec()
{
    std::vector<T> vec;
    for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
        vec.emplace_back(0, i);
    }
    return vec;
}

template <typename T>
    requires std::same_as<T, ExampleStruct>
inline std::vector<T> otherGenMethod()
{
    std::vector<T> vec;
    for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
        vec.emplace_back(0, i);
    }
    return vec;
}
// =================================================================================================
}  // namespace yutils::testPatterns