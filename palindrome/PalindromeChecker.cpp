#include "PalindromeChecker.h"
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <iostream>

bool PalindromeChecker::isPalindrome(const std::string& str) {
    if (str.empty()) return true;
    
    std::string reversed = str;
    std::reverse(reversed.begin(), reversed.end());
    return str == reversed;
}

bool PalindromeChecker::isPalindromeIgnoreCase(const std::string& str) {
    if (str.empty()) return true;
    
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    
    std::string reversed = lower;
    std::reverse(reversed.begin(), reversed.end());
    return lower == reversed;
}

bool PalindromeChecker::isPalindromeAlphanumeric(const std::string& str) {
    std::string cleaned = cleanString(str);
    return isPalindrome(cleaned);
}

bool PalindromeChecker::isPalindromeTwoPointer(const std::string& str) {
    if (str.empty()) return true;
    
    int left = 0;
    int right = str.length() - 1;
    
    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    
    return true;
}

bool PalindromeChecker::isPalindromeStack(const std::string& str) {
    if (str.empty()) return true;
    
    std::stack<char> charStack;
    int length = str.length();
    int middle = length / 2;
    
    // Push first half onto stack
    for (int i = 0; i < middle; i++) {
        charStack.push(str[i]);
    }
    
    // Start comparing from second half
    int start = (length % 2 == 0) ? middle : middle + 1;
    
    for (int i = start; i < length; i++) {
        if (charStack.empty() || charStack.top() != str[i]) {
            return false;
        }
        charStack.pop();
    }
    
    return charStack.empty();
}

bool PalindromeChecker::isPalindromeRecursive(const std::string& str) {
    if (str.empty()) return true;
    return isPalindromeRecursiveHelper(str, 0, str.length() - 1);
}

bool PalindromeChecker::isPalindromeRecursiveHelper(const std::string& str, int left, int right) {
    // Base case: if pointers meet or cross, it's a palindrome
    if (left >= right) {
        return true;
    }
    
    // Check if characters match and recursively check the rest
    if (str[left] != str[right]) {
        return false;
    }
    
    return isPalindromeRecursiveHelper(str, left + 1, right - 1);
}

bool PalindromeChecker::isPalindrome(long long number) {
    // Negative numbers are not palindromes
    if (number < 0) return false;
    
    long long original = number;
    long long reversed = 0;
    
    while (number > 0) {
        reversed = reversed * 10 + number % 10;
        number /= 10;
    }
    
    return original == reversed;
}

std::string PalindromeChecker::longestPalindromicSubstring(const std::string& str) {
    if (str.empty()) return "";
    
    int start = 0;
    int maxLength = 1;
    
    for (int i = 0; i < static_cast<int>(str.length()); i++) {
        // Check for odd-length palindromes (center at i)
        int len1 = expandAroundCenter(str, i, i);
        
        // Check for even-length palindromes (center between i and i+1)
        int len2 = expandAroundCenter(str, i, i + 1);
        
        int currentMax = std::max(len1, len2);
        
        if (currentMax > maxLength) {
            maxLength = currentMax;
            start = i - (currentMax - 1) / 2;
        }
    }
    
    return str.substr(start, maxLength);
}

int PalindromeChecker::expandAroundCenter(const std::string& str, int left, int right) {
    while (left >= 0 && right < static_cast<int>(str.length()) && str[left] == str[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}

bool PalindromeChecker::canFormPalindrome(const std::string& str) {
    std::unordered_map<char, int> charCount;
    
    // Count frequency of each character
    for (char c : str) {
        charCount[c]++;
    }
    
    // Count characters with odd frequency
    int oddCount = 0;
    for (const auto& pair : charCount) {
        if (pair.second % 2 == 1) {
            oddCount++;
        }
    }
    
    // For a palindrome, at most one character can have odd frequency
    return oddCount <= 1;
}

int PalindromeChecker::countPalindromicSubstrings(const std::string& str) {
    int count = 0;
    
    for (int i = 0; i < static_cast<int>(str.length()); i++) {
        // Count odd-length palindromes centered at i
        count += expandAroundCenter(str, i, i) > 0 ? 
                 (expandAroundCenter(str, i, i) + 1) / 2 : 0;
        
        // Count even-length palindromes centered between i and i+1
        count += expandAroundCenter(str, i, i + 1) > 0 ? 
                 expandAroundCenter(str, i, i + 1) / 2 : 0;
    }
    
    return count;
}

bool PalindromeChecker::isLinkedListPalindrome(const std::vector<int>& list) {
    if (list.empty()) return true;
    
    // Method 1: Using stack (O(n) space)
    std::stack<int> nodeStack;
    int length = list.size();
    int middle = length / 2;
    
    // Push first half onto stack
    for (int i = 0; i < middle; i++) {
        nodeStack.push(list[i]);
    }
    
    // Start comparing from second half
    int start = (length % 2 == 0) ? middle : middle + 1;
    
    for (int i = start; i < length; i++) {
        if (nodeStack.empty() || nodeStack.top() != list[i]) {
            return false;
        }
        nodeStack.pop();
    }
    
    return true;
}

std::string PalindromeChecker::cleanString(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (std::isalnum(c)) {
            result += std::tolower(c);
        }
    }
    return result;
}

bool PalindromeChecker::isPalindromeSubstring(const std::string& str, int start, int end) {
    while (start < end) {
        if (str[start] != str[end]) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}