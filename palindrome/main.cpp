#include "PalindromeChecker.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

int main() {
    std::cout << "Palindrome Checker - Multiple Approaches" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    // Test cases for string palindromes
    std::vector<std::string> stringTests = {
        "racecar",              // Simple palindrome
        "A man a plan a canal Panama",  // Sentence palindrome
        "race a car",           // Not a palindrome
        "hello",                // Not a palindrome
        "Madam",                // Case-insensitive palindrome
        "No 'x' in Nixon",      // Complex palindrome
        "Mr. Owl ate my metal worm",  // Sentence palindrome
        "",                     // Empty string
        "a",                    // Single character
        "aa",                   // Two same characters
        "ab",                   // Two different characters
        "abcba",                // Odd-length palindrome
        "abccba",               // Even-length palindrome
        "Was it a car or a cat I saw?"  // Question palindrome
    };
    
    std::cout << "\n=== Basic Palindrome Tests ===" << std::endl;
    for (const auto& test : stringTests) {
        std::cout << "\"" << test << "\"" << std::endl;
        std::cout << "  Case-sensitive:     " << (PalindromeChecker::isPalindrome(test) ? "YES" : "NO") << std::endl;
        std::cout << "  Ignore case:        " << (PalindromeChecker::isPalindromeIgnoreCase(test) ? "YES" : "NO") << std::endl;
        std::cout << "  Alphanumeric only:  " << (PalindromeChecker::isPalindromeAlphanumeric(test) ? "YES" : "NO") << std::endl;
        std::cout << std::endl;
    }
    
    std::cout << "\n=== Algorithm Comparison ===" << std::endl;
    std::string testString = "racecar";
    
    auto start = std::chrono::high_resolution_clock::now();
    bool result1 = PalindromeChecker::isPalindrome(testString);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    bool result2 = PalindromeChecker::isPalindromeTwoPointer(testString);
    end = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    bool result3 = PalindromeChecker::isPalindromeStack(testString);
    end = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    bool result4 = PalindromeChecker::isPalindromeRecursive(testString);
    end = std::chrono::high_resolution_clock::now();
    auto duration4 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "Testing \"" << testString << "\":" << std::endl;
    std::cout << "Reverse method:     " << (result1 ? "YES" : "NO") << " (" << duration1.count() << " ns)" << std::endl;
    std::cout << "Two-pointer method: " << (result2 ? "YES" : "NO") << " (" << duration2.count() << " ns)" << std::endl;
    std::cout << "Stack method:       " << (result3 ? "YES" : "NO") << " (" << duration3.count() << " ns)" << std::endl;
    std::cout << "Recursive method:   " << (result4 ? "YES" : "NO") << " (" << duration4.count() << " ns)" << std::endl;
    
    std::cout << "\n=== Number Palindromes ===" << std::endl;
    std::vector<long long> numbers = {121, 1221, 12321, 123, 1001, 0, -121, 7};
    
    for (long long num : numbers) {
        bool isPalin = PalindromeChecker::isPalindrome(num);
        std::cout << num << " -> " << (isPalin ? "YES" : "NO") << std::endl;
    }
    
    std::cout << "\n=== Longest Palindromic Substring ===" << std::endl;
    std::vector<std::string> substringTests = {
        "babad",
        "cbbd",
        "raceacar",
        "abcdeffedcba",
        "hello"
    };
    
    for (const auto& test : substringTests) {
        std::string longest = PalindromeChecker::longestPalindromicSubstring(test);
        std::cout << "\"" << test << "\" -> \"" << longest << "\"" << std::endl;
    }
    
    std::cout << "\n=== Can Form Palindrome ===" << std::endl;
    std::vector<std::string> permutationTests = {
        "aab",       // Can form "aba"
        "carerac",   // Can form "racecar"
        "abc",       // Cannot form palindrome
        "aabbcc",    // Can form palindrome
        "aabbc"      // Cannot form palindrome
    };
    
    for (const auto& test : permutationTests) {
        bool canForm = PalindromeChecker::canFormPalindrome(test);
        std::cout << "\"" << test << "\" -> " << (canForm ? "YES" : "NO") << std::endl;
    }
    
    std::cout << "\n=== Count Palindromic Substrings ===" << std::endl;
    std::vector<std::string> countTests = {
        "abc",      // 3 substrings: "a", "b", "c"
        "aaa",      // 6 substrings: "a"(3), "aa"(2), "aaa"(1)
        "abccba"    // More complex case
    };
    
    for (const auto& test : countTests) {
        int count = PalindromeChecker::countPalindromicSubstrings(test);
        std::cout << "\"" << test << "\" -> " << count << " palindromic substrings" << std::endl;
    }
    
    std::cout << "\n=== Linked List Palindromes (using vectors) ===" << std::endl;
    std::vector<std::vector<int>> listTests = {
        {1, 2, 2, 1},
        {1, 2, 3, 2, 1},
        {1, 2, 3, 4, 5},
        {1},
        {},
        {1, 1},
        {1, 2}
    };
    
    for (const auto& list : listTests) {
        bool isPalin = PalindromeChecker::isLinkedListPalindrome(list);
        std::cout << "[";
        for (size_t i = 0; i < list.size(); ++i) {
            std::cout << list[i];
            if (i < list.size() - 1) std::cout << ", ";
        }
        std::cout << "] -> " << (isPalin ? "YES" : "NO") << std::endl;
    }
    
    std::cout << "\n=== Interactive Mode ===" << std::endl;
    std::cout << "Enter strings to check for palindromes (or 'quit' to exit):" << std::endl;
    
    std::string input;
    while (true) {
        std::cout << "\nString: ";
        std::getline(std::cin, input);
        
        if (input == "quit" || input == "exit") {
            break;
        }
        
        if (input.empty()) {
            continue;
        }
        
        std::cout << "Results for \"" << input << "\":" << std::endl;
        std::cout << "  Case-sensitive:       " << (PalindromeChecker::isPalindrome(input) ? "YES" : "NO") << std::endl;
        std::cout << "  Ignore case:          " << (PalindromeChecker::isPalindromeIgnoreCase(input) ? "YES" : "NO") << std::endl;
        std::cout << "  Alphanumeric only:    " << (PalindromeChecker::isPalindromeAlphanumeric(input) ? "YES" : "NO") << std::endl;
        std::cout << "  Can form palindrome:  " << (PalindromeChecker::canFormPalindrome(input) ? "YES" : "NO") << std::endl;
        
        std::string longest = PalindromeChecker::longestPalindromicSubstring(input);
        std::cout << "  Longest palindromic substring: \"" << longest << "\"" << std::endl;
        
        int count = PalindromeChecker::countPalindromicSubstrings(input);
        std::cout << "  Palindromic substrings count: " << count << std::endl;
    }
    
    std::cout << "\nProgram completed!" << std::endl;
    return 0;
}