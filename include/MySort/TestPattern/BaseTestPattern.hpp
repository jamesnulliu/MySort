#pragma once

#include <memory>

#include <Yutils/Random.hpp>
#include <Yutils/TimeCounter.hpp>

#include "MySort/Core/PreDefined.hpp"
#include "MySort/TestPattern/DataConfig.hpp"

namespace yutils::testPatterns
{

void generateData();

class BaseTestPattern
{
public:
    friend void generateData();

public:
    explicit BaseTestPattern(const std::string& name) : m_methodName(name), m_testData({})
    {
        if (_originData == nullptr || _sortedData == nullptr) {
            throw "[ERR] Call {generateData()} to generate some data first.";
        }
        m_testData = *_originData;
    }

    virtual ~BaseTestPattern(){};

public:
    void test()
    {
        mysort::globalLogger->critical("{}", m_methodName);
        yutils::TimeCounter tcounter = getTimeCounter();
        tcounter.init();
        tcounter.startCounting();
        sort_impl();
        tcounter.endCounting();
        if (m_testData == *_sortedData) {
            mysort::globalLogger->info("| Result: Correct");
        } else {
            mysort::globalLogger->info("| Result: Wrong");
        }
        mysort::globalLogger->info("| Time cost: {}ms", tcounter.msecond());
        mysort::globalLogger->info("| Compare Count: {}", count);
        mysort::globalLogger->info("| Original Data: {}", seqToString(*_originData, 5));
        mysort::globalLogger->info("| Expected Data: {}", seqToString(*_sortedData, 5));
        mysort::globalLogger->info("|   Sorted Data: {}", seqToString(m_testData, 5));
    }

protected:
    virtual void sort_impl() = 0;

    uint64_t count;

    static std::string seqToString(const CONTAINER_TYPE& seq, uint64_t maxLen = 20ULL)
    {
        std::string str;
        uint64_t cnt{0};
        for (auto e : seq) {
            if (cnt == maxLen) {
                str += "...";
                break;
            }
            str += std::to_string(e) + ", ";
            ++cnt;
        }
        return str;
    }

    yutils::TimeCounter& getTimeCounter() const
    {
        static yutils::TimeCounter counter;
        return counter;
    }

    static std::shared_ptr<CONTAINER_TYPE> _originData;
    static std::shared_ptr<CONTAINER_TYPE> _sortedData;
    std::string m_methodName;
    CONTAINER_TYPE m_testData;
};

}  // namespace yutils::testPatterns