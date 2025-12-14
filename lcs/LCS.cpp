#include "LCS.h"

static int lcsTopDownMemoHelper(const std::string& a, const std::string& b, int i, int j, std::vector<std::vector<int>>& memo) {
    if (i == (int)a.size() || j == (int)b.size()) return 0;
    int& m = memo[i][j];
    if (m != -1) return m;
    if (a[i] == b[j]) {
        m = 1 + lcsTopDownMemoHelper(a, b, i + 1, j + 1, memo);
    } else {
        m = std::max(lcsTopDownMemoHelper(a, b, i + 1, j, memo), lcsTopDownMemoHelper(a, b, i, j + 1, memo));
    }
    return m;
}

int lcsTopDownLength(const std::string& a, const std::string& b) {
    std::vector<std::vector<int>> memo(a.size(), std::vector<int>(b.size(), -1));
    return lcsTopDownMemoHelper(a, b, 0, 0, memo);
}

LCSResult lcsTabular(const std::string& a, const std::string& b) {
    int n = (int)a.size();
    int m = (int)b.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            if (a[i] == b[j]) dp[i][j] = 1 + dp[i + 1][j + 1];
            else dp[i][j] = std::max(dp[i + 1][j], dp[i][j + 1]);
        }
    }

    // Reconstruct one LCS string using dp table
    std::string lcs;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] == b[j]) { lcs.push_back(a[i]); ++i; ++j; }
        else if (dp[i + 1][j] >= dp[i][j + 1]) { ++i; }
        else { ++j; }
    }

    return {dp[0][0], lcs};
}
