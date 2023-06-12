#pragma once
#include <cstdint>

namespace testPatterns {
    enum class GenMethod : uint8_t
    {
        NORMAL_DIST,      // Normal distribution
        UNIFORM_DIST,     // Uniform distribution
        ORDERED,          // Ordered sequence
        REVERSE_ORDERED,  // Reverse-ordered sequence
        SAME,             // All elements are the same
        OUTER             // Outer created data
    };

    // Change here if you want different test data ============================
    using ELEMENT_TYPE = double; // The element type of the testing sequence

    constexpr uint16_t NUM_OF_ELEM_TO_GENERATE = 100000;
    constexpr GenMethod GENERATE_METHOD = GenMethod::NORMAL_DIST;

    // Normal distribution params
    constexpr double ND_MEAN = 0.0;
    constexpr double ND_SIGMA = 100.0;

    // Uniform distribution params
    constexpr double UD_MIN = -1000;
    constexpr double UD_MAX = 1000;
    // ========================================================================
}