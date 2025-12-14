#pragma once
#include <vector>
#include <string>
#include <limits>
#include <iostream>

// Matrix Chain Multiplication (MCM)
// Given dimensions p = [p0, p1, ..., pn], cost of multiplying Ai (pi-1 x pi)
// with Aj (pj-1 x pj) when split at k is: cost[i][k] + cost[k+1][j] + p[i-1]*p[k]*p[j].
// We implement:
//  - bottom-up tabular DP producing min cost and split table
//  - top-down memoized recursion producing min cost and split table
//  - reconstruction of optimal parenthesization string

struct MCMResult {
    long long cost;
    std::vector<std::vector<int>> split; // split[i][j] = optimal k
};

std::string buildParenthesization(const std::vector<std::vector<int>>& split, int i, int j);
MCMResult matrixChainTabular(const std::vector<int>& p);
long long mcmTopDownMemo(const std::vector<int>& p, int i, int j, std::vector<std::vector<long long>>& memo, std::vector<std::vector<int>>& split);
MCMResult matrixChainTopDown(const std::vector<int>& p);
void printMCM(const std::vector<int>& p);
