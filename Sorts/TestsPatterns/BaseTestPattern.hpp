#pragma once
#include "../Tools/TimeCounter.hpp"
#include "../Tools/Random.hpp"
#include "../DataConfig.hpp"

#include <vector>
#include <memory>

namespace testPatterns {
    void generateData();

    class BaseTestPattern
    {
        friend void generateData();

    public:
        explicit BaseTestPattern(const std::string name)
            : m_methodName(name), m_testData({})
        {
            if (_originData == nullptr || _sortedData == nullptr) {
                throw "[ERR] Call {generateData()} to generate some data first.";
            }
            m_testData = *_originData;
        }

        virtual ~BaseTestPattern() {};

    public:
        void test()
        {
            TimeCounter tcounter = getTimeCounter();
            tcounter.init();
            tcounter.startCounting();
            sort_impl();
            tcounter.endCounting();
            std::cout << m_methodName << '\n' << "  Time cost: " << tcounter.msecond() << "ms" << std::endl;
            std::cout << "  Result: " << ((m_testData == *_sortedData) ? "Correct" : "Wrong") << std::endl;
        }

    protected:
        virtual void sort_impl() = 0;

        TimeCounter& getTimeCounter() const
        {
            static TimeCounter counter;
            return counter;
        }

        static std::shared_ptr<std::vector<ELEMENT_TYPE>> _originData;
        static std::shared_ptr<std::vector<ELEMENT_TYPE>> _sortedData;
        std::string m_methodName;
        std::vector<ELEMENT_TYPE> m_testData;
    };
}