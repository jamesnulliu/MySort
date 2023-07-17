#pragma once
#include <ctime>
#include <string>
#include <numeric>
#include <vector>

class TimeCounter
{
    static const clock_t msPerSec = CLOCKS_PER_SEC;

public:
    explicit TimeCounter() = default;
    TimeCounter& operator=(const TimeCounter&) = delete;
    ~TimeCounter() = default;

public:
    clock_t getStartingTime() const { return time1; }

    clock_t getEndingTime() const { return time2; }

    // Clear the content in {resultList}.
    void init()
    {
        resultList.clear();
    }

    // Start counting.
    void startCounting()
    {
        time1 = clock();
        whetherStart = true;
    }

    // Stop counting and store duration into {resultList}.
    void endCounting()
    {
        if (whetherStart == false) {
            throw "End Counting before starting.";
        }
        time2 = clock();
        resultList.push_back(time2 - time1);
        whetherStart = false;
    }

    // Return average duration in millisecond.
    long msecond()
    {
        return calAverage();
    }

    // Return average duration in second.
    double second()
    {
        return static_cast<double>(calAverage()) / msPerSec;
    }

private:
    // @brief Return average duration in {resultList}.
    clock_t calAverage() {
        return clock_t(std::accumulate(resultList.begin(), resultList.end(), 0L) / resultList.size());
    }
    bool whetherStart = false;
    clock_t time1 = 0L;
    clock_t time2 = 0L;
    std::vector<clock_t> resultList = {};
};