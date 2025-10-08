#pragma once
#include <stdexcept>
#include <iostream>
#include <vector>

// Array-based Circular Deque implementation
template<typename T>
class ArrayDeque {
private:
    T* data;
    int capacity;
    int front_index;
    int rear_index;
    int current_size;
    
    void resize() {
        int new_capacity = capacity * 2;
        T* new_data = new T[new_capacity];
        
        // Copy elements in correct order
        for (int i = 0; i < current_size; ++i) {
            new_data[i] = std::move(data[(front_index + i) % capacity]);
        }
        
        delete[] data;
        data = new_data;
        capacity = new_capacity;
        front_index = 0;
        rear_index = current_size;
    }
    
    int getPrevIndex(int index) const {
        return (index - 1 + capacity) % capacity;
    }
    
    int getNextIndex(int index) const {
        return (index + 1) % capacity;
    }

public:
    // Constructor
    explicit ArrayDeque(int initial_capacity = 10) 
        : capacity(initial_capacity), front_index(0), rear_index(0), current_size(0) {
        data = new T[capacity];
        std::cout << "ArrayDeque constructor called with capacity " << capacity << std::endl;
    }
    
    // Copy constructor
    ArrayDeque(const ArrayDeque& other) 
        : capacity(other.capacity), front_index(0), rear_index(other.current_size), current_size(other.current_size) {
        data = new T[capacity];
        for (int i = 0; i < current_size; ++i) {
            data[i] = other.data[(other.front_index + i) % other.capacity];
        }
        std::cout << "ArrayDeque copy constructor called" << std::endl;
    }
    
    // Move constructor
    ArrayDeque(ArrayDeque&& other) noexcept
        : data(other.data), capacity(other.capacity), 
          front_index(other.front_index), rear_index(other.rear_index), current_size(other.current_size) {
        other.data = nullptr;
        other.capacity = 0;
        other.front_index = 0;
        other.rear_index = 0;
        other.current_size = 0;
        std::cout << "ArrayDeque move constructor called" << std::endl;
    }
    
    // Copy assignment
    ArrayDeque& operator=(const ArrayDeque& other) {
        if (this != &other) {
            delete[] data;
            
            capacity = other.capacity;
            current_size = other.current_size;
            front_index = 0;
            rear_index = current_size;
            data = new T[capacity];
            
            for (int i = 0; i < current_size; ++i) {
                data[i] = other.data[(other.front_index + i) % other.capacity];
            }
        }
        std::cout << "ArrayDeque copy assignment called" << std::endl;
        return *this;
    }
    
    // Move assignment
    ArrayDeque& operator=(ArrayDeque&& other) noexcept {
        if (this != &other) {
            delete[] data;
            
            data = other.data;
            capacity = other.capacity;
            front_index = other.front_index;
            rear_index = other.rear_index;
            current_size = other.current_size;
            
            other.data = nullptr;
            other.capacity = 0;
            other.front_index = 0;
            other.rear_index = 0;
            other.current_size = 0;
        }
        std::cout << "ArrayDeque move assignment called" << std::endl;
        return *this;
    }
    
    // Destructor
    ~ArrayDeque() {
        delete[] data;
        std::cout << "ArrayDeque destructor called" << std::endl;
    }
    
    // Front operations
    void pushFront(const T& value) {
        if (current_size == capacity) {
            resize();
        }
        
        front_index = getPrevIndex(front_index);
        data[front_index] = value;
        ++current_size;
        
        if (current_size == 1) {
            rear_index = getNextIndex(front_index);
        }
    }
    
    void pushFront(T&& value) {
        if (current_size == capacity) {
            resize();
        }
        
        front_index = getPrevIndex(front_index);
        data[front_index] = std::move(value);
        ++current_size;
        
        if (current_size == 1) {
            rear_index = getNextIndex(front_index);
        }
    }
    
    T popFront() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot pop from empty deque");
        }
        
        T value = std::move(data[front_index]);
        front_index = getNextIndex(front_index);
        --current_size;
        
        return value;
    }
    
    // Back operations
    void pushBack(const T& value) {
        if (current_size == capacity) {
            resize();
        }
        
        data[rear_index] = value;
        rear_index = getNextIndex(rear_index);
        ++current_size;
    }
    
    void pushBack(T&& value) {
        if (current_size == capacity) {
            resize();
        }
        
        data[rear_index] = std::move(value);
        rear_index = getNextIndex(rear_index);
        ++current_size;
    }
    
    T popBack() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot pop from empty deque");
        }
        
        rear_index = getPrevIndex(rear_index);
        T value = std::move(data[rear_index]);
        --current_size;
        
        return value;
    }
    
    // Access operations
    const T& front() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access front of empty deque");
        }
        return data[front_index];
    }
    
    T& front() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access front of empty deque");
        }
        return data[front_index];
    }
    
    const T& back() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access back of empty deque");
        }
        int back_index = getPrevIndex(rear_index);
        return data[back_index];
    }
    
    T& back() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access back of empty deque");
        }
        int back_index = getPrevIndex(rear_index);
        return data[back_index];
    }
    
    // Random access operator
    const T& operator[](int index) const {
        if (index < 0 || index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return data[(front_index + index) % capacity];
    }
    
    T& operator[](int index) {
        if (index < 0 || index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return data[(front_index + index) % capacity];
    }
    
    const T& at(int index) const {
        return (*this)[index];
    }
    
    T& at(int index) {
        return (*this)[index];
    }
    
    // Utility operations
    bool isEmpty() const {
        return current_size == 0;
    }
    
    int size() const {
        return current_size;
    }
    
    int getCapacity() const {
        return capacity;
    }
    
    void clear() {
        current_size = 0;
        front_index = 0;
        rear_index = 0;
    }
    
    void display() const {
        std::cout << "Deque (front to back): ";
        if (isEmpty()) {
            std::cout << "EMPTY";
        } else {
            for (int i = 0; i < current_size; ++i) {
                std::cout << data[(front_index + i) % capacity] << " ";
            }
        }
        std::cout << std::endl;
    }
    
    void displayDetails() const {
        std::cout << "Deque Details:" << std::endl;
        std::cout << "  Size: " << current_size << "/" << capacity << std::endl;
        std::cout << "  Front index: " << front_index << std::endl;
        std::cout << "  Rear index: " << rear_index << std::endl;
        display();
    }
    
    void displayReverse() const {
        std::cout << "Deque (back to front): ";
        if (isEmpty()) {
            std::cout << "EMPTY";
        } else {
            for (int i = current_size - 1; i >= 0; --i) {
                std::cout << data[(front_index + i) % capacity] << " ";
            }
        }
        std::cout << std::endl;
    }
};

// Node for LinkedDeque
template<typename T>
class DequeNode {
public:
    T data;
    DequeNode<T>* next;
    DequeNode<T>* prev;
    
    DequeNode() : data{}, next(nullptr), prev(nullptr) {}
    explicit DequeNode(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    explicit DequeNode(T&& value) : data(std::move(value)), next(nullptr), prev(nullptr) {}
    
    DequeNode(const DequeNode& other) : data(other.data), next(nullptr), prev(nullptr) {
        std::cout << "DequeNode copy constructor called" << std::endl;
    }
    
    DequeNode(DequeNode&& other) noexcept : data(std::move(other.data)), next(other.next), prev(other.prev) {
        other.next = nullptr;
        other.prev = nullptr;
        std::cout << "DequeNode move constructor called" << std::endl;
    }
    
    DequeNode& operator=(const DequeNode& other) {
        if (this != &other) {
            data = other.data;
            std::cout << "DequeNode copy assignment called" << std::endl;
        }
        return *this;
    }
    
    DequeNode& operator=(DequeNode&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            other.next = nullptr;
            other.prev = nullptr;
            std::cout << "DequeNode move assignment called" << std::endl;
        }
        return *this;
    }
    
    ~DequeNode() = default;
};

// Doubly Linked List-based Deque implementation
template<typename T>
class LinkedDeque {
private:
    DequeNode<T>* front_node;
    DequeNode<T>* rear_node;
    size_t current_size;
    
    void copyFrom(const LinkedDeque& other) {
        if (other.front_node == nullptr) {
            front_node = nullptr;
            rear_node = nullptr;
            current_size = 0;
            return;
        }
        
        front_node = new DequeNode<T>(other.front_node->data);
        DequeNode<T>* current = front_node;
        DequeNode<T>* otherCurrent = other.front_node->next;
        
        while (otherCurrent != nullptr) {
            current->next = new DequeNode<T>(otherCurrent->data);
            current->next->prev = current;
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
        
        rear_node = current;
        current_size = other.current_size;
    }
    
    void clear() {
        while (front_node != nullptr) {
            DequeNode<T>* temp = front_node;
            front_node = front_node->next;
            delete temp;
        }
        rear_node = nullptr;
        current_size = 0;
    }

public:
    // Default constructor
    LinkedDeque() : front_node(nullptr), rear_node(nullptr), current_size(0) {
        std::cout << "LinkedDeque default constructor called" << std::endl;
    }
    
    // Copy constructor
    LinkedDeque(const LinkedDeque& other) : front_node(nullptr), rear_node(nullptr), current_size(0) {
        copyFrom(other);
        std::cout << "LinkedDeque copy constructor called" << std::endl;
    }
    
    // Move constructor
    LinkedDeque(LinkedDeque&& other) noexcept 
        : front_node(other.front_node), rear_node(other.rear_node), current_size(other.current_size) {
        other.front_node = nullptr;
        other.rear_node = nullptr;
        other.current_size = 0;
        std::cout << "LinkedDeque move constructor called" << std::endl;
    }
    
    // Copy assignment
    LinkedDeque& operator=(const LinkedDeque& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
            std::cout << "LinkedDeque copy assignment called" << std::endl;
        }
        return *this;
    }
    
    // Move assignment
    LinkedDeque& operator=(LinkedDeque&& other) noexcept {
        if (this != &other) {
            clear();
            front_node = other.front_node;
            rear_node = other.rear_node;
            current_size = other.current_size;
            other.front_node = nullptr;
            other.rear_node = nullptr;
            other.current_size = 0;
            std::cout << "LinkedDeque move assignment called" << std::endl;
        }
        return *this;
    }
    
    // Destructor
    ~LinkedDeque() {
        clear();
        std::cout << "LinkedDeque destructor called" << std::endl;
    }
    
    // Front operations
    void pushFront(const T& value) {
        DequeNode<T>* newNode = new DequeNode<T>(value);
        
        if (front_node == nullptr) {
            front_node = rear_node = newNode;
        } else {
            newNode->next = front_node;
            front_node->prev = newNode;
            front_node = newNode;
        }
        
        ++current_size;
    }
    
    void pushFront(T&& value) {
        DequeNode<T>* newNode = new DequeNode<T>(std::move(value));
        
        if (front_node == nullptr) {
            front_node = rear_node = newNode;
        } else {
            newNode->next = front_node;
            front_node->prev = newNode;
            front_node = newNode;
        }
        
        ++current_size;
    }
    
    T popFront() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot pop from empty deque");
        }
        
        DequeNode<T>* temp = front_node;
        T value = std::move(front_node->data);
        
        front_node = front_node->next;
        if (front_node != nullptr) {
            front_node->prev = nullptr;
        } else {
            rear_node = nullptr;
        }
        
        delete temp;
        --current_size;
        
        return value;
    }
    
    // Back operations
    void pushBack(const T& value) {
        DequeNode<T>* newNode = new DequeNode<T>(value);
        
        if (rear_node == nullptr) {
            front_node = rear_node = newNode;
        } else {
            rear_node->next = newNode;
            newNode->prev = rear_node;
            rear_node = newNode;
        }
        
        ++current_size;
    }
    
    void pushBack(T&& value) {
        DequeNode<T>* newNode = new DequeNode<T>(std::move(value));
        
        if (rear_node == nullptr) {
            front_node = rear_node = newNode;
        } else {
            rear_node->next = newNode;
            newNode->prev = rear_node;
            rear_node = newNode;
        }
        
        ++current_size;
    }
    
    T popBack() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot pop from empty deque");
        }
        
        DequeNode<T>* temp = rear_node;
        T value = std::move(rear_node->data);
        
        rear_node = rear_node->prev;
        if (rear_node != nullptr) {
            rear_node->next = nullptr;
        } else {
            front_node = nullptr;
        }
        
        delete temp;
        --current_size;
        
        return value;
    }
    
    // Access operations
    const T& front() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access front of empty deque");
        }
        return front_node->data;
    }
    
    T& front() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access front of empty deque");
        }
        return front_node->data;
    }
    
    const T& back() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access back of empty deque");
        }
        return rear_node->data;
    }
    
    T& back() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access back of empty deque");
        }
        return rear_node->data;
    }
    
    // Random access operator (O(n) complexity)
    const T& operator[](int index) const {
        if (index < 0 || index >= static_cast<int>(current_size)) {
            throw std::out_of_range("Index out of range");
        }
        
        DequeNode<T>* current;
        if (index < static_cast<int>(current_size) / 2) {
            // Start from front
            current = front_node;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
        } else {
            // Start from back
            current = rear_node;
            for (int i = static_cast<int>(current_size) - 1; i > index; --i) {
                current = current->prev;
            }
        }
        
        return current->data;
    }
    
    T& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(current_size)) {
            throw std::out_of_range("Index out of range");
        }
        
        DequeNode<T>* current;
        if (index < static_cast<int>(current_size) / 2) {
            // Start from front
            current = front_node;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
        } else {
            // Start from back
            current = rear_node;
            for (int i = static_cast<int>(current_size) - 1; i > index; --i) {
                current = current->prev;
            }
        }
        
        return current->data;
    }
    
    const T& at(int index) const {
        return (*this)[index];
    }
    
    T& at(int index) {
        return (*this)[index];
    }
    
    // Utility operations
    bool isEmpty() const {
        return front_node == nullptr;
    }
    
    size_t size() const {
        return current_size;
    }
    
    void clear() {
        while (front_node != nullptr) {
            DequeNode<T>* temp = front_node;
            front_node = front_node->next;
            delete temp;
        }
        rear_node = nullptr;
        current_size = 0;
    }
    
    void display() const {
        std::cout << "Deque (front to back): ";
        if (isEmpty()) {
            std::cout << "EMPTY";
        } else {
            DequeNode<T>* current = front_node;
            while (current != nullptr) {
                std::cout << current->data << " ";
                current = current->next;
            }
        }
        std::cout << std::endl;
    }
    
    void displayReverse() const {
        std::cout << "Deque (back to front): ";
        if (isEmpty()) {
            std::cout << "EMPTY";
        } else {
            DequeNode<T>* current = rear_node;
            while (current != nullptr) {
                std::cout << current->data << " ";
                current = current->prev;
            }
        }
        std::cout << std::endl;
    }
};