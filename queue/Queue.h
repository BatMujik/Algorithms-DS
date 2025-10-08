#pragma once
#include <stdexcept>
#include <iostream>
#include <vector>

// Array-based Circular Queue implementation
template<typename T>
class ArrayQueue {
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

public:
    // Constructor
    explicit ArrayQueue(int initial_capacity = 10) 
        : capacity(initial_capacity), front_index(0), rear_index(0), current_size(0) {
        data = new T[capacity];
        std::cout << "ArrayQueue constructor called with capacity " << capacity << std::endl;
    }
    
    // Copy constructor
    ArrayQueue(const ArrayQueue& other) 
        : capacity(other.capacity), front_index(0), rear_index(other.current_size), current_size(other.current_size) {
        data = new T[capacity];
        for (int i = 0; i < current_size; ++i) {
            data[i] = other.data[(other.front_index + i) % other.capacity];
        }
        std::cout << "ArrayQueue copy constructor called" << std::endl;
    }
    
    // Move constructor
    ArrayQueue(ArrayQueue&& other) noexcept
        : data(other.data), capacity(other.capacity), 
          front_index(other.front_index), rear_index(other.rear_index), current_size(other.current_size) {
        other.data = nullptr;
        other.capacity = 0;
        other.front_index = 0;
        other.rear_index = 0;
        other.current_size = 0;
        std::cout << "ArrayQueue move constructor called" << std::endl;
    }
    
    // Copy assignment
    ArrayQueue& operator=(const ArrayQueue& other) {
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
        std::cout << "ArrayQueue copy assignment called" << std::endl;
        return *this;
    }
    
    // Move assignment
    ArrayQueue& operator=(ArrayQueue&& other) noexcept {
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
        std::cout << "ArrayQueue move assignment called" << std::endl;
        return *this;
    }
    
    // Destructor
    ~ArrayQueue() {
        delete[] data;
        std::cout << "ArrayQueue destructor called" << std::endl;
    }
    
    // Queue operations
    void enqueue(const T& value) {
        if (current_size == capacity) {
            resize();
        }
        
        data[rear_index] = value;
        rear_index = (rear_index + 1) % capacity;
        ++current_size;
    }
    
    void enqueue(T&& value) {
        if (current_size == capacity) {
            resize();
        }
        
        data[rear_index] = std::move(value);
        rear_index = (rear_index + 1) % capacity;
        ++current_size;
    }
    
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot dequeue from empty queue");
        }
        
        T value = std::move(data[front_index]);
        front_index = (front_index + 1) % capacity;
        --current_size;
        
        return value;
    }
    
    const T& front() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access front of empty queue");
        }
        return data[front_index];
    }
    
    T& front() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access front of empty queue");
        }
        return data[front_index];
    }
    
    const T& back() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access back of empty queue");
        }
        int back_index = (rear_index - 1 + capacity) % capacity;
        return data[back_index];
    }
    
    T& back() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access back of empty queue");
        }
        int back_index = (rear_index - 1 + capacity) % capacity;
        return data[back_index];
    }
    
    bool isEmpty() const {
        return current_size == 0;
    }
    
    int size() const {
        return current_size;
    }
    
    int getCapacity() const {
        return capacity;
    }
    
    void display() const {
        std::cout << "Queue (front to back): ";
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
        std::cout << "Queue Details:" << std::endl;
        std::cout << "  Size: " << current_size << "/" << capacity << std::endl;
        std::cout << "  Front index: " << front_index << std::endl;
        std::cout << "  Rear index: " << rear_index << std::endl;
        display();
    }
};

// Node for LinkedQueue
template<typename T>
class QueueNode {
public:
    T data;
    QueueNode<T>* next;
    
    QueueNode() : data{}, next(nullptr) {}
    explicit QueueNode(const T& value) : data(value), next(nullptr) {}
    explicit QueueNode(T&& value) : data(std::move(value)), next(nullptr) {}
    
    QueueNode(const QueueNode& other) : data(other.data), next(nullptr) {
        std::cout << "QueueNode copy constructor called" << std::endl;
    }
    
    QueueNode(QueueNode&& other) noexcept : data(std::move(other.data)), next(other.next) {
        other.next = nullptr;
        std::cout << "QueueNode move constructor called" << std::endl;
    }
    
    QueueNode& operator=(const QueueNode& other) {
        if (this != &other) {
            data = other.data;
            std::cout << "QueueNode copy assignment called" << std::endl;
        }
        return *this;
    }
    
    QueueNode& operator=(QueueNode&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            other.next = nullptr;
            std::cout << "QueueNode move assignment called" << std::endl;
        }
        return *this;
    }
    
    ~QueueNode() = default;
};

// Linked List-based Queue implementation
template<typename T>
class LinkedQueue {
private:
    QueueNode<T>* front_node;
    QueueNode<T>* rear_node;
    size_t current_size;
    
    void copyFrom(const LinkedQueue& other) {
        if (other.front_node == nullptr) {
            front_node = nullptr;
            rear_node = nullptr;
            current_size = 0;
            return;
        }
        
        front_node = new QueueNode<T>(other.front_node->data);
        QueueNode<T>* current = front_node;
        QueueNode<T>* otherCurrent = other.front_node->next;
        
        while (otherCurrent != nullptr) {
            current->next = new QueueNode<T>(otherCurrent->data);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
        
        rear_node = current;
        current_size = other.current_size;
    }
    
    void clear() {
        while (front_node != nullptr) {
            QueueNode<T>* temp = front_node;
            front_node = front_node->next;
            delete temp;
        }
        rear_node = nullptr;
        current_size = 0;
    }

public:
    // Default constructor
    LinkedQueue() : front_node(nullptr), rear_node(nullptr), current_size(0) {
        std::cout << "LinkedQueue default constructor called" << std::endl;
    }
    
    // Copy constructor
    LinkedQueue(const LinkedQueue& other) : front_node(nullptr), rear_node(nullptr), current_size(0) {
        copyFrom(other);
        std::cout << "LinkedQueue copy constructor called" << std::endl;
    }
    
    // Move constructor
    LinkedQueue(LinkedQueue&& other) noexcept 
        : front_node(other.front_node), rear_node(other.rear_node), current_size(other.current_size) {
        other.front_node = nullptr;
        other.rear_node = nullptr;
        other.current_size = 0;
        std::cout << "LinkedQueue move constructor called" << std::endl;
    }
    
    // Copy assignment
    LinkedQueue& operator=(const LinkedQueue& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
            std::cout << "LinkedQueue copy assignment called" << std::endl;
        }
        return *this;
    }
    
    // Move assignment
    LinkedQueue& operator=(LinkedQueue&& other) noexcept {
        if (this != &other) {
            clear();
            front_node = other.front_node;
            rear_node = other.rear_node;
            current_size = other.current_size;
            other.front_node = nullptr;
            other.rear_node = nullptr;
            other.current_size = 0;
            std::cout << "LinkedQueue move assignment called" << std::endl;
        }
        return *this;
    }
    
    // Destructor
    ~LinkedQueue() {
        clear();
        std::cout << "LinkedQueue destructor called" << std::endl;
    }
    
    // Queue operations
    void enqueue(const T& value) {
        QueueNode<T>* newNode = new QueueNode<T>(value);
        
        if (rear_node == nullptr) {
            front_node = rear_node = newNode;
        } else {
            rear_node->next = newNode;
            rear_node = newNode;
        }
        
        ++current_size;
    }
    
    void enqueue(T&& value) {
        QueueNode<T>* newNode = new QueueNode<T>(std::move(value));
        
        if (rear_node == nullptr) {
            front_node = rear_node = newNode;
        } else {
            rear_node->next = newNode;
            rear_node = newNode;
        }
        
        ++current_size;
    }
    
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot dequeue from empty queue");
        }
        
        QueueNode<T>* temp = front_node;
        T value = std::move(front_node->data);
        
        front_node = front_node->next;
        if (front_node == nullptr) {
            rear_node = nullptr;
        }
        
        delete temp;
        --current_size;
        
        return value;
    }
    
    const T& front() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access front of empty queue");
        }
        return front_node->data;
    }
    
    T& front() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access front of empty queue");
        }
        return front_node->data;
    }
    
    const T& back() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access back of empty queue");
        }
        return rear_node->data;
    }
    
    T& back() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access back of empty queue");
        }
        return rear_node->data;
    }
    
    bool isEmpty() const {
        return front_node == nullptr;
    }
    
    size_t size() const {
        return current_size;
    }
    
    void display() const {
        std::cout << "Queue (front to back): ";
        if (isEmpty()) {
            std::cout << "EMPTY";
        } else {
            QueueNode<T>* current = front_node;
            while (current != nullptr) {
                std::cout << current->data << " ";
                current = current->next;
            }
        }
        std::cout << std::endl;
    }
};

// Priority Queue implementation using heap
template<typename T>
class PriorityQueue {
private:
    std::vector<T> heap;
    
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] <= heap[parent]) break;
            
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
    }
    
    void heapifyDown(int index) {
        int size = static_cast<int>(heap.size());
        
        while (true) {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            
            if (left < size && heap[left] > heap[largest]) {
                largest = left;
            }
            
            if (right < size && heap[right] > heap[largest]) {
                largest = right;
            }
            
            if (largest == index) break;
            
            std::swap(heap[index], heap[largest]);
            index = largest;
        }
    }

public:
    PriorityQueue() {
        std::cout << "PriorityQueue constructor called" << std::endl;
    }
    
    ~PriorityQueue() {
        std::cout << "PriorityQueue destructor called" << std::endl;
    }
    
    void enqueue(const T& value) {
        heap.push_back(value);
        heapifyUp(static_cast<int>(heap.size()) - 1);
    }
    
    void enqueue(T&& value) {
        heap.push_back(std::move(value));
        heapifyUp(static_cast<int>(heap.size()) - 1);
    }
    
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot dequeue from empty priority queue");
        }
        
        T result = std::move(heap[0]);
        heap[0] = std::move(heap.back());
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return result;
    }
    
    const T& top() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot access top of empty priority queue");
        }
        return heap[0];
    }
    
    bool isEmpty() const {
        return heap.empty();
    }
    
    size_t size() const {
        return heap.size();
    }
    
    void display() const {
        std::cout << "Priority Queue (heap order): ";
        if (isEmpty()) {
            std::cout << "EMPTY";
        } else {
            for (const T& item : heap) {
                std::cout << item << " ";
            }
        }
        std::cout << std::endl;
    }
};