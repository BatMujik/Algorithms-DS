#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <functional>

// Node class for linked list with proper copy/move semantics
template<typename T>
class Node {
public:
    T data;
    Node<T>* next;
    
    // Constructors
    Node() : data{}, next(nullptr) {}
    explicit Node(const T& value) : data(value), next(nullptr) {}
    explicit Node(T&& value) : data(std::move(value)), next(nullptr) {}
    
    // Copy constructor
    Node(const Node& other) : data(other.data), next(nullptr) {
        std::cout << "Node copy constructor called" << std::endl;
    }
    
    // Move constructor
    Node(Node&& other) noexcept : data(std::move(other.data)), next(other.next) {
        other.next = nullptr;
        std::cout << "Node move constructor called" << std::endl;
    }
    
    // Copy assignment
    Node& operator=(const Node& other) {
        if (this != &other) {
            data = other.data;
            std::cout << "Node copy assignment called" << std::endl;
        }
        return *this;
    }
    
    // Move assignment
    Node& operator=(Node&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            other.next = nullptr;
            std::cout << "Node move assignment called" << std::endl;
        }
        return *this;
    }
    
    // Destructor
    ~Node() = default;
};

// Linked Stack implementation with copy/move semantics
template<typename T>
class LinkedStack {
private:
    Node<T>* top_;
    size_t size_;
    
    void copyFrom(const LinkedStack& other) {
        if (other.top_ == nullptr) {
            top_ = nullptr;
            size_ = 0;
            return;
        }
        
        top_ = new Node<T>(other.top_->data);
        Node<T>* current = top_;
        Node<T>* otherCurrent = other.top_->next;
        
        while (otherCurrent != nullptr) {
            current->next = new Node<T>(otherCurrent->data);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
        
        size_ = other.size_;
    }
    
    void clear() {
        while (top_ != nullptr) {
            Node<T>* temp = top_;
            top_ = top_->next;
            delete temp;
        }
        size_ = 0;
    }

public:
    // Default constructor
    LinkedStack() : top_(nullptr), size_(0) {
        std::cout << "LinkedStack default constructor called" << std::endl;
    }
    
    // Copy constructor
    LinkedStack(const LinkedStack& other) : top_(nullptr), size_(0) {
        copyFrom(other);
        std::cout << "LinkedStack copy constructor called" << std::endl;
    }
    
    // Move constructor
    LinkedStack(LinkedStack&& other) noexcept 
        : top_(other.top_), size_(other.size_) {
        other.top_ = nullptr;
        other.size_ = 0;
        std::cout << "LinkedStack move constructor called" << std::endl;
    }
    
    // Copy assignment
    LinkedStack& operator=(const LinkedStack& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
            std::cout << "LinkedStack copy assignment called" << std::endl;
        }
        return *this;
    }
    
    // Move assignment
    LinkedStack& operator=(LinkedStack&& other) noexcept {
        if (this != &other) {
            clear();
            top_ = other.top_;
            size_ = other.size_;
            other.top_ = nullptr;
            other.size_ = 0;
            std::cout << "LinkedStack move assignment called" << std::endl;
        }
        return *this;
    }
    
    // Destructor
    ~LinkedStack() {
        clear();
        std::cout << "LinkedStack destructor called" << std::endl;
    }
    
    // Stack operations
    void push(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top_;
        top_ = newNode;
        ++size_;
    }
    
    void push(T&& value) {
        Node<T>* newNode = new Node<T>(std::move(value));
        newNode->next = top_;
        top_ = newNode;
        ++size_;
    }
    
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot pop from empty stack");
        }
        
        Node<T>* temp = top_;
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
        Node<T>* current = top_;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

// Postfix Evaluator using LinkedStack
class PostfixLinkedEvaluator {
public:
    // Main evaluation function
    static double evaluate(const std::string& postfix);
    
    // Evaluate with variables
    static double evaluate(const std::string& postfix, const std::unordered_map<std::string, double>& variables);
    
    // Evaluate with functions and variables
    static double evaluateAdvanced(const std::string& postfix, 
                                 const std::unordered_map<std::string, double>& variables,
                                 const std::unordered_map<std::string, std::function<double(double)>>& functions);
    
    // Convert infix to postfix
    static std::string infixToPostfix(const std::string& infix);
    
    // Validate postfix expression
    static bool isValidPostfix(const std::string& postfix);
    
    // Get detailed validation result
    static bool validateWithDetails(const std::string& postfix, std::string& errorMessage);

private:
    // Helper functions
    static bool isOperator(char c);
    static bool isOperator(const std::string& token);
    static bool isFunction(const std::string& token);
    static bool isNumber(const std::string& token);
    static bool isVariable(const std::string& token);
    
    static int getPrecedence(char op);
    static bool isLeftAssociative(char op);
    
    static double performOperation(double a, double b, const std::string& op);
    static double performFunction(const std::string& func, double arg);
    
    static std::vector<std::string> tokenize(const std::string& expression);
    static std::string removeSpaces(const std::string& str);
    
    // Built-in functions
    static const std::unordered_map<std::string, std::function<double(double)>> builtInFunctions;
};