#pragma once
#include <vector>

// 1. Iterative approach - O(n) time, O(1) space
long long fibIterative(int n);

// 2. Recursive approach - O(2^n) time, O(n) space
long long fibRecursive(int n);

// 3. Dynamic programming approach with memoization - O(n) time, O(n) space
long long fibDP(int n);
long long fibDPHelper(int n, std::vector<long long>& memo);

// 4. Matrix exponentiation approach - O(log n) time, O(1) space
long long fibMatrix(int n);
