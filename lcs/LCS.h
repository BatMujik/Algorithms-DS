#pragma once
#include <string>
#include <vector>
#include <iostream>

struct LCSResult {
    int length;
    std::string lcs; // one possible LCS string
};

// Bottom-up tabular DP
LCSResult lcsTabular(const std::string& a, const std::string& b);

// Top-down memoized recursion (returns length only); reconstruction using memo and strings
int lcsTopDownLength(const std::string& a, const std::string& b);

// Utility to print result
inline void printLCS(const std::string& a, const std::string& b) {
    auto res = lcsTabular(a, b);
    std::cout << "A: " << a << "\nB: " << b << "\nLength: " << res.length << "\nLCS: " << res.lcs << "\n";
}
