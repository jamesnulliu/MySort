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
}  // namespace mysort