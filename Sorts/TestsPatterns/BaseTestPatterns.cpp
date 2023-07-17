#include "BaseTestPattern.hpp"

namespace testPatterns {
    std::shared_ptr<CONTAINER_TYPE> BaseTestPattern::_originData;
    std::shared_ptr<CONTAINER_TYPE> BaseTestPattern::_sortedData;

    void generateData()
    {
        BaseTestPattern::_originData = std::make_shared<CONTAINER_TYPE>();
        BaseTestPattern::_sortedData = std::make_shared<CONTAINER_TYPE>();

        auto& originData = *(BaseTestPattern::_originData);
        auto& sortedData = *(BaseTestPattern::_sortedData);
        std::vector<ELEMENT_TYPE> genData{};

        switch (GENERATE_METHOD)
        {
        case GenMethod::NORMAL_DIST: {
            genData =
                Rand_Normal<ELEMENT_TYPE>{}.generateVec(NUM_OF_ELEM_TO_GENERATE, ND_MEAN, ND_SIGMA);
            break;
        }
        case GenMethod::UNIFORM_DIST: {
            genData =
                Rand_Uniform<ELEMENT_TYPE>{}.generateVec(NUM_OF_ELEM_TO_GENERATE, UD_MIN, UD_MAX);
            break;
        }
        case GenMethod::ORDERED: {
            for (size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
                genData.push_back((ELEMENT_TYPE)((MIN + MAX) / 2) + (ELEMENT_TYPE)i);
            }
            break;
        }
        case GenMethod::REVERSE_ORDERED: {
            for (size_t i = 0; i < NUM_OF_ELEM_TO_GENERATE; ++i) {
                genData.push_back((ELEMENT_TYPE)((MIN + MAX) / 2) - (ELEMENT_TYPE)i);
            }
            break;
        }
        case GenMethod::SAME: {
            genData =
                std::vector<ELEMENT_TYPE>(NUM_OF_ELEM_TO_GENERATE);
            break;
        }
        case GenMethod::OUTER: {
            ////throw "[ERR] Write some codes here to assign a sequence to {originData}";
            genData = { 10, 11 };
            break;
        }
        default:
            break;
        }

        std::cout << "===================================================" << std::endl;
        std::cout << "Data Brief Information:\n";
        DistributionVisualizer<ELEMENT_TYPE> visualizer;
        visualizer(genData);
        std::cout << "===================================================" << std::endl;

        originData = constructContainer(genData);

        TimeCounter tcounter;
        tcounter.init();
        tcounter.startCounting();
        std::ranges::sort(genData);
        tcounter.endCounting();

        sortedData = constructContainer(genData);
        std::cout << "[std::sort]\n" << "  Time cost: " << tcounter.msecond() << "ms" << std::endl;
    }
}