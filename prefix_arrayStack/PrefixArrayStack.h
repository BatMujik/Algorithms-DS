#pragma once
#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <functional>

template<typename T>
class PrefixArrayStack {
private:
    T* data;
    int capacity;
    int top_index;
    
    void resize() {
        int new_capacity = capacity * 2;
        T* new_data = new T[new_capacity];
        
        for (int i = 0; i <= top_index; ++i) {
            new_data[i] = std::move(data[i]);
        }
        
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    // Constructor
    explicit PrefixArrayStack(int initial_capacity = 10) 
        : capacity(initial_capacity), top_index(-1) {
        data = new T[capacity];
        std::cout << "PrefixArrayStack constructor called with capacity " << capacity << std::endl;
    }
    
    // Copy constructor
    PrefixArrayStack(const PrefixArrayStack& other) 
        : capacity(other.capacity), top_index(other.top_index) {
        data = new T[capacity];
        for (int i = 0; i <= top_index; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "PrefixArrayStack copy constructor called" << std::endl;
    }
    
    // Move constructor
    PrefixArrayStack(PrefixArrayStack&& other) noexcept
        : data(other.data), capacity(other.capacity), top_index(other.top_index) {
        other.data = nullptr;
        other.capacity = 0;
        other.top_index = -1;
        std::cout << "PrefixArrayStack move constructor called" << std::endl;
    }
    
    // Copy assignment
    PrefixArrayStack& operator=(const PrefixArrayStack& other) {
        if (this != &other) {
            delete[] data;
            
            capacity = other.capacity;
            top_index = other.top_index;
            data = new T[capacity];
            
            for (int i = 0; i <= top_index; ++i) {
                data[i] = other.data[i];
            }
        }
        std::cout << "PrefixArrayStack copy assignment called" << std::endl;
        return *this;
    }
    
    // Move assignment
    PrefixArrayStack& operator=(PrefixArrayStack&& other) noexcept {
        if (this != &other) {
            delete[] data;
            
            data = other.data;
            capacity = other.capacity;
            top_index = other.top_index;
            
            other.data = nullptr;
            other.capacity = 0;
            other.top_index = -1;
        }
        std::cout << "PrefixArrayStack move assignment called" << std::endl;
        return *this;
    }
    
    // Destructor
    ~PrefixArrayStack() {
        delete[] data;
        std::cout << "PrefixArrayStack destructor called" << std::endl;
    }
    
    // Stack operations
    void push(const T& value) {
        if (top_index + 1 >= capacity) {
            resize();
        }
        data[++top_index] = value;
    }
    
    void push(T&& value) {
        if (top_index + 1 >= capacity) {
            resize();
        }
        data[++top_index] = std::move(value);
    }
    
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot pop from empty stack");
        }
        return std::move(data[top_index--]);
    }
    
    const T& top() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access top of empty stack");
        }
        return data[top_index];
    }
    
    T& top() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access top of empty stack");
        }
        return data[top_index];
    }
    
    bool isEmpty() const {
        return top_index == -1;
    }
    
    int size() const {
        return top_index + 1;
    }
    
    int getCapacity() const {
        return capacity;
    }
    
    void display() const {
        std::cout << "Stack (bottom to top): ";
        for (int i = 0; i <= top_index; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

// Prefix Evaluator using Array Stack
class PrefixArrayEvaluator {
public:
    static double evaluate(const std::string& prefix);
    static double evaluate(const std::string& prefix, const std::unordered_map<std::string, double>& variables);
    static std::string prefixToPostfix(const std::string& prefix);
    static std::string prefixToInfix(const std::string& prefix);
    static bool isValidPrefix(const std::string& prefix);
    
private:
    static bool isOperator(const std::string& token);
    static bool isFunction(const std::string& token);
    static bool isNumber(const std::string& token);
    static bool isVariable(const std::string& token);
    static double performOperation(double a, double b, const std::string& op);
    static double performFunction(const std::string& func, double arg);
    static std::vector<std::string> tokenize(const std::string& expression);
    
    static const std::unordered_map<std::string, std::function<double(double)>> builtInFunctions;
};