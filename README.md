# Data Structures and Algorithms Collection

This repository contains a comprehensive collection of data structures and algorithms implemented in C++, organized into separate folders for easy navigation and learning.

## Project Structure

```
algo_ds/
├── fibonacci/                     # Fibonacci implementations (4 approaches)
├── postfix_expression/           # Complete postfix system with linked stack
├── is_balanced_brackets/         # Bracket balancing checker
├── palindrome/                   # Palindrome checker (multiple approaches)
├── value_eval/                   # Expression evaluator
├── postfix_arrayStack/          # Postfix evaluation with array-based stack
├── postfix_linkedStack/         # Postfix evaluation with linked list stack
├── postfix_reader/              # Postfix expression parser
├── prefix_arrayStack/           # Prefix evaluation with array-based stack
├── prefix_linkedStack/          # Prefix evaluation with linked list stack
├── prefix_reader/               # Prefix expression parser
├── queue/                       # Queue implementations (array & linked)
├── wave_algorithm/              # Wave algorithm for pathfinding
├── deque/                       # Double-ended queue implementation
└── array_based_stack/           # Original array-based stack
```

## Implemented Components

### ✅ Completed

1. **Fibonacci Sequence** (`fibonacci/`)
   - Iterative approach: O(n) time, O(1) space
   - Recursive approach: O(2^n) time, O(n) space
   - Dynamic Programming with memoization: O(n) time, O(n) space
   - Matrix exponentiation: O(log n) time, O(1) space
   - Comprehensive performance testing and comparison

2. **Postfix Expression System** (`postfix_expression/`)
   - Linked list-based stack with full copy/move semantics
   - Infix to postfix conversion with operator precedence
   - Postfix expression evaluation
   - Comprehensive input validation and error handling
   - Interactive testing mode

3. **Balanced Brackets Checker** (`is_balanced_brackets/`)
   - Multiple bracket types: (), [], {}, <>
   - Detailed error reporting with position information
   - Selective bracket type checking
   - Extract brackets from mixed text
   - Interactive validation mode

4. **Palindrome Checker** (`palindrome/`)
   - Multiple algorithms: reverse, two-pointer, stack-based, recursive
   - Case-insensitive checking
   - Alphanumeric-only palindromes
   - Longest palindromic substring
   - Palindromic substring counting
   - Number palindrome checking
   - Linked list palindrome detection

5. **Expression Evaluator** (`value_eval/`)
   - Recursive descent parser
   - Variable substitution support
   - Built-in mathematical functions (sin, cos, log, sqrt, etc.)
   - Infix to postfix conversion
   - Complex expression evaluation with parentheses
   - Comprehensive error handling

6. **Postfix Reader** (`postfix_reader/`)
   - Advanced postfix expression parsing and tokenization
   - Token validation with detailed error reporting
   - File input support for single and multiple expressions
   - Variable and function management
   - Expression structure validation
   - Interactive parsing mode

7. **Postfix Linked Stack** (`postfix_linkedStack/`)
   - Linked list-based stack for postfix evaluation
   - Full copy/move semantics implementation
   - Memory-efficient node-based storage
   - Variable and function support
   - Infix to postfix conversion
   - Performance benchmarking

8. **Prefix Reader** (`prefix_reader/`)
   - Complete prefix expression parsing system
   - Prefix to postfix/infix conversion algorithms
   - Expression tree building for complex conversions
   - Recursive evaluation with proper precedence
   - Advanced token analysis and validation
   - Multiple format support (prefix ↔ infix ↔ postfix)

9. **Prefix Array Stack** (`prefix_arrayStack/`)
   - Array-based stack with dynamic resizing
   - Copy/move constructor semantics
   - Prefix expression evaluation
   - Memory-efficient array storage

10. **Prefix Linked Stack** (`prefix_linkedStack/`)
    - Linked list-based stack for prefix evaluation
    - Node-based memory management
    - Full semantic support for modern C++
    - Comprehensive prefix expression handling

### 🚧 Planned Components

### 🚧 Remaining Components

11. **Postfix Array Stack** (`postfix_arrayStack/`)
    - Array-based stack implementation with dynamic resizing
    - Copy/move constructor semantics  
    - Postfix expression evaluation

12. **Queue System** (`queue/`)
    - Array-based circular queue
    - Linked list-based queue
    - Priority queue implementation
    - Queue operations and utilities

13. **Wave Algorithm** (`wave_algorithm/`)
    - Pathfinding algorithm implementation
    - Grid-based shortest path calculation
    - Obstacle avoidance
    - Visualization support

14. **Deque (Double-ended Queue)** (`deque/`)
    - Insertion/deletion at both ends
    - Array-based implementation
    - Linked list-based implementation
    - STL-compatible interface

## Features Across All Components

### 🎯 Core Features
- **Copy/Move Semantics**: Proper implementation of the Rule of 5
- **Memory Management**: Safe allocation and deallocation
- **Error Handling**: Comprehensive exception handling with descriptive messages
- **Performance Testing**: Timing comparisons between different approaches
- **Interactive Modes**: User-friendly testing interfaces
- **Comprehensive Testing**: Multiple test cases covering edge cases

### 🛠️ Implementation Highlights
- **Template-based**: Generic implementations where applicable
- **RAII Principles**: Resource Acquisition Is Initialization
- **Modern C++**: C++17 features and best practices
- **Documentation**: Detailed comments and usage examples
- **Modular Design**: Each component is self-contained

## Building and Running

### Prerequisites
- C++17 compatible compiler (g++, clang++, MSVC)
- Windows/Linux/macOS

### Compilation
Each folder contains its own implementation. To compile any component:

```bash
cd [component_folder]
g++ -std=c++17 -Wall -Wextra -g -o main *.cpp
./main
```

### Example Usage

```cpp
// Fibonacci example
#include "fibonacci.h"
long long result = fibMatrix(50);  // Fast O(log n) calculation

// Palindrome example
#include "PalindromeChecker.h"
bool isPalin = PalindromeChecker::isPalindromeAlphanumeric("A man a plan a canal Panama");

// Bracket balancing example
#include "BracketBalancer.h"
bool balanced = BracketBalancer::isBalanced("({[]})");

// Expression evaluation example
#include "ValueEvaluator.h"
double result = ValueEvaluator::evaluate("2 + 3 * sin(0.5)");
```

## Educational Value

This collection serves as:
- **Learning Resource**: Multiple implementations of the same concept
- **Algorithm Comparison**: Performance analysis between different approaches
- **Best Practices**: Modern C++ implementation patterns
- **Problem Solving**: Real-world algorithmic challenges

## Contributing

Each component is designed to be:
1. **Self-contained**: Independent of other components
2. **Well-documented**: Clear interface and implementation
3. **Tested**: Comprehensive test cases
4. **Performant**: Optimized implementations

## Future Enhancements

- [ ] Unit test framework integration
- [ ] Benchmarking suite
- [ ] Visualization tools
- [ ] Additional algorithms (sorting, searching, graphs)
- [ ] Thread-safe implementations
- [ ] Custom allocator support

## Time Complexities Summary

| Component | Operation | Best Case | Average Case | Worst Case | Space |
|-----------|-----------|-----------|--------------|------------|-------|
| Fibonacci (Matrix) | Calculate F(n) | O(log n) | O(log n) | O(log n) | O(1) |
| Palindrome (Two-pointer) | Check | O(n) | O(n) | O(n) | O(1) |
| Bracket Balance | Validate | O(n) | O(n) | O(n) | O(n) |
| Postfix Evaluation | Evaluate | O(n) | O(n) | O(n) | O(n) |
| Expression Parser | Parse & Eval | O(n) | O(n) | O(n) | O(n) |

This collection provides a solid foundation for understanding fundamental data structures and algorithms while demonstrating modern C++ programming practices.