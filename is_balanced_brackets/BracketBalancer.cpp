#include "BracketBalancer.h"
#include <iostream>
#include <sstream>

// Static member definitions
const std::unordered_map<char, char> BracketBalancer::bracketPairs = {
    {')', '('},
    {']', '['},
    {'}', '{'},
    {'>', '<'}  // For template brackets in some contexts
};

const std::string BracketBalancer::openingBrackets = "([{<";
const std::string BracketBalancer::closingBrackets = ")]}>";

bool BracketBalancer::isBalanced(const std::string& expression) {
    std::stack<char> bracketStack;
    
    for (char c : expression) {
        if (isOpeningBracket(c)) {
            bracketStack.push(c);
        } else if (isClosingBracket(c)) {
            if (bracketStack.empty()) {
                return false; // Closing bracket without matching opening
            }
            
            char topBracket = bracketStack.top();
            bracketStack.pop();
            
            if (topBracket != getMatchingOpening(c)) {
                return false; // Mismatched bracket types
            }
        }
        // Ignore non-bracket characters
    }
    
    return bracketStack.empty(); // All brackets should be matched
}

bool BracketBalancer::isBalancedWithDetails(const std::string& expression, std::string& errorMessage) {
    std::stack<std::pair<char, int>> bracketStack; // Store bracket and its position
    
    for (int i = 0; i < static_cast<int>(expression.length()); ++i) {
        char c = expression[i];
        
        if (isOpeningBracket(c)) {
            bracketStack.push({c, i});
        } else if (isClosingBracket(c)) {
            if (bracketStack.empty()) {
                std::ostringstream oss;
                oss << "Unmatched closing bracket '" << c << "' at position " << i;
                errorMessage = oss.str();
                return false;
            }
            
            auto topPair = bracketStack.top();
            bracketStack.pop();
            
            if (topPair.first != getMatchingOpening(c)) {
                std::ostringstream oss;
                oss << "Mismatched brackets: '" << topPair.first << "' at position " 
                    << topPair.second << " does not match '" << c << "' at position " << i;
                errorMessage = oss.str();
                return false;
            }
        }
    }
    
    if (!bracketStack.empty()) {
        auto topPair = bracketStack.top();
        std::ostringstream oss;
        oss << "Unmatched opening bracket '" << topPair.first << "' at position " << topPair.second;
        errorMessage = oss.str();
        return false;
    }
    
    errorMessage = "All brackets are properly balanced";
    return true;
}

bool BracketBalancer::isBalancedForTypes(const std::string& expression, const std::vector<char>& openBrackets) {
    std::stack<char> bracketStack;
    
    // Create a set for quick lookup
    std::unordered_map<char, bool> allowedOpenings;
    std::unordered_map<char, bool> allowedClosings;
    
    for (char open : openBrackets) {
        allowedOpenings[open] = true;
        allowedClosings[getMatchingClosing(open)] = true;
    }
    
    for (char c : expression) {
        if (allowedOpenings.count(c)) {
            bracketStack.push(c);
        } else if (allowedClosings.count(c)) {
            if (bracketStack.empty()) {
                return false;
            }
            
            char topBracket = bracketStack.top();
            bracketStack.pop();
            
            if (topBracket != getMatchingOpening(c)) {
                return false;
            }
        }
        // Ignore other brackets and non-bracket characters
    }
    
    return bracketStack.empty();
}

int BracketBalancer::getFirstUnbalancedPosition(const std::string& expression) {
    std::stack<std::pair<char, int>> bracketStack;
    
    for (int i = 0; i < static_cast<int>(expression.length()); ++i) {
        char c = expression[i];
        
        if (isOpeningBracket(c)) {
            bracketStack.push({c, i});
        } else if (isClosingBracket(c)) {
            if (bracketStack.empty()) {
                return i; // First unmatched closing bracket
            }
            
            auto topPair = bracketStack.top();
            bracketStack.pop();
            
            if (topPair.first != getMatchingOpening(c)) {
                return i; // First mismatched bracket
            }
        }
    }
    
    if (!bracketStack.empty()) {
        return bracketStack.top().second; // First unmatched opening bracket
    }
    
    return -1; // All brackets are balanced
}

std::string BracketBalancer::extractBrackets(const std::string& expression) {
    std::string result;
    for (char c : expression) {
        if (isOpeningBracket(c) || isClosingBracket(c)) {
            result += c;
        }
    }
    return result;
}

bool BracketBalancer::isOpeningBracket(char c) {
    return openingBrackets.find(c) != std::string::npos;
}

bool BracketBalancer::isClosingBracket(char c) {
    return closingBrackets.find(c) != std::string::npos;
}

char BracketBalancer::getMatchingClosing(char openBracket) {
    switch (openBracket) {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
        case '<': return '>';
        default: return '\0';
    }
}

char BracketBalancer::getMatchingOpening(char closeBracket) {
    auto it = bracketPairs.find(closeBracket);
    return (it != bracketPairs.end()) ? it->second : '\0';
}