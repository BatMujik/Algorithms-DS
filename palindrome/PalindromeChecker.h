#pragma once
#include <string>
#include <vector>
#include <stack>
#include <deque>

class PalindromeChecker {
public:
    // Basic palindrome check (case-sensitive)
    static bool isPalindrome(const std::string& str);
    
    // Case-insensitive palindrome check
    static bool isPalindromeIgnoreCase(const std::string& str);
    
    // Palindrome check ignoring spaces and punctuation
    static bool isPalindromeAlphanumeric(const std::string& str);
    
    // Two-pointer approach
    static bool isPalindromeTwoPointer(const std::string& str);
    
    // Stack-based approach
    static bool isPalindromeStack(const std::string& str);
    
    // Recursive approach
    static bool isPalindromeRecursive(const std::string& str);
    
    // Check if a number is palindrome
    static bool isPalindrome(long long number);
    
    // Find longest palindromic substring
    static std::string longestPalindromicSubstring(const std::string& str);
    
    // Check if string can be rearranged to form a palindrome
    static bool canFormPalindrome(const std::string& str);
    
    // Count palindromic substrings
    static int countPalindromicSubstrings(const std::string& str);
    
    // Check if linked list is palindrome (using vector to simulate)
    static bool isLinkedListPalindrome(const std::vector<int>& list);

private:
    // Helper function to clean string (remove non-alphanumeric, convert to lowercase)
    static std::string cleanString(const std::string& str);
    
    // Helper for recursive palindrome check
    static bool isPalindromeRecursiveHelper(const std::string& str, int left, int right);
    
    // Helper to check if substring is palindrome (for optimization)
    static bool isPalindromeSubstring(const std::string& str, int start, int end);
    
    // Expand around center for palindrome detection
    static int expandAroundCenter(const std::string& str, int left, int right);
};