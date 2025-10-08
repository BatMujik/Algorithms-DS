#include "BracketBalancer.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::cout << "Balanced Brackets Checker" << std::endl;
    std::cout << "=========================" << std::endl;
    
    // Test cases
    std::vector<std::string> testCases = {
        "()",                    // Simple balanced
        "[]",                    // Square brackets
        "{}",                    // Curly brackets
        "<>",                    // Angle brackets
        "()[]{}",               // Multiple types balanced
        "([{}])",               // Nested balanced
        "((()))",               // Multiple nesting
        "[{()}]",               // Complex nesting
        "",                     // Empty string
        "abc",                  // No brackets
        "a(b)c[d]e{f}g",       // With other characters
        
        // Unbalanced cases
        "(",                    // Single opening
        ")",                    // Single closing
        "([)]",                 // Crossed brackets
        "(((",                  // Multiple opening
        ")))",                  // Multiple closing
        "({[}])",              // Wrong order
        "(()",                  // Missing closing
        "())",                  // Extra closing
        "[{()}",               // Missing closing brace
        "abc)def",             // Unmatched in text
    };
    
    std::cout << "\n=== Basic Balance Check ===" << std::endl;
    for (const auto& test : testCases) {
        bool balanced = BracketBalancer::isBalanced(test);
        std::cout << "\"" << test << "\" -> " << (balanced ? "BALANCED" : "UNBALANCED") << std::endl;
    }
    
    std::cout << "\n=== Detailed Error Messages ===" << std::endl;
    std::vector<std::string> errorTestCases = {
        "([)]",
        "(()",
        "())",
        "{[}]",
        "abc)def"
    };
    
    for (const auto& test : errorTestCases) {
        std::string errorMessage;
        bool balanced = BracketBalancer::isBalancedWithDetails(test, errorMessage);
        std::cout << "\"" << test << "\" -> " << (balanced ? "BALANCED" : "UNBALANCED") 
                  << "\n  " << errorMessage << std::endl;
    }
    
    std::cout << "\n=== Specific Bracket Types ===" << std::endl;
    std::string complexExpression = "function(arg1, arg2) { array[index] = value; }";
    
    std::vector<char> parenthesesOnly = {'('};
    std::vector<char> squareOnly = {'['};
    std::vector<char> curlyOnly = {'{'};
    std::vector<char> roundAndSquare = {'(', '['};
    
    std::cout << "Expression: \"" << complexExpression << "\"" << std::endl;
    std::cout << "Parentheses only: " << (BracketBalancer::isBalancedForTypes(complexExpression, parenthesesOnly) ? "BALANCED" : "UNBALANCED") << std::endl;
    std::cout << "Square brackets only: " << (BracketBalancer::isBalancedForTypes(complexExpression, squareOnly) ? "BALANCED" : "UNBALANCED") << std::endl;
    std::cout << "Curly brackets only: " << (BracketBalancer::isBalancedForTypes(complexExpression, curlyOnly) ? "BALANCED" : "UNBALANCED") << std::endl;
    std::cout << "Round and square: " << (BracketBalancer::isBalancedForTypes(complexExpression, roundAndSquare) ? "BALANCED" : "UNBALANCED") << std::endl;
    
    std::cout << "\n=== First Unbalanced Position ===" << std::endl;
    for (const auto& test : errorTestCases) {
        int position = BracketBalancer::getFirstUnbalancedPosition(test);
        std::cout << "\"" << test << "\" -> ";
        if (position == -1) {
            std::cout << "All balanced" << std::endl;
        } else {
            std::cout << "First error at position " << position << " ('" << test[position] << "')" << std::endl;
        }
    }
    
    std::cout << "\n=== Extract Brackets ===" << std::endl;
    std::vector<std::string> extractTests = {
        "function(arg1, arg2)",
        "array[i] = obj.method()",
        "if (condition) { doSomething(); }",
        "template<typename T>",
        "a + b * (c - d)"
    };
    
    for (const auto& test : extractTests) {
        std::string extracted = BracketBalancer::extractBrackets(test);
        std::cout << "\"" << test << "\" -> \"" << extracted << "\"" << std::endl;
    }
    
    std::cout << "\n=== Interactive Mode ===" << std::endl;
    std::cout << "Enter expressions to check (or 'quit' to exit):" << std::endl;
    
    std::string input;
    while (true) {
        std::cout << "\nExpression: ";
        std::getline(std::cin, input);
        
        if (input == "quit" || input == "exit") {
            break;
        }
        
        if (input.empty()) {
            continue;
        }
        
        // Basic check
        bool balanced = BracketBalancer::isBalanced(input);
        std::cout << "Result: " << (balanced ? "BALANCED" : "UNBALANCED") << std::endl;
        
        // Detailed check
        std::string errorMessage;
        BracketBalancer::isBalancedWithDetails(input, errorMessage);
        std::cout << "Details: " << errorMessage << std::endl;
        
        // Extract brackets
        std::string extracted = BracketBalancer::extractBrackets(input);
        if (!extracted.empty()) {
            std::cout << "Brackets only: \"" << extracted << "\"" << std::endl;
        }
        
        // First error position
        int errorPos = BracketBalancer::getFirstUnbalancedPosition(input);
        if (errorPos != -1) {
            std::cout << "First error at position: " << errorPos << std::endl;
        }
    }
    
    std::cout << "\nProgram completed!" << std::endl;
    return 0;
}