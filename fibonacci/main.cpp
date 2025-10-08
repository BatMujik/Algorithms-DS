#include "fibonacci.h"
#include <iostream>
#include <chrono>
#include <iomanip>

void testFibonacci(int n) {
    std::cout << "\n=== Testing Fibonacci for n = " << n << " ===" << std::endl;
    
    // Test all approaches and measure time
    auto start = std::chrono::high_resolution_clock::now();
    
    // 1. Iterative approach
    start = std::chrono::high_resolution_clock::now();
    long long result1 = fibIterative(n);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Iterative:       " << std::setw(15) << result1 
              << " | Time: " << std::setw(8) << duration1.count() << " μs" << std::endl;
    
    // 2. Dynamic Programming approach
    start = std::chrono::high_resolution_clock::now();
    long long result2 = fibDP(n);
    end = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "DP (Memoization): " << std::setw(15) << result2 
              << " | Time: " << std::setw(8) << duration2.count() << " μs" << std::endl;
    
    // 3. Matrix Exponentiation approach
    start = std::chrono::high_resolution_clock::now();
    long long result3 = fibMatrix(n);
    end = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Matrix Exp:      " << std::setw(15) << result3 
              << " | Time: " << std::setw(8) << duration3.count() << " μs" << std::endl;
    
    // 4. Recursive approach (only for small n to avoid long execution time)
    if (n <= 35) {
        start = std::chrono::high_resolution_clock::now();
        long long result4 = fibRecursive(n);
        end = std::chrono::high_resolution_clock::now();
        auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Recursive:       " << std::setw(15) << result4 
                  << " | Time: " << std::setw(8) << duration4.count() << " μs" << std::endl;
    } else {
        std::cout << "Recursive:       " << std::setw(15) << "Skipped (too slow for n > 35)" << std::endl;
    }
    
    // Verify all results are the same (excluding recursive for large n)
    bool consistent = (result1 == result2) && (result2 == result3);
    if (n <= 35) {
        long long result4 = fibRecursive(n);
        consistent = consistent && (result3 == result4);
    }
    
    std::cout << "Results consistent: " << (consistent ? "YES" : "NO") << std::endl;
}

int main() {
    std::cout << "Fibonacci Implementation Comparison" << std::endl;
    std::cout << "===================================" << std::endl;
    
    // Test with various values
    int testValues[] = {10, 20, 30, 40, 50, 60};
    
    for (int n : testValues) {
        testFibonacci(n);
    }
    
    std::cout << "\n=== Time Complexity Analysis ===" << std::endl;
    std::cout << "1. Iterative:       O(n) time,     O(1) space" << std::endl;
    std::cout << "2. Recursive:       O(2^n) time,   O(n) space (call stack)" << std::endl;
    std::cout << "3. DP Memoization:  O(n) time,     O(n) space" << std::endl;
    std::cout << "4. Matrix Exp:      O(log n) time, O(1) space" << std::endl;
    
    std::cout << "\n=== Interactive Test ===" << std::endl;
    std::cout << "Enter a number to calculate Fibonacci (0 to exit): ";
    
    int n;
    while (std::cin >> n && n != 0) {
        if (n < 0) {
            std::cout << "Please enter a non-negative number." << std::endl;
        } else {
            testFibonacci(n);
        }
        std::cout << "\nEnter another number (0 to exit): ";
    }
    
    return 0;
}