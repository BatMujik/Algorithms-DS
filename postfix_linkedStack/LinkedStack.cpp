#include "LinkedStack.h"
#include <algorithm>
#include <cctype>

// Static member initialization
const std::unordered_map<std::string, std::function<double(double)>> PostfixLinkedEvaluator::builtInFunctions = {
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

double PostfixLinkedEvaluator::evaluate(const std::string& postfix) {
    std::unordered_map<std::string, double> emptyVars;
    return evaluate(postfix, emptyVars);
}

double PostfixLinkedEvaluator::evaluate(const std::string& postfix, const std::unordered_map<std::string, double>& variables) {
    return evaluateAdvanced(postfix, variables, builtInFunctions);
}

double PostfixLinkedEvaluator::evaluateAdvanced(const std::string& postfix, 
                                              const std::unordered_map<std::string, double>& variables,
                                              const std::unordered_map<std::string, std::function<double(double)>>& functions) {
    if (!isValidPostfix(postfix)) {
        throw std::invalid_argument("Invalid postfix expression");
    }
    
    LinkedStack<double> operandStack;
    std::vector<std::string> tokens = tokenize(postfix);
    
    for (const std::string& token : tokens) {
        if (isNumber(token)) {
            operandStack.push(std::stod(token));
        } else if (isVariable(token)) {
            auto it = variables.find(token);
            if (it != variables.end()) {
                operandStack.push(it->second);
            } else {
                throw std::runtime_error("Undefined variable: " + token);
            }
        } else if (isFunction(token)) {
            if (operandStack.isEmpty()) {
                throw std::runtime_error("Insufficient operands for function: " + token);
            }
            
            double arg = operandStack.pop();
            
            auto funcIt = functions.find(token);
            if (funcIt != functions.end()) {
                double result = funcIt->second(arg);
                operandStack.push(result);
            } else {
                throw std::runtime_error("Unknown function: " + token);
            }
        } else if (isOperator(token)) {
            if (operandStack.size() < 2) {
                throw std::runtime_error("Insufficient operands for operator: " + token);
            }
            
            double b = operandStack.pop();
            double a = operandStack.pop();
            
            double result = performOperation(a, b, token);
            operandStack.push(result);
        } else {
            throw std::invalid_argument("Unknown token: " + token);
        }
    }
    
    if (operandStack.size() != 1) {
        throw std::runtime_error("Invalid postfix expression: incorrect number of operands");
    }
    
    return operandStack.pop();
}

std::string PostfixLinkedEvaluator::infixToPostfix(const std::string& infix) {
    std::string result;
    LinkedStack<char> operatorStack;
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
            // Add variable/function name to result
            while (i < cleaned.length() && (std::isalnum(cleaned[i]) || cleaned[i] == '_')) {
                result += cleaned[i];
                ++i;
            }
            result += ' ';
            --i; // Adjust for loop increment
        } else if (c == '(') {
            operatorStack.push(c);
        } else if (c == ')') {
            while (!operatorStack.isEmpty() && operatorStack.top() != '(') {
                result += operatorStack.pop();
                result += ' ';
            }
            if (!operatorStack.isEmpty()) {
                operatorStack.pop(); // Remove '('
            }
        } else if (isOperator(c)) {
            while (!operatorStack.isEmpty() && 
                   operatorStack.top() != '(' &&
                   ((isLeftAssociative(c) && getPrecedence(operatorStack.top()) >= getPrecedence(c)) ||
                    (!isLeftAssociative(c) && getPrecedence(operatorStack.top()) > getPrecedence(c)))) {
                result += operatorStack.pop();
                result += ' ';
            }
            operatorStack.push(c);
        }
    }
    
    while (!operatorStack.isEmpty()) {
        result += operatorStack.pop();
        result += ' ';
    }
    
    // Remove trailing space
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    return result;
}

bool PostfixLinkedEvaluator::isValidPostfix(const std::string& postfix) {
    std::string errorMessage;
    return validateWithDetails(postfix, errorMessage);
}

bool PostfixLinkedEvaluator::validateWithDetails(const std::string& postfix, std::string& errorMessage) {
    std::vector<std::string> tokens = tokenize(postfix);
    
    if (tokens.empty()) {
        errorMessage = "Empty expression";
        return false;
    }
    
    int operandCount = 0;
    
    for (size_t i = 0; i < tokens.size(); ++i) {
        const std::string& token = tokens[i];
        
        if (isNumber(token) || isVariable(token)) {
            operandCount++;
        } else if (isFunction(token)) {
            if (operandCount < 1) {
                errorMessage = "Insufficient operands for function '" + token + "' at position " + std::to_string(i + 1);
                return false;
            }
            // Function doesn't change operand count (1 in, 1 out)
        } else if (isOperator(token)) {
            if (operandCount < 2) {
                errorMessage = "Insufficient operands for operator '" + token + "' at position " + std::to_string(i + 1);
                return false;
            }
            operandCount--; // Two operands become one result
        } else {
            errorMessage = "Invalid token '" + token + "' at position " + std::to_string(i + 1);
            return false;
        }
    }
    
    if (operandCount != 1) {
        if (operandCount == 0) {
            errorMessage = "Expression evaluates to no result";
        } else {
            errorMessage = "Expression has " + std::to_string(operandCount) + " unprocessed operands (should be exactly 1)";
        }
        return false;
    }
    
    errorMessage = "Valid postfix expression";
    return true;
}

// Helper function implementations
bool PostfixLinkedEvaluator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%';
}

bool PostfixLinkedEvaluator::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || 
           token == "^" || token == "%" || token == "mod" || token == "div" || token == "pow";
}

bool PostfixLinkedEvaluator::isFunction(const std::string& token) {
    return builtInFunctions.find(token) != builtInFunctions.end();
}

bool PostfixLinkedEvaluator::isNumber(const std::string& token) {
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

bool PostfixLinkedEvaluator::isVariable(const std::string& token) {
    if (token.empty() || !std::isalpha(token[0])) {
        return false;
    }
    
    for (char c : token) {
        if (!std::isalnum(c) && c != '_') {
            return false;
        }
    }
    
    return !isFunction(token) && !isOperator(token);
}

int PostfixLinkedEvaluator::getPrecedence(char op) {
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

bool PostfixLinkedEvaluator::isLeftAssociative(char op) {
    return op != '^'; // Only exponentiation is right associative
}

double PostfixLinkedEvaluator::performOperation(double a, double b, const std::string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/" || op == "div") {
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    }
    if (op == "^" || op == "pow") return std::pow(a, b);
    if (op == "%" || op == "mod") {
        if (b == 0) throw std::runtime_error("Modulo by zero");
        return std::fmod(a, b);
    }
    
    throw std::invalid_argument("Unknown operator: " + op);
}

double PostfixLinkedEvaluator::performFunction(const std::string& func, double arg) {
    auto it = builtInFunctions.find(func);
    if (it != builtInFunctions.end()) {
        return it->second(arg);
    }
    throw std::invalid_argument("Unknown function: " + func);
}

std::vector<std::string> PostfixLinkedEvaluator::tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string PostfixLinkedEvaluator::removeSpaces(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (c != ' ' && c != '\t') {
            result += c;
        }
    }
    return result;
}