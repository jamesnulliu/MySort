#pragma once
#include "PreDefined.hpp"

#include <algorithm>

namespace mysort {
    template<class _RandIt, class _Pr = std::less<void>>
    void SelectionSort(_RandIt seq, indext first, indext last, const _Pr& comp = {}) {
        for (indext i = first; i < last; ++i) {
            // The index of the smallest (or largest) elem in {seq[i : last-1]} (should be)
            indext selected = i;
            // Following for-loop actually make {selected} the smallest (or largest):
            for (indext j = i + 1; j <= last; ++j) {
                if (!comp(*(seq + selected), *(seq + j))) { selected = j; }
            }
            // Swap the selected and {seq[i]}:
            if (selected != i) { std::iter_swap(seq + selected, seq + i); }
        }
    }
}