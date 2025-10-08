#include "ValueEvaluator.h"
#include <stack>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <iostream>

// Static member definitions
std::unordered_map<std::string, double> ValueEvaluator::currentVariables;

const std::unordered_map<std::string, std::function<double(double)>> ValueEvaluator::builtInFunctions = {
    {"sin", [](double x) { return std::sin(x); }},
    {"cos", [](double x) { return std::cos(x); }},
    {"tan", [](double x) { return std::tan(x); }},
    {"log", [](double x) { return std::log(x); }},
    {"ln", [](double x) { return std::log(x); }},
    {"log10", [](double x) { return std::log10(x); }},
    {"sqrt", [](double x) { return std::sqrt(x); }},
    {"abs", [](double x) { return std::abs(x); }},
    {"floor", [](double x) { return std::floor(x); }},
    {"ceil", [](double x) { return std::ceil(x); }},
    {"exp", [](double x) { return std::exp(x); }},
    {"asin", [](double x) { return std::asin(x); }},
    {"acos", [](double x) { return std::acos(x); }},
    {"atan", [](double x) { return std::atan(x); }}
};

double ValueEvaluator::evaluate(const std::string& expression) {
    std::unordered_map<std::string, double> emptyVars;
    return evaluate(expression, emptyVars);
}

double ValueEvaluator::evaluate(const std::string& expression, const std::unordered_map<std::string, double>& variables) {
    currentVariables = variables;
    
    // Try different evaluation strategies
    try {
        return evaluateComplex(expression);
    } catch (const std::exception& e) {
        try {
            return evaluateArithmetic(expression);
        } catch (const std::exception& e2) {
            std::string postfix = infixToPostfix(expression);
            return evaluatePostfix(postfix);
        }
    }
}

double ValueEvaluator::evaluateArithmetic(const std::string& expression) {
    if (!isValidExpression(expression)) {
        throw std::invalid_argument("Invalid expression syntax");
    }
    
    std::string postfix = infixToPostfix(expression);
    return evaluatePostfix(postfix);
}

double ValueEvaluator::evaluateWithFunctions(const std::string& expression, 
                                           const std::unordered_map<std::string, std::function<double(double)>>& functions) {
    // This is a simplified version - in a full implementation, we'd need to parse function calls
    return evaluateArithmetic(expression);
}

double ValueEvaluator::evaluateComplex(const std::string& expression) {
    std::string cleaned = removeSpaces(expression);
    size_t pos = 0;
    double result = parseExpression(cleaned, pos);
    
    if (pos < cleaned.length()) {
        throw std::invalid_argument("Unexpected characters at end of expression");
    }
    
    return result;
}

bool ValueEvaluator::isValidExpression(const std::string& expression) {
    std::string cleaned = removeSpaces(expression);
    
    if (cleaned.empty()) return false;
    
    int parentheses = 0;
    bool expectOperand = true;
    
    for (size_t i = 0; i < cleaned.length(); ++i) {
        char c = cleaned[i];
        
        if (c == '(') {
            if (!expectOperand) return false;
            parentheses++;
        } else if (c == ')') {
            if (expectOperand || parentheses == 0) return false;
            parentheses--;
            expectOperand = false;
        } else if (isOperator(c)) {
            if (expectOperand && c != '-' && c != '+') return false;
            expectOperand = true;
        } else if (std::isdigit(c) || c == '.') {
            if (!expectOperand) return false;
            // Skip the rest of the number
            while (i + 1 < cleaned.length() && (std::isdigit(cleaned[i + 1]) || cleaned[i + 1] == '.')) {
                ++i;
            }
            expectOperand = false;
        } else if (std::isalpha(c)) {
            if (!expectOperand) return false;
            // Skip the rest of the variable/function name
            while (i + 1 < cleaned.length() && (std::isalnum(cleaned[i + 1]) || cleaned[i + 1] == '_')) {
                ++i;
            }
            expectOperand = false;
        } else {
            return false; // Invalid character
        }
    }
    
    return parentheses == 0 && !expectOperand;
}

std::string ValueEvaluator::infixToPostfix(const std::string& infix) {
    std::string result;
    std::stack<char> operators;
    std::string cleaned = removeSpaces(infix);
    
    for (size_t i = 0; i < cleaned.length(); ++i) {
        char c = cleaned[i];
        
        if (std::isdigit(c) || c == '.') {
            // Add number to result
            while (i < cleaned.length() && (std::isdigit(cleaned[i]) || cleaned[i] == '.')) {
                result += cleaned[i];
                ++i;
            }
            result += ' ';
            --i; // Adjust for loop increment
        } else if (std::isalpha(c)) {
            // Add variable name to result
            while (i < cleaned.length() && (std::isalnum(cleaned[i]) || cleaned[i] == '_')) {
                result += cleaned[i];
                ++i;
            }
            result += ' ';
            --i; // Adjust for loop increment
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                result += operators.top();
                result += ' ';
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop(); // Remove '('
            }
        } else if (isOperator(c)) {
            while (!operators.empty() && 
                   operators.top() != '(' &&
                   ((isLeftAssociative(c) && getPrecedence(operators.top()) >= getPrecedence(c)) ||
                    (!isLeftAssociative(c) && getPrecedence(operators.top()) > getPrecedence(c)))) {
                result += operators.top();
                result += ' ';
                operators.pop();
            }
            operators.push(c);
        }
    }
    
    while (!operators.empty()) {
        result += operators.top();
        result += ' ';
        operators.pop();
    }
    
    // Remove trailing space
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    return result;
}

double ValueEvaluator::evaluatePostfix(const std::string& postfix) {
    std::stack<double> operands;
    std::istringstream iss(postfix);
    std::string token;
    
    while (iss >> token) {
        if (isNumber(token)) {
            operands.push(std::stod(token));
        } else if (isVariable(token)) {
            auto it = currentVariables.find(token);
            if (it != currentVariables.end()) {
                operands.push(it->second);
            } else {
                throw std::invalid_argument("Undefined variable: " + token);
            }
        } else if (token.length() == 1 && isOperator(token[0])) {
            if (operands.size() < 2) {
                throw std::invalid_argument("Insufficient operands for operator: " + token);
            }
            
            double b = operands.top(); operands.pop();
            double a = operands.top(); operands.pop();
            
            double result = performOperation(a, b, token[0]);
            operands.push(result);
        } else if (isFunction(token)) {
            if (operands.size() < 1) {
                throw std::invalid_argument("Insufficient operands for function: " + token);
            }
            
            double arg = operands.top(); operands.pop();
            double result = performFunction(token, arg);
            operands.push(result);
        } else {
            throw std::invalid_argument("Unknown token: " + token);
        }
    }
    
    if (operands.size() != 1) {
        throw std::invalid_argument("Invalid postfix expression");
    }
    
    return operands.top();
}

double ValueEvaluator::evaluateComparison(const std::string& expression) {
    // Simple comparison evaluation - would need more complex parsing for full implementation
    return evaluateArithmetic(expression);
}

// Helper function implementations
bool ValueEvaluator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%';
}

bool ValueEvaluator::isFunction(const std::string& token) {
    return builtInFunctions.find(token) != builtInFunctions.end();
}

int ValueEvaluator::getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

bool ValueEvaluator::isLeftAssociative(char op) {
    return op != '^'; // Only exponentiation is right associative
}

double ValueEvaluator::performOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        case '^': return std::pow(a, b);
        case '%':
            if (b == 0) throw std::runtime_error("Modulo by zero");
            return std::fmod(a, b);
        default:
            throw std::invalid_argument("Unknown operator");
    }
}

double ValueEvaluator::performFunction(const std::string& func, double arg) {
    auto it = builtInFunctions.find(func);
    if (it != builtInFunctions.end()) {
        return it->second(arg);
    }
    throw std::invalid_argument("Unknown function: " + func);
}

double ValueEvaluator::performComparison(double a, double b, const std::string& op) {
    if (op == "==") return (a == b) ? 1.0 : 0.0;
    if (op == "!=") return (a != b) ? 1.0 : 0.0;
    if (op == "<") return (a < b) ? 1.0 : 0.0;
    if (op == "<=") return (a <= b) ? 1.0 : 0.0;
    if (op == ">") return (a > b) ? 1.0 : 0.0;
    if (op == ">=") return (a >= b) ? 1.0 : 0.0;
    throw std::invalid_argument("Unknown comparison operator: " + op);
}

std::string ValueEvaluator::removeSpaces(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (c != ' ' && c != '\t') {
            result += c;
        }
    }
    return result;
}

bool ValueEvaluator::isNumber(const std::string& token) {
    if (token.empty()) return false;
    
    size_t start = 0;
    if (token[0] == '-' || token[0] == '+') {
        start = 1;
        if (token.length() == 1) return false;
    }
    
    bool hasDecimal = false;
    for (size_t i = start; i < token.length(); ++i) {
        if (token[i] == '.') {
            if (hasDecimal) return false;
            hasDecimal = true;
        } else if (!std::isdigit(token[i])) {
            return false;
        }
    }
    
    return true;
}

bool ValueEvaluator::isVariable(const std::string& token) {
    if (token.empty() || !std::isalpha(token[0])) return false;
    
    for (char c : token) {
        if (!std::isalnum(c) && c != '_') return false;
    }
    
    return !isFunction(token); // Make sure it's not a function name
}

// Recursive descent parser implementation
double ValueEvaluator::parseExpression(const std::string& expr, size_t& pos) {
    double result = parseTerm(expr, pos);
    
    while (pos < expr.length() && (expr[pos] == '+' || expr[pos] == '-')) {
        char op = expr[pos++];
        double term = parseTerm(expr, pos);
        
        if (op == '+') {
            result += term;
        } else {
            result -= term;
        }
    }
    
    return result;
}

double ValueEvaluator::parseTerm(const std::string& expr, size_t& pos) {
    double result = parseFactor(expr, pos);
    
    while (pos < expr.length() && (expr[pos] == '*' || expr[pos] == '/' || expr[pos] == '%')) {
        char op = expr[pos++];
        double factor = parseFactor(expr, pos);
        
        if (op == '*') {
            result *= factor;
        } else if (op == '/') {
            if (factor == 0) throw std::runtime_error("Division by zero");
            result /= factor;
        } else { // %
            if (factor == 0) throw std::runtime_error("Modulo by zero");
            result = std::fmod(result, factor);
        }
    }
    
    return result;
}

double ValueEvaluator::parseFactor(const std::string& expr, size_t& pos) {
    if (pos >= expr.length()) {
        throw std::invalid_argument("Unexpected end of expression");
    }
    
    // Handle unary minus/plus
    if (expr[pos] == '-') {
        pos++;
        return -parseFactor(expr, pos);
    } else if (expr[pos] == '+') {
        pos++;
        return parseFactor(expr, pos);
    }
    
    // Handle parentheses
    if (expr[pos] == '(') {
        pos++; // Skip '('
        double result = parseExpression(expr, pos);
        if (pos >= expr.length() || expr[pos] != ')') {
            throw std::invalid_argument("Missing closing parenthesis");
        }
        pos++; // Skip ')'
        return result;
    }
    
    // Handle numbers and variables
    return parseNumber(expr, pos);
}

double ValueEvaluator::parseNumber(const std::string& expr, size_t& pos) {
    size_t start = pos;
    
    // Handle variables/functions
    if (std::isalpha(expr[pos])) {
        while (pos < expr.length() && (std::isalnum(expr[pos]) || expr[pos] == '_')) {
            pos++;
        }
        
        std::string identifier = expr.substr(start, pos - start);
        
        // Check if it's a function
        if (isFunction(identifier)) {
            if (pos < expr.length() && expr[pos] == '(') {
                pos++; // Skip '('
                double arg = parseExpression(expr, pos);
                if (pos >= expr.length() || expr[pos] != ')') {
                    throw std::invalid_argument("Missing closing parenthesis for function");
                }
                pos++; // Skip ')'
                return performFunction(identifier, arg);
            } else {
                throw std::invalid_argument("Function requires parentheses: " + identifier);
            }
        }
        
        // It's a variable
        auto it = currentVariables.find(identifier);
        if (it != currentVariables.end()) {
            return it->second;
        } else {
            throw std::invalid_argument("Undefined variable: " + identifier);
        }
    }
    
    // Handle numbers
    if (!std::isdigit(expr[pos]) && expr[pos] != '.') {
        throw std::invalid_argument("Expected number or variable");
    }
    
    while (pos < expr.length() && (std::isdigit(expr[pos]) || expr[pos] == '.')) {
        pos++;
    }
    
    return std::stod(expr.substr(start, pos - start));
}