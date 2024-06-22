#pragma once
#include <Yutils/Random.hpp>

namespace mysort
{
template <class _It, class _Pr>
    requires std::forward_iterator<_It>
_It midOfRandom3(_It rangeBegin, _It rangeEnd, _Pr comp)
{
    std::vector<uint64_t> vec = yutils::RandUniform<uint64_t>().generateVec(
        3, 0.0, (double) std::distance(rangeBegin, rangeEnd));

    _It first = std::next(rangeBegin, vec[0]), second = std::next(rangeBegin, vec[1]),
        third = std::next(rangeBegin, vec[2]);

    return (comp(*first, *second) && comp(*second, *third))  ? second
           : (comp(*second, *first) && comp(*first, *third)) ? first
                                                             : third;
}

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
}  // namespace mysort