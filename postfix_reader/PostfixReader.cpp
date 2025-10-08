#include "PostfixReader.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cmath>

PostfixReader::PostfixReader() {
    // Initialize valid operators
    validOperators = {"+", "-", "*", "/", "^", "%", "mod", "div", "pow"};
    
    // Initialize built-in functions
    initializeBuiltInFunctions();
}

std::vector<Token> PostfixReader::readFromString(const std::string& expression) {
    std::vector<Token> tokens;
    std::vector<std::string> tokenStrings = splitIntoTokens(expression);
    
    for (const std::string& tokenStr : tokenStrings) {
        if (!tokenStr.empty()) {
            Token token = parseToken(tokenStr);
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

std::vector<Token> PostfixReader::readFromFile(const std::string& filename) {
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

std::vector<std::vector<Token>> PostfixReader::readMultipleFromFile(const std::string& filename) {
    std::vector<std::vector<Token>> allExpressions;
    std::vector<std::string> lines = readLinesFromFile(filename);
    
    for (const std::string& line : lines) {
        std::string trimmedLine = trim(line);
        if (!trimmedLine.empty() && trimmedLine[0] != '#') { // Skip empty lines and comments
            std::vector<Token> tokens = readFromString(trimmedLine);
            if (!tokens.empty()) {
                allExpressions.push_back(tokens);
            }
        }
    }
    
    return allExpressions;
}

bool PostfixReader::validatePostfixExpression(const std::vector<Token>& tokens) {
    if (tokens.empty()) {
        return false;
    }
    
    int operandCount = 0;
    
    for (const Token& token : tokens) {
        switch (token.type) {
            case TokenType::NUMBER:
            case TokenType::VARIABLE:
                operandCount++;
                break;
                
            case TokenType::OPERATOR:
                if (operandCount < 2) {
                    return false; // Not enough operands for binary operator
                }
                operandCount--; // Two operands become one result
                break;
                
            case TokenType::FUNCTION:
                if (operandCount < 1) {
                    return false; // Not enough operands for function
                }
                // Function takes one operand and produces one result (no change in count)
                break;
                
            case TokenType::INVALID:
                return false;
        }
    }
    
    return operandCount == 1; // Should have exactly one result
}

std::string PostfixReader::tokensToString(const std::vector<Token>& tokens) {
    std::string result;
    for (size_t i = 0; i < tokens.size(); ++i) {
        result += tokens[i].value;
        if (i < tokens.size() - 1) {
            result += " ";
        }
    }
    return result;
}

Token PostfixReader::parseToken(const std::string& tokenStr) {
    std::string cleanToken = trim(tokenStr);
    
    if (cleanToken.empty()) {
        return Token(TokenType::INVALID, cleanToken);
    }
    
    TokenType type = determineTokenType(cleanToken);
    
    if (type == TokenType::NUMBER) {
        try {
            double value = std::stod(cleanToken);
            return Token(type, cleanToken, value);
        } catch (const std::exception&) {
            return Token(TokenType::INVALID, cleanToken);
        }
    }
    
    return Token(type, cleanToken);
}

std::string PostfixReader::getTokenTypeString(TokenType type) {
    switch (type) {
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::OPERATOR: return "OPERATOR";
        case TokenType::FUNCTION: return "FUNCTION";
        case TokenType::VARIABLE: return "VARIABLE";
        case TokenType::INVALID: return "INVALID";
        default: return "UNKNOWN";
    }
}

void PostfixReader::setVariable(const std::string& name, double value) {
    variables[name] = value;
}

void PostfixReader::setVariables(const std::unordered_map<std::string, double>& vars) {
    for (const auto& pair : vars) {
        variables[pair.first] = pair.second;
    }
}

void PostfixReader::setFunction(const std::string& name, std::function<double(double)> func) {
    functions[name] = func;
}

double PostfixReader::getVariable(const std::string& name) const {
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    throw std::runtime_error("Undefined variable: " + name);
}

bool PostfixReader::isValidOperator(const std::string& token) const {
    return std::find(validOperators.begin(), validOperators.end(), token) != validOperators.end();
}

bool PostfixReader::isValidFunction(const std::string& token) const {
    return functions.find(token) != functions.end();
}

bool PostfixReader::isValidVariable(const std::string& token) const {
    return isValidIdentifier(token) && !isValidFunction(token) && !isValidOperator(token);
}

int PostfixReader::getOperatorPrecedence(const std::string& op) const {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/" || op == "%" || op == "mod" || op == "div") return 2;
    if (op == "^" || op == "pow") return 3;
    return 0;
}

void PostfixReader::displayTokens(const std::vector<Token>& tokens) const {
    std::cout << "\nToken Analysis:" << std::endl;
    std::cout << "===============" << std::endl;
    
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& token = tokens[i];
        std::cout << "Token " << (i + 1) << ": ";
        std::cout << "\"" << token.value << "\" ";
        std::cout << "(" << getTokenTypeString(token.type) << ")";
        
        if (token.type == TokenType::NUMBER) {
            std::cout << " = " << token.numericValue;
        } else if (token.type == TokenType::VARIABLE) {
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
    std::cout << "Valid postfix: " << (validatePostfixExpression(tokens) ? "YES" : "NO") << std::endl;
}

bool PostfixReader::validateWithDetails(const std::vector<Token>& tokens, std::string& errorMessage) {
    if (tokens.empty()) {
        errorMessage = "Empty expression";
        return false;
    }
    
    int operandCount = 0;
    
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& token = tokens[i];
        
        switch (token.type) {
            case TokenType::NUMBER:
            case TokenType::VARIABLE:
                operandCount++;
                break;
                
            case TokenType::OPERATOR:
                if (operandCount < 2) {
                    errorMessage = "Insufficient operands for operator '" + token.value + 
                                 "' at position " + std::to_string(i + 1);
                    return false;
                }
                operandCount--;
                break;
                
            case TokenType::FUNCTION:
                if (operandCount < 1) {
                    errorMessage = "Insufficient operands for function '" + token.value + 
                                 "' at position " + std::to_string(i + 1);
                    return false;
                }
                break;
                
            case TokenType::INVALID:
                errorMessage = "Invalid token '" + token.value + "' at position " + std::to_string(i + 1);
                return false;
        }
    }
    
    if (operandCount != 1) {
        if (operandCount == 0) {
            errorMessage = "Expression evaluates to no result";
        } else {
            errorMessage = "Expression has " + std::to_string(operandCount) + 
                         " unprocessed operands (should be exactly 1)";
        }
        return false;
    }
    
    errorMessage = "Valid postfix expression";
    return true;
}

bool PostfixReader::hasBalancedOperandsOperators(const std::vector<Token>& tokens) {
    auto counts = countOperandsAndOperators(tokens);
    int operands = counts.first;
    int operators = counts.second;
    
    // For a valid postfix expression: operands = operators + 1
    return operands == operators + 1;
}

std::pair<int, int> PostfixReader::countOperandsAndOperators(const std::vector<Token>& tokens) {
    int operands = 0;
    int operators = 0;
    
    for (const Token& token : tokens) {
        switch (token.type) {
            case TokenType::NUMBER:
            case TokenType::VARIABLE:
                operands++;
                break;
            case TokenType::OPERATOR:
                operators++;
                break;
            case TokenType::FUNCTION:
                // Functions don't change the operand/operator balance
                break;
            case TokenType::INVALID:
                break;
        }
    }
    
    return std::make_pair(operands, operators);
}

// Private helper functions
void PostfixReader::initializeBuiltInFunctions() {
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

bool PostfixReader::isNumber(const std::string& str) const {
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

bool PostfixReader::isValidIdentifier(const std::string& str) const {
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

TokenType PostfixReader::determineTokenType(const std::string& token) {
    if (isNumber(token)) {
        return TokenType::NUMBER;
    } else if (isValidOperator(token)) {
        return TokenType::OPERATOR;
    } else if (isValidFunction(token)) {
        return TokenType::FUNCTION;
    } else if (isValidIdentifier(token)) {
        return TokenType::VARIABLE;
    } else {
        return TokenType::INVALID;
    }
}

std::vector<std::string> PostfixReader::splitIntoTokens(const std::string& expression) {
    std::vector<std::string> tokens;
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string PostfixReader::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "";
    }
    
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

std::vector<std::string> PostfixReader::readLinesFromFile(const std::string& filename) {
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