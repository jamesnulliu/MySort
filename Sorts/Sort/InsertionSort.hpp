#pragma once
#include "PreDefined.hpp"

#include <algorithm>

namespace mysort {
    template<class _It, class _Pr = std::less<void>>
    void InsertionSort(_It seq, indext first, indext last, const _Pr& comp = {})
    {
        for (indext j = first + 1; j <= last; ++j) {
            auto key = *(seq + j);
            indext i = j - 1;
            // The while-loop move the consecutive subseq whose elems are larger than {key}
            // | 1 position forward to overlap {key}'s position:
            // As a result, {seq[first : j-1]} must be already sorted.
            while (i >= first && !comp(*(seq + i), key)) {
                *(seq + 1 + i) = *(seq + i);
                --i;
            }
            // Insert {key} to the appropriate position:
            *(seq + 1 + i) = key;
        }
    }
}