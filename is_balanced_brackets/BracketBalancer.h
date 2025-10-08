#pragma once
#include <string>
#include <stack>
#include <unordered_map>
#include <vector>

class BracketBalancer {
public:
    // Check if brackets are balanced using STL stack
    static bool isBalanced(const std::string& expression);
    
    // Check if brackets are balanced with detailed error reporting
    static bool isBalancedWithDetails(const std::string& expression, std::string& errorMessage);
    
    // Check balance for specific bracket types only
    static bool isBalancedForTypes(const std::string& expression, const std::vector<char>& openBrackets);
    
    // Get the position of first unbalanced bracket
    static int getFirstUnbalancedPosition(const std::string& expression);
    
    // Remove all non-bracket characters and return cleaned string
    static std::string extractBrackets(const std::string& expression);
    
    // Check if character is an opening bracket
    static bool isOpeningBracket(char c);
    
    // Check if character is a closing bracket
    static bool isClosingBracket(char c);
    
    // Get the matching closing bracket for an opening bracket
    static char getMatchingClosing(char openBracket);
    
    // Get the matching opening bracket for a closing bracket
    static char getMatchingOpening(char closeBracket);

private:
    // Mapping of closing brackets to opening brackets
    static const std::unordered_map<char, char> bracketPairs;
    
    // Set of all opening brackets
    static const std::string openingBrackets;
    
    // Set of all closing brackets
    static const std::string closingBrackets;
};