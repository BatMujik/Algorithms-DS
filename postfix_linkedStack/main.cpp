#include "LinkedStack.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

void testCopyMoveSemantics() {
    std::cout << "\n=== Testing Copy/Move Semantics ===" << std::endl;
    
    std::cout << "\n1. Creating original stack:" << std::endl;
    LinkedStack<int> original;
    original.push(1);
    original.push(2);
    original.push(3);
    std::cout << "Original: ";
    original.display();
    
    std::cout << "\n2. Copy constructor:" << std::endl;
    LinkedStack<int> copied(original);
    std::cout << "Copied: ";
    copied.display();
    
    std::cout << "\n3. Move constructor:" << std::endl;
    LinkedStack<int> moved(std::move(copied));
    std::cout << "Moved: ";
    moved.display();
    std::cout << "Copied after move: ";
    copied.display();
    
    std::cout << "\n4. Copy assignment:" << std::endl;
    LinkedStack<int> assigned;
    assigned = original;
    std::cout << "Assigned: ";
    assigned.display();
    
    std::cout << "\n5. Move assignment:" << std::endl;
    LinkedStack<int> moveAssigned;
    moveAssigned = std::move(assigned);
    std::cout << "Move assigned: ";
    moveAssigned.display();
    std::cout << "Assigned after move: ";
    assigned.display();
}

void testBasicStackOperations() {
    std::cout << "\n=== Testing Basic Stack Operations ===" << std::endl;
    
    LinkedStack<double> stack;
    
    std::cout << "Empty stack size: " << stack.size() << std::endl;
    std::cout << "Is empty: " << (stack.isEmpty() ? "YES" : "NO") << std::endl;
    
    // Push some values
    std::cout << "\nPushing values: 1.5, 2.7, 3.14, 4.2" << std::endl;
    stack.push(1.5);
    stack.push(2.7);
    stack.push(3.14);
    stack.push(4.2);
    
    std::cout << "Stack size: " << stack.size() << std::endl;
    stack.display();
    
    // Pop some values
    std::cout << "\nPopping values:" << std::endl;
    while (!stack.isEmpty()) {
        std::cout << "Popped: " << stack.pop() << std::endl;
        std::cout << "Remaining size: " << stack.size() << std::endl;
    }
    
    try {
        stack.pop(); // Should throw exception
    } catch (const std::exception& e) {
        std::cout << "Expected exception: " << e.what() << std::endl;
    }
}

void testPostfixEvaluation() {
    std::cout << "\n=== Testing Postfix Evaluation ===" << std::endl;
    
    std::vector<std::string> testExpressions = {
        "3 4 +",                    // 7
        "5 2 * 3 +",               // 13
        "10 2 / 3 4 * +",          // 17
        "2 3 ^ 1 +",               // 9
        "15 7 1 1 + - / 3 * 2 1 1 + + -",  // 5
        "5 1 2 + 4 * + 3 -",       // 14
        "4 2 + 3 5 1 - * +",       // 18
    };
    
    for (const std::string& expr : testExpressions) {
        try {
            double result = PostfixLinkedEvaluator::evaluate(expr);
            std::cout << std::setw(25) << expr << " = " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << std::setw(25) << expr << " ERROR: " << e.what() << std::endl;
        }
    }
}

void testVariablesAndFunctions() {
    std::cout << "\n=== Testing Variables and Functions ===" << std::endl;
    
    std::unordered_map<std::string, double> variables = {
        {"x", 3.0},
        {"y", 4.0},
        {"z", 2.0},
        {"pi", 3.14159}
    };
    
    std::vector<std::string> testExpressions = {
        "x y +",                   // 7
        "x y * z +",              // 14
        "pi 2 /",                 // 1.5708
        "x 2 ^ y 2 ^ + sqrt",     // 5 (3^2 + 4^2 = 25, sqrt(25) = 5)
        "pi sin",                 // ~0
        "x y + z * abs",          // 14
        "undefined_var 2 +",      // Should error
    };
    
    for (const std::string& expr : testExpressions) {
        try {
            double result = PostfixLinkedEvaluator::evaluate(expr, variables);
            std::cout << std::setw(25) << expr << " = " << std::fixed << std::setprecision(4) << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << std::setw(25) << expr << " ERROR: " << e.what() << std::endl;
        }
    }
}

void testInfixToPostfix() {
    std::cout << "\n=== Testing Infix to Postfix Conversion ===" << std::endl;
    
    std::vector<std::string> infixExpressions = {
        "3 + 4",
        "3 + 4 * 2",
        "(3 + 4) * 2",
        "3 + 4 * 2 - 1",
        "2 ^ 3 ^ 2",
        "a + b * c",
        "((a + b) * c - d) / e",
    };
    
    for (const std::string& infix : infixExpressions) {
        try {
            std::string postfix = PostfixLinkedEvaluator::infixToPostfix(infix);
            std::cout << std::setw(20) << infix << " -> " << postfix << std::endl;
        } catch (const std::exception& e) {
            std::cout << std::setw(20) << infix << " ERROR: " << e.what() << std::endl;
        }
    }
}

void testValidation() {
    std::cout << "\n=== Testing Expression Validation ===" << std::endl;
    
    std::vector<std::string> testExpressions = {
        "3 4 +",           // Valid
        "3 4 5 + *",       // Valid
        "3 4",             // Invalid - too many operands
        "3 + 4",           // Invalid - infix format
        "3 4 + +",         // Invalid - too many operators
        "",                // Invalid - empty
        "3 4 + 5",         // Invalid - leftover operand
        "sin 3.14",        // Valid - function application
        "3 4 + sin",       // Valid - function on result
    };
    
    for (const std::string& expr : testExpressions) {
        std::string errorMessage;
        bool valid = PostfixLinkedEvaluator::validateWithDetails(expr, errorMessage);
        
        std::cout << std::setw(15) << "\"" + expr + "\"" << " -> " 
                  << (valid ? "VALID" : "INVALID") << " (" << errorMessage << ")" << std::endl;
    }
}

void testErrorHandling() {
    std::cout << "\n=== Testing Error Handling ===" << std::endl;
    
    std::vector<std::string> errorCases = {
        "5 0 /",           // Division by zero
        "5 0 %",           // Modulo by zero
        "invalid token",   // Invalid token
        "3 4 + +",         // Too many operators
        "3 4 5",           // Too many operands
    };
    
    for (const std::string& expr : errorCases) {
        std::cout << "\nTesting: \"" << expr << "\"" << std::endl;
        try {
            double result = PostfixLinkedEvaluator::evaluate(expr);
            std::cout << "  Unexpected success: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "  Expected error: " << e.what() << std::endl;
        }
    }
}

void performanceComparison() {
    std::cout << "\n=== Performance Comparison ===" << std::endl;
    
    std::string complexExpression = "3 4 + 5 6 + * 7 8 + 9 10 + * + 2 3 + 4 5 + * -";
    const int iterations = 100000;
    
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        double result = PostfixLinkedEvaluator::evaluate(complexExpression);
        (void)result; // Suppress unused variable warning
    }
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Expression: " << complexExpression << std::endl;
    std::cout << "Iterations: " << iterations << std::endl;
    std::cout << "Total time: " << duration.count() << " μs" << std::endl;
    std::cout << "Average time per evaluation: " << (duration.count() / static_cast<double>(iterations)) << " μs" << std::endl;
    
    // Single evaluation for result verification
    double result = PostfixLinkedEvaluator::evaluate(complexExpression);
    std::cout << "Result: " << result << std::endl;
}

void interactiveMode() {
    std::cout << "\n=== Interactive Mode ===" << std::endl;
    std::cout << "Enter postfix expressions to evaluate (or 'quit' to exit)" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  set var value  - Set variable" << std::endl;
    std::cout << "  infix expr     - Convert infix to postfix" << std::endl;
    std::cout << "  help          - Show this help" << std::endl;
    
    std::unordered_map<std::string, double> variables;
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
        
        if (input == "help") {
            std::cout << "Commands:" << std::endl;
            std::cout << "  set var value  - Set variable" << std::endl;
            std::cout << "  infix expr     - Convert infix to postfix" << std::endl;
            std::cout << "  help          - Show this help" << std::endl;
            std::cout << "  quit/exit     - Exit program" << std::endl;
            continue;
        }
        
        if (input.substr(0, 4) == "set ") {
            std::istringstream iss(input.substr(4));
            std::string varName;
            double value;
            
            if (iss >> varName >> value) {
                variables[varName] = value;
                std::cout << "Set " << varName << " = " << value << std::endl;
            } else {
                std::cout << "Invalid syntax. Use: set varname value" << std::endl;
            }
            continue;
        }
        
        if (input.substr(0, 6) == "infix ") {
            try {
                std::string postfix = PostfixLinkedEvaluator::infixToPostfix(input.substr(6));
                std::cout << "Postfix: " << postfix << std::endl;
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            continue;
        }
        
        // Evaluate as postfix expression
        try {
            double result = PostfixLinkedEvaluator::evaluate(input, variables);
            std::cout << "Result: " << std::fixed << std::setprecision(6) << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}

int main() {
    std::cout << "Postfix Expression Evaluator with Linked Stack" << std::endl;
    std::cout << "===============================================" << std::endl;
    
    try {
        testCopyMoveSemantics();
        testBasicStackOperations();
        testPostfixEvaluation();
        testVariablesAndFunctions();
        testInfixToPostfix();
        testValidation();
        testErrorHandling();
        performanceComparison();
        interactiveMode();
        
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}