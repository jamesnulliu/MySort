#pragma once
#include <functional>

template<typename T, typename Compare = std::less<T>>
class CompareCounter {
public:
    CompareCounter(Compare comp = Compare()) : comp(comp) {}

    bool operator()(const T& a, const T& b) const {
        ++count;
        return comp(a, b);
    }

    std::size_t getCount() const {
        return count;
    }

    void resetCount() {
        count = 0;
    }

private:
    Compare comp;
    static uint64_t count;
};

template<typename T, typename Compare>
uint64_t CompareCounter<T, Compare>::count = 0;