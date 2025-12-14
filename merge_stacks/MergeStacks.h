#pragma once
#include "../array_based_stack/Stack.h"
#include <vector>

// Merges two stacks into one.
// Convention: printing from top to bottom using pops.
// mergePreserveOrder: resulting stack has elements of `a` then `b`, preserving each stack's bottom-to-top order.
// mergeInterleave: alternates elements from `a` and `b` starting from each stack's bottom.

Stack mergePreserveOrder(const Stack& a, const Stack& b);
Stack mergeInterleave(const Stack& a, const Stack& b);

// Helper: dump stack to vector from bottom to top without mutating original
std::vector<int> toVectorBottomToTop(const Stack& s);
