#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <algorithm>

// Token types for prefix expressions
enum class PrefixTokenType {
    NUMBER,
    OPERATOR,
    FUNCTION,
    VARIABLE,
    INVALID
};

// Token structure for prefix expressions
struct PrefixToken {
    PrefixTokenType type;
    std::string value;
    double numericValue;
    
    PrefixToken() : type(PrefixTokenType::INVALID), value(""), numericValue(0.0) {}
    PrefixToken(PrefixTokenType t, const std::string& v) : type(t), value(v), numericValue(0.0) {
        if (t == PrefixTokenType::NUMBER) {
            numericValue = std::stod(v);
        }
    }
    PrefixToken(PrefixTokenType t, const std::string& v, double num) : type(t), value(v), numericValue(num) {}
};

class PrefixReader {
public:
    // Constructor
    PrefixReader();
    
    // Read prefix expression from string
    std::vector<PrefixToken> readFromString(const std::string& expression);
    
    // Read prefix expression from file
    std::vector<PrefixToken> readFromFile(const std::string& filename);
    
    // Read multiple expressions from file (one per line)
    std::vector<std::vector<PrefixToken>> readMultipleFromFile(const std::string& filename);
    
    // Validate prefix expression
    bool validatePrefixExpression(const std::vector<PrefixToken>& tokens);
    
    // Convert tokens back to string
    std::string tokensToString(const std::vector<PrefixToken>& tokens);
    
    // Parse and validate individual token
    PrefixToken parseToken(const std::string& tokenStr);
    
    // Get token type as string
    std::string getTokenTypeString(PrefixTokenType type);
    
    // Convert infix to prefix
    std::string infixToPrefix(const std::string& infix);
    
    // Convert postfix to prefix
    std::string postfixToPrefix(const std::string& postfix);
    
    // Convert prefix to postfix
    std::string prefixToPostfix(const std::string& prefix);
    
    // Convert prefix to infix (with minimal parentheses)
    std::string prefixToInfix(const std::string& prefix);
    
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
    
    // Get operator precedence
    int getOperatorPrecedence(const std::string& op) const;
    
    // Check if operator is right associative
    bool isRightAssociative(const std::string& op) const;
    
    // Display token information
    void displayTokens(const std::vector<PrefixToken>& tokens) const;
    
    // Advanced validation with detailed error reporting
    bool validateWithDetails(const std::vector<PrefixToken>& tokens, std::string& errorMessage);
    
    // Check if expression has correct operand/operator ratio for prefix
    bool hasCorrectPrefixStructure(const std::vector<PrefixToken>& tokens);
    
    // Count operands and operators
    std::pair<int, int> countOperandsAndOperators(const std::vector<PrefixToken>& tokens);
    
    // Evaluate prefix expression (basic evaluation)
    double evaluatePrefix(const std::vector<PrefixToken>& tokens);
    double evaluatePrefix(const std::string& prefix);

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
    PrefixTokenType determineTokenType(const std::string& token);
    
    // Tokenization helpers
    std::vector<std::string> splitIntoTokens(const std::string& expression);
    std::string trim(const std::string& str);
    
    // File reading helpers
    std::vector<std::string> readLinesFromFile(const std::string& filename);
    
    // Conversion helpers
    std::string reverseString(const std::string& str);
    std::vector<std::string> reverseTokens(const std::vector<std::string>& tokens);
    char getOppositeParenthesis(char paren);
    
    // Recursive evaluation helpers
    double evaluatePrefixRecursive(const std::vector<PrefixToken>& tokens, int& index);
    
    // Expression tree helpers for infix conversion
    struct ExprNode {
        std::string value;
        ExprNode* left;
        ExprNode* right;
        bool isOperator;
        
        ExprNode(const std::string& val, bool isOp = false) 
            : value(val), left(nullptr), right(nullptr), isOperator(isOp) {}
        
        ~ExprNode() {
            delete left;
            delete right;
        }
    };
    
    ExprNode* buildExpressionTree(const std::vector<PrefixToken>& tokens, int& index);
    std::string treeToInfix(ExprNode* node, int parentPrec = -1);
};