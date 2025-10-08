#pragma once
#include <stdexcept>
#include <iostream>

template<typename T>
class ArrayStack {
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
    explicit ArrayStack(int initial_capacity = 10) 
        : capacity(initial_capacity), top_index(-1) {
        data = new T[capacity];
        std::cout << "ArrayStack constructor called with capacity " << capacity << std::endl;
    }
    
    // Copy constructor
    ArrayStack(const ArrayStack& other) 
        : capacity(other.capacity), top_index(other.top_index) {
        data = new T[capacity];
        for (int i = 0; i <= top_index; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "ArrayStack copy constructor called" << std::endl;
    }
    
    // Move constructor
    ArrayStack(ArrayStack&& other) noexcept
        : data(other.data), capacity(other.capacity), top_index(other.top_index) {
        other.data = nullptr;
        other.capacity = 0;
        other.top_index = -1;
        std::cout << "ArrayStack move constructor called" << std::endl;
    }
    
    // Copy assignment
    ArrayStack& operator=(const ArrayStack& other) {
        if (this != &other) {
            delete[] data;
            
            capacity = other.capacity;
            top_index = other.top_index;
            data = new T[capacity];
            
            for (int i = 0; i <= top_index; ++i) {
                data[i] = other.data[i];
            }
        }
        std::cout << "ArrayStack copy assignment called" << std::endl;
        return *this;
    }
    
    // Move assignment
    ArrayStack& operator=(ArrayStack&& other) noexcept {
        if (this != &other) {
            delete[] data;
            
            data = other.data;
            capacity = other.capacity;
            top_index = other.top_index;
            
            other.data = nullptr;
            other.capacity = 0;
            other.top_index = -1;
        }
        std::cout << "ArrayStack move assignment called" << std::endl;
        return *this;
    }
    
    // Destructor
    ~ArrayStack() {
        delete[] data;
        std::cout << "ArrayStack destructor called" << std::endl;
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

// PostfixEvaluator using ArrayStack
class PostfixArrayEvaluator {
public:
    static double evaluate(const std::string& postfix);
    static bool isOperator(char c);
    static double performOperation(double a, double b, char op);
    static std::string infixToPostfix(const std::string& infix);
    
private:
    static int getPrecedence(char op);
    static bool isLeftAssociative(char op);
};