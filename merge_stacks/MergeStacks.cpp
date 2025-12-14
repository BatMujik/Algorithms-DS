#include "MergeStacks.h"
#include <algorithm>

std::vector<int> toVectorBottomToTop(const Stack& s) {
    // Copy by value to avoid mutating original via pops
    Stack copy = s;
    std::vector<int> tmp;
    // Pop to get top-to-bottom, then reverse to bottom-to-top
    while (!copy.isEmpty()) {
        tmp.push_back(copy.top());
        copy.pop();
    }
    std::reverse(tmp.begin(), tmp.end());
    return tmp;
}

Stack mergePreserveOrder(const Stack& a, const Stack& b) {
    Stack result;
    auto va = toVectorBottomToTop(a);
    auto vb = toVectorBottomToTop(b);
    // Push in bottom-to-top order: first a then b
    for (int x : va) result.push(x);
    for (int x : vb) result.push(x);
    return result;
}

Stack mergeInterleave(const Stack& a, const Stack& b) {
    Stack result;
    auto va = toVectorBottomToTop(a);
    auto vb = toVectorBottomToTop(b);
    size_t i = 0, j = 0;
    while (i < va.size() || j < vb.size()) {
        if (i < va.size()) { result.push(va[i]); ++i; }
        if (j < vb.size()) { result.push(vb[j]); ++j; }
    }
    return result;
}
