#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <functional>
#include <vector>

// Node class for linked list with proper copy/move semantics
template<typename T>
class PrefixNode {
public:
    T data;
    PrefixNode<T>* next;
    
    // Constructors
    PrefixNode() : data{}, next(nullptr) {}
    explicit PrefixNode(const T& value) : data(value), next(nullptr) {}
    explicit PrefixNode(T&& value) : data(std::move(value)), next(nullptr) {}
    
    // Copy constructor
    PrefixNode(const PrefixNode& other) : data(other.data), next(nullptr) {
        std::cout << "PrefixNode copy constructor called" << std::endl;
    }
    
    // Move constructor
    PrefixNode(PrefixNode&& other) noexcept : data(std::move(other.data)), next(other.next) {
        other.next = nullptr;
        std::cout << "PrefixNode move constructor called" << std::endl;
    }
    
    // Copy assignment
    PrefixNode& operator=(const PrefixNode& other) {
        if (this != &other) {
            data = other.data;
            std::cout << "PrefixNode copy assignment called" << std::endl;
        }
        return *this;
    }
    
    // Move assignment
    PrefixNode& operator=(PrefixNode&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            other.next = nullptr;
            std::cout << "PrefixNode move assignment called" << std::endl;
        }
        return *this;
    }
    
    // Destructor
    ~PrefixNode() = default;
};

// Linked Stack implementation for prefix evaluation
template<typename T>
class PrefixLinkedStack {
private:
    PrefixNode<T>* top_;
    size_t size_;
    
    void copyFrom(const PrefixLinkedStack& other) {
        if (other.top_ == nullptr) {
            top_ = nullptr;
            size_ = 0;
            return;
        }
        
        top_ = new PrefixNode<T>(other.top_->data);
        PrefixNode<T>* current = top_;
        PrefixNode<T>* otherCurrent = other.top_->next;
        
        while (otherCurrent != nullptr) {
            current->next = new PrefixNode<T>(otherCurrent->data);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
        
        size_ = other.size_;
    }
    
    void clear() {
        while (top_ != nullptr) {
            PrefixNode<T>* temp = top_;
            top_ = top_->next;
            delete temp;
        }
        size_ = 0;
    }

public:
    // Default constructor
    PrefixLinkedStack() : top_(nullptr), size_(0) {
        std::cout << "PrefixLinkedStack default constructor called" << std::endl;
    }
    
    // Copy constructor
    PrefixLinkedStack(const PrefixLinkedStack& other) : top_(nullptr), size_(0) {
        copyFrom(other);
        std::cout << "PrefixLinkedStack copy constructor called" << std::endl;
    }
    
    // Move constructor
    PrefixLinkedStack(PrefixLinkedStack&& other) noexcept 
        : top_(other.top_), size_(other.size_) {
        other.top_ = nullptr;
        other.size_ = 0;
        std::cout << "PrefixLinkedStack move constructor called" << std::endl;
    }
    
    // Copy assignment
    PrefixLinkedStack& operator=(const PrefixLinkedStack& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
            std::cout << "PrefixLinkedStack copy assignment called" << std::endl;
        }
        return *this;
    }
    
    // Move assignment
    PrefixLinkedStack& operator=(PrefixLinkedStack&& other) noexcept {
        if (this != &other) {
            clear();
            top_ = other.top_;
            size_ = other.size_;
            other.top_ = nullptr;
            other.size_ = 0;
            std::cout << "PrefixLinkedStack move assignment called" << std::endl;
        }
        return *this;
    }
    
    // Destructor
    ~PrefixLinkedStack() {
        clear();
        std::cout << "PrefixLinkedStack destructor called" << std::endl;
    }
    
    // Stack operations
    void push(const T& value) {
        PrefixNode<T>* newNode = new PrefixNode<T>(value);
        newNode->next = top_;
        top_ = newNode;
        ++size_;
    }
    
    void push(T&& value) {
        PrefixNode<T>* newNode = new PrefixNode<T>(std::move(value));
        newNode->next = top_;
        top_ = newNode;
        ++size_;
    }
    
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot pop from empty stack");
        }
        
        PrefixNode<T>* temp = top_;
        T value = std::move(top_->data);
        top_ = top_->next;
        delete temp;
        --size_;
        
        return value;
    }
    
    const T& top() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access top of empty stack");
        }
        return top_->data;
    }
    
    T& top() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access top of empty stack");
        }
        return top_->data;
    }
    
    bool isEmpty() const {
        return top_ == nullptr;
    }
    
    size_t size() const {
        return size_;
    }
    
    void display() const {
        std::cout << "Stack (top to bottom): ";
        PrefixNode<T>* current = top_;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

// Prefix Evaluator using LinkedStack
class PrefixLinkedEvaluator {
public:
    // Main evaluation function
    static double evaluate(const std::string& prefix);
    
    // Evaluate with variables
    static double evaluate(const std::string& prefix, const std::unordered_map<std::string, double>& variables);
    
    // Convert prefix to postfix
    static std::string prefixToPostfix(const std::string& prefix);
    
    // Convert prefix to infix
    static std::string prefixToInfix(const std::string& prefix);
    
    // Validate prefix expression
    static bool isValidPrefix(const std::string& prefix);
    
    // Get detailed validation result
    static bool validateWithDetails(const std::string& prefix, std::string& errorMessage);

private:
    // Helper functions
    static bool isOperator(const std::string& token);
    static bool isFunction(const std::string& token);
    static bool isNumber(const std::string& token);
    static bool isVariable(const std::string& token);
    
    static double performOperation(double a, double b, const std::string& op);
    static double performFunction(const std::string& func, double arg);
    
    static std::vector<std::string> tokenize(const std::string& expression);
    
    // Built-in functions
    static const std::unordered_map<std::string, std::function<double(double)>> builtInFunctions;
};