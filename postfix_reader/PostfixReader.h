#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <functional>

// Token types for postfix expressions
enum class TokenType {
    NUMBER,
    OPERATOR,
    FUNCTION,
    VARIABLE,
    INVALID
};

// Token structure
struct Token {
    TokenType type;
    std::string value;
    double numericValue;
    
    Token() : type(TokenType::INVALID), value(""), numericValue(0.0) {}
    Token(TokenType t, const std::string& v) : type(t), value(v), numericValue(0.0) {
        if (t == TokenType::NUMBER) {
            numericValue = std::stod(v);
        }
    }
    Token(TokenType t, const std::string& v, double num) : type(t), value(v), numericValue(num) {}
};

class PostfixReader {
public:
    // Constructor
    PostfixReader();
    
    // Read postfix expression from string
    std::vector<Token> readFromString(const std::string& expression);
    
    // Read postfix expression from file
    std::vector<Token> readFromFile(const std::string& filename);
    
    // Read multiple expressions from file (one per line)
    std::vector<std::vector<Token>> readMultipleFromFile(const std::string& filename);
    
    // Validate postfix expression
    bool validatePostfixExpression(const std::vector<Token>& tokens);
    
    // Convert tokens back to string
    std::string tokensToString(const std::vector<Token>& tokens);
    
    // Parse and validate individual token
    Token parseToken(const std::string& tokenStr);
    
    // Get token type as string
    std::string getTokenTypeString(TokenType type);
    
    // Set custom variables
    void setVariable(const std::string& name, double value);
    void setVariables(const std::unordered_map<std::string, double>& vars);
    
    // Set custom functions
    void setFunction(const std::string& name, std::function<double(double)> func);
    
    // Get variable value
    double getVariable(const std::string& name) const;
    
    // Check if token is valid operator
    bool isValidOperator(const std::string& token) const;
    
    // Check if token is valid function
    bool isValidFunction(const std::string& token) const;
    
    // Check if token is valid variable
    bool isValidVariable(const std::string& token) const;
    
    // Get operator precedence (for validation)
    int getOperatorPrecedence(const std::string& op) const;
    
    // Display token information
    void displayTokens(const std::vector<Token>& tokens) const;
    
    // Advanced validation with detailed error reporting
    bool validateWithDetails(const std::vector<Token>& tokens, std::string& errorMessage);
    
    // Check if expression has balanced operands and operators
    bool hasBalancedOperandsOperators(const std::vector<Token>& tokens);
    
    // Count operands and operators
    std::pair<int, int> countOperandsAndOperators(const std::vector<Token>& tokens);

private:
    // Internal variables and functions storage
    std::unordered_map<std::string, double> variables;
    std::unordered_map<std::string, std::function<double(double)>> functions;
    
    // Valid operators
    std::vector<std::string> validOperators;
    
    // Built-in functions
    void initializeBuiltInFunctions();
    
    // Helper functions
    bool isNumber(const std::string& str) const;
    bool isValidIdentifier(const std::string& str) const;
    TokenType determineTokenType(const std::string& token);
    
    // Tokenization helpers
    std::vector<std::string> splitIntoTokens(const std::string& expression);
    std::string trim(const std::string& str);
    
    // File reading helpers
    std::vector<std::string> readLinesFromFile(const std::string& filename);
};