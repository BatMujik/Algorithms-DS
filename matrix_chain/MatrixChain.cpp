#include "MatrixChain.h"

std::string buildParenthesization(const std::vector<std::vector<int>>& split, int i, int j) {
	if (i == j) {
		return "A" + std::to_string(i);
	}
	int k = split[i][j];
	return "(" + buildParenthesization(split, i, k) + " x " + buildParenthesization(split, k + 1, j) + ")";
}

MCMResult matrixChainTabular(const std::vector<int>& p) {
	int n = static_cast<int>(p.size()) - 1; // number of matrices
	if (n <= 0) return {0, {}};
	const long long INF = std::numeric_limits<long long>::max() / 4;
	std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(n + 1, 0));
	std::vector<std::vector<int>> split(n + 1, std::vector<int>(n + 1, -1));

	for (int len = 2; len <= n; ++len) {
		for (int i = 1; i <= n - len + 1; ++i) {
			int j = i + len - 1;
			dp[i][j] = INF;
			for (int k = i; k < j; ++k) {
				long long q = dp[i][k] + dp[k + 1][j] + 1LL * p[i - 1] * p[k] * p[j];
				if (q < dp[i][j]) {
					dp[i][j] = q;
					split[i][j] = k;
				}
			}
		}
	}
	return {dp[1][n], split};
}

long long mcmTopDownMemo(const std::vector<int>& p, int i, int j, std::vector<std::vector<long long>>& memo, std::vector<std::vector<int>>& split) {
	if (i == j) return 0;
	if (memo[i][j] != -1) return memo[i][j];
	long long best = std::numeric_limits<long long>::max() / 4;
	int bestK = -1;
	for (int k = i; k < j; ++k) {
		long long left = mcmTopDownMemo(p, i, k, memo, split);
		long long right = mcmTopDownMemo(p, k + 1, j, memo, split);
		long long q = left + right + 1LL * p[i - 1] * p[k] * p[j];
		if (q < best) { best = q; bestK = k; }
	}
	split[i][j] = bestK;
	memo[i][j] = best;
	return best;
}

MCMResult matrixChainTopDown(const std::vector<int>& p) {
	int n = static_cast<int>(p.size()) - 1;
	if (n <= 0) return {0, {}};
	std::vector<std::vector<long long>> memo(n + 1, std::vector<long long>(n + 1, -1));
	std::vector<std::vector<int>> split(n + 1, std::vector<int>(n + 1, -1));
	long long cost = mcmTopDownMemo(p, 1, n, memo, split);
	return {cost, split};
}

void printMCM(const std::vector<int>& p) {
	auto tab = matrixChainTabular(p);
	auto top = matrixChainTopDown(p);
	std::cout << "Dimensions: ";
	for (size_t i = 0; i < p.size(); ++i) std::cout << p[i] << (i + 1 == p.size() ? '\n' : ' ');
	std::cout << "Tabular cost: " << tab.cost << '\n';
	if (!tab.split.empty()) std::cout << "Tabular parens: " << buildParenthesization(tab.split, 1, static_cast<int>(p.size()) - 1) << '\n';
	std::cout << "TopDown cost: " << top.cost << '\n';
	if (!top.split.empty()) std::cout << "TopDown parens: " << buildParenthesization(top.split, 1, static_cast<int>(p.size()) - 1) << '\n';
}