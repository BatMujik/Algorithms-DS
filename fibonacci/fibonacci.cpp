#include "fibonacci.h"
#include <vector>

// 1. Iterative approach - O(n) time, O(1) space
long long fibIterative(int n) {
    if (n <= 1) return n;
    
    long long prev = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

// 2. Recursive approach - O(2^n) time, O(n) space
long long fibRecursive(int n) {
    if (n <= 1) return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// 3. Dynamic programming approach with memoization - O(n) time, O(n) space
long long fibDP(int n) {
    if (n <= 1) return n;
    
    std::vector<long long> memo(n + 1, -1);
    return fibDPHelper(n, memo);
}

long long fibDPHelper(int n, std::vector<long long>& memo) {
    if (n <= 1) return n;
    
    if (memo[n] != -1) return memo[n];
    
    memo[n] = fibDPHelper(n - 1, memo) + fibDPHelper(n - 2, memo);
    return memo[n];
}

// Helper function for matrix multiplication
void multiplyMatrix(long long F[2][2], long long M[2][2]) {
    long long x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    long long y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    long long z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    long long w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
    
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

// Helper function for matrix power
void matrixPower(long long F[2][2], int n) {
    if (n == 0 || n == 1) return;
    
    long long M[2][2] = {{1, 1}, {1, 0}};
    
    matrixPower(F, n / 2);
    multiplyMatrix(F, F);
    
    if (n % 2 != 0) {
        multiplyMatrix(F, M);
    }
}

// 4. Matrix exponentiation approach - O(log n) time, O(1) space
long long fibMatrix(int n) {
    if (n <= 1) return n;
    
    long long F[2][2] = {{1, 1}, {1, 0}};
    matrixPower(F, n - 1);
    
    return F[0][0];
}