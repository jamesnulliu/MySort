#include "MySort/TestPattern/BaseTestPattern.hpp"
#include <algorithm>

namespace testPatterns
{
std::shared_ptr<CONTAINER_TYPE> BaseTestPattern::_originData;
std::shared_ptr<CONTAINER_TYPE> BaseTestPattern::_sortedData;

void generateData()
{
    BaseTestPattern::_originData = std::make_shared<CONTAINER_TYPE>();
    BaseTestPattern::_sortedData = std::make_shared<CONTAINER_TYPE>();

    auto& originData = *(BaseTestPattern::_originData);
    auto& sortedData = *(BaseTestPattern::_sortedData);
    std::vector<ELEMENT_TYPE> genData{};

    switch (GENERATE_METHOD) {
    case GenMethod::NORMAL_DIST: {
        genData = yutils::RandNormal<ELEMENT_TYPE>{}.generateVec(NUM_OF_ELEM_TO_GENERATE, ND_MEAN,
                                                                 ND_SIGMA);
        break;
    }
    case GenMethod::UNIFORM_DIST: {
        genData = yutils::RandUniform<ELEMENT_TYPE>{}.generateVec(NUM_OF_ELEM_TO_GENERATE, UD_MIN,
                                                                  UD_MAX);
        break;
    }
    case GenMethod::ORDERED: {
        for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
            genData.push_back((ELEMENT_TYPE) ((MIN + MAX) / 2) + (ELEMENT_TYPE) i);
        }
        break;
    }
    case GenMethod::REVERSE_ORDERED: {
        for (std::size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
            genData.push_back((ELEMENT_TYPE) ((MIN + MAX) / 2) - (ELEMENT_TYPE) i);
        }
        break;
    }
    case GenMethod::SAME: {
        genData = std::vector<ELEMENT_TYPE>(NUM_OF_ELEM_TO_GENERATE);
        break;
    }
    case GenMethod::OUTER: {
        genData = OuterGenMethod();
        break;
    }
    default:
        break;
    }

    std::cout << "===================================================" << std::endl;
    std::cout << "Data Brief Information:\n";
    // @note The type name is not human-readable in gcc.
    std::cout << "Container Type: " << typeid(CONTAINER_TYPE).name() << '\n';
    std::cout << "Element Type: " << typeid(ELEMENT_TYPE).name() << '\n';
    std::cout << "Element Number: " << NUM_OF_ELEM_TO_GENERATE << '\n';
    yutils::DistributionVisualizer<ELEMENT_TYPE> visualizer;
    visualizer(genData);
    std::cout << "===================================================" << std::endl;

    originData = constructContainer(genData);

    yutils::TimeCounter tcounter;
    tcounter.init();
    tcounter.startCounting();
    std::ranges::sort(genData, std::less<>{});
    tcounter.endCounting();

    sortedData = constructContainer(genData);
    YCRITICAL("std::sort (Benchmark for std::vector)");
    YTRACE("| Time cost: {}ms", tcounter.msecond());
}
}  // namespace testPatterns