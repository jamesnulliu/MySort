#pragma once
#include "../Tools/TimeCounter.hpp"
#include "../Tools/Random.hpp"
#include "../DataConfig.hpp"

#include <vector>
#include <memory>
#include <iostream>

namespace testPatterns {
    void generateData();

    class BaseTestPattern
    {
    public:
        friend void generateData();

    public:
        explicit BaseTestPattern(const std::string& name)
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

        static void printOriginSeq() { printSeq(*_originData); }
        static void printSortedSeq() { printSeq(*_sortedData); }

        static void printSeq(const CONTAINER_TYPE& seq)
        {
            uint64_t cnt{ 0 };
            for (auto e : seq) {
                if (cnt == 20ULL) {
                    std::cout << "\b\b...";
                    break;
                }
                std::cout << e << ", ";
                ++cnt;
            }
            std::cout << std::endl;
        }

        TimeCounter& getTimeCounter() const
        {
            static TimeCounter counter;
            return counter;
        }

        static std::shared_ptr<CONTAINER_TYPE> _originData;
        static std::shared_ptr<CONTAINER_TYPE> _sortedData;
        std::string m_methodName;
        CONTAINER_TYPE m_testData;
    };
}