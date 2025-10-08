#include "PostfixReader.h"
#include <iostream>
#include <fstream>

void testBasicReading() {
    std::cout << "\n=== Basic Reading Tests ===" << std::endl;
    
    PostfixReader reader;
    
    std::vector<std::string> testExpressions = {
        "3 4 +",
        "5 2 * 3 +",
        "10 2 / 3 4 * +",
        "2 3 ^ 4 +",
        "x y + z *",
        "3.14 2 * sin",
        "invalid token here",
        "",
        "3 4 + +",  // Invalid - too many operators
        "3 4 5 +",  // Invalid - too many operands
    };
    
    for (const std::string& expr : testExpressions) {
        std::cout << "\nExpression: \"" << expr << "\"" << std::endl;
        
        try {
            std::vector<Token> tokens = reader.readFromString(expr);
            reader.displayTokens(tokens);
            
            std::string errorMessage;
            bool valid = reader.validateWithDetails(tokens, errorMessage);
            std::cout << "Validation: " << errorMessage << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}

void testVariablesAndFunctions() {
    std::cout << "\n=== Variables and Functions Tests ===" << std::endl;
    
    PostfixReader reader;
    
    // Set some variables
    reader.setVariable("x", 5.0);
    reader.setVariable("y", 3.0);
    reader.setVariable("z", 2.0);
    reader.setVariable("pi", 3.14159);
    
    std::vector<std::string> testExpressions = {
        "x y +",
        "pi 2 * sin",
        "x sqrt y +",
        "z 2 ^ x +",
        "pi 4 / cos",
        "undefined_var 2 +",  // Should show undefined
    };
    
    for (const std::string& expr : testExpressions) {
        std::cout << "\nExpression: \"" << expr << "\"" << std::endl;
        
        try {
            std::vector<Token> tokens = reader.readFromString(expr);
            reader.displayTokens(tokens);
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}

void testFileReading() {
    std::cout << "\n=== File Reading Tests ===" << std::endl;
    
    // Create test files
    std::ofstream testFile("test_expressions.txt");
    testFile << "3 4 +\n";
    testFile << "5 2 * 7 +\n";
    testFile << "# This is a comment\n";
    testFile << "x y + z *\n";
    testFile << "\n";  // Empty line
    testFile << "2 3 ^ 1 +\n";
    testFile.close();
    
    std::ofstream singleFile("single_expression.txt");
    singleFile << "10 5 / 2 + 3 *";
    singleFile.close();
    
    PostfixReader reader;
    reader.setVariable("x", 10.0);
    reader.setVariable("y", 5.0);
    reader.setVariable("z", 2.0);
    
    try {
        // Test single expression from file
        std::cout << "\nReading single expression from file:" << std::endl;
        std::vector<Token> tokens = reader.readFromFile("single_expression.txt");
        reader.displayTokens(tokens);
        
        // Test multiple expressions from file
        std::cout << "\nReading multiple expressions from file:" << std::endl;
        std::vector<std::vector<Token>> allExpressions = reader.readMultipleFromFile("test_expressions.txt");
        
        for (size_t i = 0; i < allExpressions.size(); ++i) {
            std::cout << "\n--- Expression " << (i + 1) << " ---" << std::endl;
            reader.displayTokens(allExpressions[i]);
        }
        
    } catch (const std::exception& e) {
        std::cout << "File reading error: " << e.what() << std::endl;
    }
}

void testValidation() {
    std::cout << "\n=== Validation Tests ===" << std::endl;
    
    PostfixReader reader;
    
    std::vector<std::string> testCases = {
        "3 4 +",           // Valid
        "3 4 5 + *",       // Valid
        "3 4",             // Invalid - too many operands
        "3 + 4",           // Invalid - insufficient operands
        "3 4 + +",         // Invalid - too many operators
        "",                // Invalid - empty
        "3 4 + 5",         // Invalid - leftover operand
        "sin 3.14",        // Valid - function application
        "3 4 + sin",       // Valid - function on result
        "3 sin 4 +",       // Valid - function in middle
    };
    
    for (const std::string& expr : testCases) {
        std::cout << "\nTesting: \"" << expr << "\"" << std::endl;
        
        try {
            std::vector<Token> tokens = reader.readFromString(expr);
            
            std::string errorMessage;
            bool valid = reader.validateWithDetails(tokens, errorMessage);
            
            auto counts = reader.countOperandsAndOperators(tokens);
            
            std::cout << "  Tokens: " << tokens.size() << std::endl;
            std::cout << "  Operands: " << counts.first << ", Operators: " << counts.second << std::endl;
            std::cout << "  Balanced: " << (reader.hasBalancedOperandsOperators(tokens) ? "YES" : "NO") << std::endl;
            std::cout << "  Result: " << (valid ? "VALID" : "INVALID") << std::endl;
            std::cout << "  Message: " << errorMessage << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "  Error: " << e.what() << std::endl;
        }
    }
}

void interactiveMode() {
    std::cout << "\n=== Interactive Mode ===" << std::endl;
    std::cout << "Enter postfix expressions to analyze (or 'quit' to exit)" << std::endl;
    std::cout << "You can also set variables using: set varname value" << std::endl;
    
    PostfixReader reader;
    std::string input;
    
    while (true) {
        std::cout << "\nPostfix> ";
        std::getline(std::cin, input);
        
        if (input == "quit" || input == "exit") {
            break;
        }
        
        if (input.empty()) {
            continue;
        }
        
        // Check for variable setting
        if (input.substr(0, 4) == "set ") {
            std::istringstream iss(input.substr(4));
            std::string varName;
            double value;
            
            if (iss >> varName >> value) {
                reader.setVariable(varName, value);
                std::cout << "Set " << varName << " = " << value << std::endl;
            } else {
                std::cout << "Invalid syntax. Use: set varname value" << std::endl;
            }
            continue;
        }
        
        try {
            std::vector<Token> tokens = reader.readFromString(input);
            reader.displayTokens(tokens);
            
            std::string errorMessage;
            reader.validateWithDetails(tokens, errorMessage);
            
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}

int main() {
    std::cout << "Postfix Expression Reader and Parser" << std::endl;
    std::cout << "====================================" << std::endl;
    
    try {
        testBasicReading();
        testVariablesAndFunctions();
        testFileReading();
        testValidation();
        interactiveMode();
        
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
    
    // Clean up test files
    std::remove("test_expressions.txt");
    std::remove("single_expression.txt");
    
    std::cout << "\nProgram completed!" << std::endl;
    return 0;
}