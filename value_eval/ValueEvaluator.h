#pragma once
#include <string>
#include <unordered_map>
#include <functional>

class ValueEvaluator {
public:
    // Main evaluation function
    static double evaluate(const std::string& expression);
    
    // Evaluate with variable substitution
    static double evaluate(const std::string& expression, const std::unordered_map<std::string, double>& variables);
    
    // Evaluate arithmetic expression (infix notation)
    static double evaluateArithmetic(const std::string& expression);
    
    // Evaluate with custom functions
    static double evaluateWithFunctions(const std::string& expression, 
                                       const std::unordered_map<std::string, std::function<double(double)>>& functions);
    
    // Parse and evaluate complex expressions with parentheses
    static double evaluateComplex(const std::string& expression);
    
    // Validate expression syntax
    static bool isValidExpression(const std::string& expression);
    
    // Convert infix to postfix for evaluation
    static std::string infixToPostfix(const std::string& infix);
    
    // Evaluate postfix expression
    static double evaluatePostfix(const std::string& postfix);
    
    // Support for comparison operators (returns 1.0 for true, 0.0 for false)
    static double evaluateComparison(const std::string& expression);

private:
    // Helper functions
    static bool isOperator(char c);
    static bool isFunction(const std::string& token);
    static int getPrecedence(char op);
    static bool isLeftAssociative(char op);
    static double performOperation(double a, double b, char op);
    static double performFunction(const std::string& func, double arg);
    static double performComparison(double a, double b, const std::string& op);
    
    // Tokenization helpers
    static std::vector<std::string> tokenize(const std::string& expression);
    static std::string removeSpaces(const std::string& str);
    static bool isNumber(const std::string& token);
    static bool isVariable(const std::string& token);
    
    // Expression parsing helpers
    static double parseExpression(const std::string& expr, size_t& pos);
    static double parseTerm(const std::string& expr, size_t& pos);
    static double parseFactor(const std::string& expr, size_t& pos);
    static double parseNumber(const std::string& expr, size_t& pos);
    
    // Built-in functions
    static const std::unordered_map<std::string, std::function<double(double)>> builtInFunctions;
    
    // Current variables context (for recursive evaluation)
    static std::unordered_map<std::string, double> currentVariables;
};