#include "PrefixReader.h"
#include <iostream>
#include <stack>
#include <cctype>
#include <cmath>

PrefixReader::PrefixReader() {
    // Initialize valid operators
    validOperators = {"+", "-", "*", "/", "^", "%", "mod", "div", "pow"};
    
    // Initialize built-in functions
    initializeBuiltInFunctions();
}

std::vector<PrefixToken> PrefixReader::readFromString(const std::string& expression) {
    std::vector<PrefixToken> tokens;
    std::vector<std::string> tokenStrings = splitIntoTokens(expression);
    
    for (const std::string& tokenStr : tokenStrings) {
        if (!tokenStr.empty()) {
            PrefixToken token = parseToken(tokenStr);
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

std::vector<PrefixToken> PrefixReader::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::string line;
    std::string expression;
    
    // Read all lines and concatenate
    while (std::getline(file, line)) {
        expression += line + " ";
    }
    
    file.close();
    return readFromString(expression);
}

std::vector<std::vector<PrefixToken>> PrefixReader::readMultipleFromFile(const std::string& filename) {
    std::vector<std::vector<PrefixToken>> allExpressions;
    std::vector<std::string> lines = readLinesFromFile(filename);
    
    for (const std::string& line : lines) {
        std::string trimmedLine = trim(line);
        if (!trimmedLine.empty() && trimmedLine[0] != '#') { // Skip empty lines and comments
            std::vector<PrefixToken> tokens = readFromString(trimmedLine);
            if (!tokens.empty()) {
                allExpressions.push_back(tokens);
            }
        }
    }
    
    return allExpressions;
}

bool PrefixReader::validatePrefixExpression(const std::vector<PrefixToken>& tokens) {
    if (tokens.empty()) {
        return false;
    }
    
    // In prefix notation, we evaluate from right to left
    // We need to ensure that every operator has enough operands to its right
    int operandCount = 0;
    
    // Process tokens from right to left
    for (int i = static_cast<int>(tokens.size()) - 1; i >= 0; --i) {
        const PrefixToken& token = tokens[i];
        
        switch (token.type) {
            case PrefixTokenType::NUMBER:
            case PrefixTokenType::VARIABLE:
                operandCount++;
                break;
                
            case PrefixTokenType::FUNCTION:
                if (operandCount < 1) {
                    return false; // Not enough operands for function
                }
                // Function consumes one operand and produces one result (no change in count)
                break;
                
            case PrefixTokenType::OPERATOR:
                if (operandCount < 2) {
                    return false; // Not enough operands for binary operator
                }
                operandCount--; // Two operands become one result
                break;
                
            case PrefixTokenType::INVALID:
                return false;
        }
    }
    
    return operandCount == 1; // Should have exactly one result
}

std::string PrefixReader::tokensToString(const std::vector<PrefixToken>& tokens) {
    std::string result;
    for (size_t i = 0; i < tokens.size(); ++i) {
        result += tokens[i].value;
        if (i < tokens.size() - 1) {
            result += " ";
        }
    }
    return result;
}

PrefixToken PrefixReader::parseToken(const std::string& tokenStr) {
    std::string cleanToken = trim(tokenStr);
    
    if (cleanToken.empty()) {
        return PrefixToken(PrefixTokenType::INVALID, cleanToken);
    }
    
    PrefixTokenType type = determineTokenType(cleanToken);
    
    if (type == PrefixTokenType::NUMBER) {
        try {
            double value = std::stod(cleanToken);
            return PrefixToken(type, cleanToken, value);
        } catch (const std::exception&) {
            return PrefixToken(PrefixTokenType::INVALID, cleanToken);
        }
    }
    
    return PrefixToken(type, cleanToken);
}

std::string PrefixReader::getTokenTypeString(PrefixTokenType type) {
    switch (type) {
        case PrefixTokenType::NUMBER: return "NUMBER";
        case PrefixTokenType::OPERATOR: return "OPERATOR";
        case PrefixTokenType::FUNCTION: return "FUNCTION";
        case PrefixTokenType::VARIABLE: return "VARIABLE";
        case PrefixTokenType::INVALID: return "INVALID";
        default: return "UNKNOWN";
    }
}

std::string PrefixReader::infixToPrefix(const std::string& infix) {
    // Algorithm: Reverse infix, swap parentheses, convert to postfix, then reverse result
    
    // Step 1: Reverse the infix expression and swap parentheses
    std::string reversedInfix;
    for (int i = static_cast<int>(infix.length()) - 1; i >= 0; --i) {
        char c = infix[i];
        if (c == '(') {
            reversedInfix += ')';
        } else if (c == ')') {
            reversedInfix += '(';
        } else {
            reversedInfix += c;
        }
    }
    
    // Step 2: Convert the reversed infix to postfix
    std::string postfix;
    std::stack<char> operators;
    
    for (size_t i = 0; i < reversedInfix.length(); ++i) {
        char c = reversedInfix[i];
        
        if (std::isspace(c)) {
            continue;
        } else if (std::isdigit(c) || c == '.') {
            // Add number to result
            while (i < reversedInfix.length() && 
                   (std::isdigit(reversedInfix[i]) || reversedInfix[i] == '.')) {
                postfix += reversedInfix[i];
                ++i;
            }
            postfix += ' ';
            --i; // Adjust for loop increment
        } else if (std::isalpha(c)) {
            // Add variable/function name to result
            while (i < reversedInfix.length() && 
                   (std::isalnum(reversedInfix[i]) || reversedInfix[i] == '_')) {
                postfix += reversedInfix[i];
                ++i;
            }
            postfix += ' ';
            --i; // Adjust for loop increment
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop(); // Remove '('
            }
        } else if (isValidOperator(std::string(1, c))) {
            // For prefix conversion, we need to handle right associativity differently
            while (!operators.empty() && 
                   operators.top() != '(' &&
                   getOperatorPrecedence(std::string(1, operators.top())) > getOperatorPrecedence(std::string(1, c))) {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            operators.push(c);
        }
    }
    
    while (!operators.empty()) {
        postfix += operators.top();
        postfix += ' ';
        operators.pop();
    }
    
    // Step 3: Reverse the postfix expression to get prefix
    std::vector<std::string> tokens = splitIntoTokens(postfix);
    std::reverse(tokens.begin(), tokens.end());
    
    std::string prefix;
    for (size_t i = 0; i < tokens.size(); ++i) {
        prefix += tokens[i];
        if (i < tokens.size() - 1) {
            prefix += " ";
        }
    }
    
    return prefix;
}

std::string PrefixReader::postfixToPrefix(const std::string& postfix) {
    std::vector<std::string> tokens = splitIntoTokens(postfix);
    std::stack<std::string> stack;
    
    for (const std::string& token : tokens) {
        if (isValidOperator(token)) {
            if (stack.size() < 2) {
                throw std::runtime_error("Invalid postfix expression");
            }
            
            std::string operand2 = stack.top(); stack.pop();
            std::string operand1 = stack.top(); stack.pop();
            
            std::string prefixExpr = token + " " + operand1 + " " + operand2;
            stack.push(prefixExpr);
        } else if (isValidFunction(token)) {
            if (stack.empty()) {
                throw std::runtime_error("Invalid postfix expression");
            }
            
            std::string operand = stack.top(); stack.pop();
            std::string prefixExpr = token + " " + operand;
            stack.push(prefixExpr);
        } else {
            stack.push(token);
        }
    }
    
    if (stack.size() != 1) {
        throw std::runtime_error("Invalid postfix expression");
    }
    
    return stack.top();
}

std::string PrefixReader::prefixToPostfix(const std::string& prefix) {
    std::vector<std::string> tokens = splitIntoTokens(prefix);
    std::stack<std::string> stack;
    
    // Process tokens from right to left
    for (int i = static_cast<int>(tokens.size()) - 1; i >= 0; --i) {
        const std::string& token = tokens[i];
        
        if (isValidOperator(token)) {
            if (stack.size() < 2) {
                throw std::runtime_error("Invalid prefix expression");
            }
            
            std::string operand1 = stack.top(); stack.pop();
            std::string operand2 = stack.top(); stack.pop();
            
            std::string postfixExpr = operand1 + " " + operand2 + " " + token;
            stack.push(postfixExpr);
        } else if (isValidFunction(token)) {
            if (stack.empty()) {
                throw std::runtime_error("Invalid prefix expression");
            }
            
            std::string operand = stack.top(); stack.pop();
            std::string postfixExpr = operand + " " + token;
            stack.push(postfixExpr);
        } else {
            stack.push(token);
        }
    }
    
    if (stack.size() != 1) {
        throw std::runtime_error("Invalid prefix expression");
    }
    
    return stack.top();
}

std::string PrefixReader::prefixToInfix(const std::string& prefix) {
    std::vector<PrefixToken> tokens = readFromString(prefix);
    int index = 0;
    ExprNode* tree = buildExpressionTree(tokens, index);
    
    if (tree == nullptr) {
        throw std::runtime_error("Failed to build expression tree");
    }
    
    std::string result = treeToInfix(tree);
    delete tree;
    
    return result;
}

double PrefixReader::evaluatePrefix(const std::vector<PrefixToken>& tokens) {
    if (!validatePrefixExpression(tokens)) {
        throw std::invalid_argument("Invalid prefix expression");
    }
    
    int index = 0;
    return evaluatePrefixRecursive(tokens, index);
}

double PrefixReader::evaluatePrefix(const std::string& prefix) {
    std::vector<PrefixToken> tokens = readFromString(prefix);
    return evaluatePrefix(tokens);
}

// Helper function implementations
void PrefixReader::setVariable(const std::string& name, double value) {
    variables[name] = value;
}

void PrefixReader::setVariables(const std::unordered_map<std::string, double>& vars) {
    for (const auto& pair : vars) {
        variables[pair.first] = pair.second;
    }
}

void PrefixReader::setFunction(const std::string& name, std::function<double(double)> func) {
    functions[name] = func;
}

double PrefixReader::getVariable(const std::string& name) const {
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    throw std::runtime_error("Undefined variable: " + name);
}

bool PrefixReader::isValidOperator(const std::string& token) const {
    return std::find(validOperators.begin(), validOperators.end(), token) != validOperators.end();
}

bool PrefixReader::isValidFunction(const std::string& token) const {
    return functions.find(token) != functions.end();
}

bool PrefixReader::isValidVariable(const std::string& token) const {
    return isValidIdentifier(token) && !isValidFunction(token) && !isValidOperator(token);
}

int PrefixReader::getOperatorPrecedence(const std::string& op) const {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/" || op == "%" || op == "mod" || op == "div") return 2;
    if (op == "^" || op == "pow") return 3;
    return 0;
}

bool PrefixReader::isRightAssociative(const std::string& op) const {
    return op == "^" || op == "pow";
}

void PrefixReader::displayTokens(const std::vector<PrefixToken>& tokens) const {
    std::cout << "\nPrefix Token Analysis:" << std::endl;
    std::cout << "=====================" << std::endl;
    
    for (size_t i = 0; i < tokens.size(); ++i) {
        const PrefixToken& token = tokens[i];
        std::cout << "Token " << (i + 1) << ": ";
        std::cout << "\"" << token.value << "\" ";
        std::cout << "(" << getTokenTypeString(token.type) << ")";
        
        if (token.type == PrefixTokenType::NUMBER) {
            std::cout << " = " << token.numericValue;
        } else if (token.type == PrefixTokenType::VARIABLE) {
            try {
                double value = getVariable(token.value);
                std::cout << " = " << value;
            } catch (const std::exception&) {
                std::cout << " = UNDEFINED";
            }
        }
        
        std::cout << std::endl;
    }
    
    std::cout << "\nExpression: " << tokensToString(tokens) << std::endl;
    std::cout << "Valid prefix: " << (validatePrefixExpression(tokens) ? "YES" : "NO") << std::endl;
}

// Continue with remaining implementations...
void PrefixReader::initializeBuiltInFunctions() {
    functions["sin"] = [](double x) { return std::sin(x); };
    functions["cos"] = [](double x) { return std::cos(x); };
    functions["tan"] = [](double x) { return std::tan(x); };
    functions["log"] = [](double x) { return std::log(x); };
    functions["ln"] = [](double x) { return std::log(x); };
    functions["log10"] = [](double x) { return std::log10(x); };
    functions["sqrt"] = [](double x) { return std::sqrt(x); };
    functions["abs"] = [](double x) { return std::abs(x); };
    functions["floor"] = [](double x) { return std::floor(x); };
    functions["ceil"] = [](double x) { return std::ceil(x); };
    functions["exp"] = [](double x) { return std::exp(x); };
    functions["asin"] = [](double x) { return std::asin(x); };
    functions["acos"] = [](double x) { return std::acos(x); };
    functions["atan"] = [](double x) { return std::atan(x); };
}

bool PrefixReader::isNumber(const std::string& str) const {
    if (str.empty()) return false;
    
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        start = 1;
        if (str.length() == 1) return false;
    }
    
    bool hasDecimal = false;
    for (size_t i = start; i < str.length(); ++i) {
        if (str[i] == '.') {
            if (hasDecimal) return false;
            hasDecimal = true;
        } else if (!std::isdigit(str[i])) {
            return false;
        }
    }
    
    return true;
}

bool PrefixReader::isValidIdentifier(const std::string& str) const {
    if (str.empty() || !std::isalpha(str[0])) {
        return false;
    }
    
    for (char c : str) {
        if (!std::isalnum(c) && c != '_') {
            return false;
        }
    }
    
    return true;
}

PrefixTokenType PrefixReader::determineTokenType(const std::string& token) {
    if (isNumber(token)) {
        return PrefixTokenType::NUMBER;
    } else if (isValidOperator(token)) {
        return PrefixTokenType::OPERATOR;
    } else if (isValidFunction(token)) {
        return PrefixTokenType::FUNCTION;
    } else if (isValidIdentifier(token)) {
        return PrefixTokenType::VARIABLE;
    } else {
        return PrefixTokenType::INVALID;
    }
}

std::vector<std::string> PrefixReader::splitIntoTokens(const std::string& expression) {
    std::vector<std::string> tokens;
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string PrefixReader::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "";
    }
    
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

std::vector<std::string> PrefixReader::readLinesFromFile(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    file.close();
    return lines;
}

double PrefixReader::evaluatePrefixRecursive(const std::vector<PrefixToken>& tokens, int& index) {
    if (index >= static_cast<int>(tokens.size())) {
        throw std::runtime_error("Unexpected end of expression");
    }
    
    const PrefixToken& token = tokens[index++];
    
    switch (token.type) {
        case PrefixTokenType::NUMBER:
            return token.numericValue;
            
        case PrefixTokenType::VARIABLE: {
            auto it = variables.find(token.value);
            if (it != variables.end()) {
                return it->second;
            } else {
                throw std::runtime_error("Undefined variable: " + token.value);
            }
        }
        
        case PrefixTokenType::FUNCTION: {
            double operand = evaluatePrefixRecursive(tokens, index);
            auto it = functions.find(token.value);
            if (it != functions.end()) {
                return it->second(operand);
            } else {
                throw std::runtime_error("Unknown function: " + token.value);
            }
        }
        
        case PrefixTokenType::OPERATOR: {
            double left = evaluatePrefixRecursive(tokens, index);
            double right = evaluatePrefixRecursive(tokens, index);
            
            if (token.value == "+") return left + right;
            if (token.value == "-") return left - right;
            if (token.value == "*") return left * right;
            if (token.value == "/" || token.value == "div") {
                if (right == 0) throw std::runtime_error("Division by zero");
                return left / right;
            }
            if (token.value == "^" || token.value == "pow") return std::pow(left, right);
            if (token.value == "%" || token.value == "mod") {
                if (right == 0) throw std::runtime_error("Modulo by zero");
                return std::fmod(left, right);
            }
            
            throw std::runtime_error("Unknown operator: " + token.value);
        }
        
        default:
            throw std::runtime_error("Invalid token type");
    }
}

PrefixReader::ExprNode* PrefixReader::buildExpressionTree(const std::vector<PrefixToken>& tokens, int& index) {
    if (index >= static_cast<int>(tokens.size())) {
        return nullptr;
    }
    
    const PrefixToken& token = tokens[index++];
    
    if (token.type == PrefixTokenType::OPERATOR) {
        ExprNode* node = new ExprNode(token.value, true);
        node->left = buildExpressionTree(tokens, index);
        node->right = buildExpressionTree(tokens, index);
        return node;
    } else if (token.type == PrefixTokenType::FUNCTION) {
        ExprNode* node = new ExprNode(token.value, true);
        node->left = buildExpressionTree(tokens, index);
        return node;
    } else {
        return new ExprNode(token.value, false);
    }
}

std::string PrefixReader::treeToInfix(ExprNode* node, int parentPrec) {
    if (node == nullptr) {
        return "";
    }
    
    if (!node->isOperator) {
        return node->value;
    }
    
    if (isValidFunction(node->value)) {
        return node->value + "(" + treeToInfix(node->left) + ")";
    }
    
    int currentPrec = getOperatorPrecedence(node->value);
    std::string result;
    
    if (currentPrec < parentPrec) {
        result += "(";
    }
    
    result += treeToInfix(node->left, currentPrec);
    result += " " + node->value + " ";
    result += treeToInfix(node->right, currentPrec);
    
    if (currentPrec < parentPrec) {
        result += ")";
    }
    
    return result;
}