#include "Queue.h"
#include <string>
#include <chrono>
#include <random>

// Queue utilities and algorithms
namespace QueueUtils {
    
    // Reverse a queue using recursion
    template<typename T>
    void reverseQueue(ArrayQueue<T>& queue) {
        if (queue.isEmpty()) return;
        
        T item = queue.dequeue();
        reverseQueue(queue);
        queue.enqueue(item);
    }
    
    template<typename T>
    void reverseQueue(LinkedQueue<T>& queue) {
        if (queue.isEmpty()) return;
        
        T item = queue.dequeue();
        reverseQueue(queue);
        queue.enqueue(item);
    }
    
    // Generate first n numbers using queue
    template<typename QueueType>
    void generateBinaryNumbers(int n) {
        if (n <= 0) return;
        
        QueueType queue;
        queue.enqueue("1");
        
        std::cout << "First " << n << " binary numbers:" << std::endl;
        for (int i = 0; i < n; ++i) {
            std::string front = queue.dequeue();
            std::cout << front << " ";
            
            queue.enqueue(front + "0");
            queue.enqueue(front + "1");
        }
        std::cout << std::endl;
    }
    
    // Interleave first and second half of queue
    template<typename T>
    void interleaveQueue(ArrayQueue<T>& queue) {
        if (queue.size() % 2 != 0) {
            std::cout << "Queue size must be even for interleaving" << std::endl;
            return;
        }
        
        int half = queue.size() / 2;
        ArrayQueue<T> temp;
        
        // Move first half to temp queue
        for (int i = 0; i < half; ++i) {
            temp.enqueue(queue.dequeue());
        }
        
        // Interleave: temp (first half) and queue (second half)
        for (int i = 0; i < half; ++i) {
            queue.enqueue(temp.dequeue());
            queue.enqueue(queue.dequeue());
        }
    }
    
    // Performance benchmark
    template<typename QueueType>
    void performanceBenchmark(int operations) {
        std::cout << "\n=== Performance Benchmark (" << operations << " operations) ===" << std::endl;
        
        QueueType queue;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);
        
        // Enqueue operations
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < operations; ++i) {
            queue.enqueue(dis(gen));
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Enqueue " << operations << " elements: " << duration.count() << " μs" << std::endl;
        
        // Dequeue operations
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < operations; ++i) {
            queue.dequeue();
        }
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Dequeue " << operations << " elements: " << duration.count() << " μs" << std::endl;
    }
}

// Test functions
void testArrayQueue() {
    std::cout << "\n========= ARRAY QUEUE TESTS =========" << std::endl;
    
    // Basic operations
    ArrayQueue<int> queue(5);
    std::cout << "\n--- Basic Operations ---" << std::endl;
    
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.displayDetails();
    
    std::cout << "Front: " << queue.front() << std::endl;
    std::cout << "Back: " << queue.back() << std::endl;
    
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
    queue.displayDetails();
    
    // Test resize
    std::cout << "\n--- Testing Resize ---" << std::endl;
    for (int i = 1; i <= 10; ++i) {
        queue.enqueue(i * 10);
    }
    queue.displayDetails();
    
    // Copy semantics
    std::cout << "\n--- Copy Semantics ---" << std::endl;
    ArrayQueue<int> copied_queue = queue;
    copied_queue.display();
    
    // Move semantics
    std::cout << "\n--- Move Semantics ---" << std::endl;
    ArrayQueue<int> moved_queue = std::move(copied_queue);
    moved_queue.display();
    copied_queue.display(); // Should be empty
    
    // Exception handling
    std::cout << "\n--- Exception Handling ---" << std::endl;
    ArrayQueue<int> empty_queue;
    try {
        empty_queue.dequeue();
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

void testLinkedQueue() {
    std::cout << "\n========= LINKED QUEUE TESTS =========" << std::endl;
    
    // Basic operations
    LinkedQueue<std::string> queue;
    std::cout << "\n--- Basic Operations ---" << std::endl;
    
    queue.enqueue("First");
    queue.enqueue("Second");
    queue.enqueue("Third");
    queue.display();
    
    std::cout << "Front: " << queue.front() << std::endl;
    std::cout << "Back: " << queue.back() << std::endl;
    std::cout << "Size: " << queue.size() << std::endl;
    
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
    queue.display();
    
    // Copy semantics
    std::cout << "\n--- Copy Semantics ---" << std::endl;
    LinkedQueue<std::string> copied_queue = queue;
    copied_queue.display();
    
    // Move semantics
    std::cout << "\n--- Move Semantics ---" << std::endl;
    LinkedQueue<std::string> moved_queue = std::move(copied_queue);
    moved_queue.display();
    copied_queue.display(); // Should be empty
    
    // Exception handling
    std::cout << "\n--- Exception Handling ---" << std::endl;
    LinkedQueue<std::string> empty_queue;
    try {
        empty_queue.front();
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

void testPriorityQueue() {
    std::cout << "\n========= PRIORITY QUEUE TESTS =========" << std::endl;
    
    PriorityQueue<int> pq;
    std::cout << "\n--- Basic Operations ---" << std::endl;
    
    pq.enqueue(30);
    pq.enqueue(10);
    pq.enqueue(50);
    pq.enqueue(20);
    pq.enqueue(40);
    
    pq.display();
    std::cout << "Top element: " << pq.top() << std::endl;
    
    std::cout << "\nDequeuing elements (highest priority first):" << std::endl;
    while (!pq.isEmpty()) {
        std::cout << pq.dequeue() << " ";
    }
    std::cout << std::endl;
}

void testQueueAlgorithms() {
    std::cout << "\n========= QUEUE ALGORITHMS TESTS =========" << std::endl;
    
    // Test binary number generation
    std::cout << "\n--- Binary Number Generation ---" << std::endl;
    QueueUtils::generateBinaryNumbers<ArrayQueue<std::string>>(10);
    
    // Test queue reversal
    std::cout << "\n--- Queue Reversal ---" << std::endl;
    ArrayQueue<int> queue;
    for (int i = 1; i <= 5; ++i) {
        queue.enqueue(i);
    }
    
    std::cout << "Original queue: ";
    queue.display();
    
    QueueUtils::reverseQueue(queue);
    std::cout << "Reversed queue: ";
    queue.display();
    
    // Test interleaving
    std::cout << "\n--- Queue Interleaving ---" << std::endl;
    ArrayQueue<int> interleave_queue;
    for (int i = 1; i <= 6; ++i) {
        interleave_queue.enqueue(i);
    }
    
    std::cout << "Original queue: ";
    interleave_queue.display();
    
    QueueUtils::interleaveQueue(interleave_queue);
    std::cout << "Interleaved queue: ";
    interleave_queue.display();
}

void performanceBenchmarks() {
    std::cout << "\n========= PERFORMANCE BENCHMARKS =========" << std::endl;
    
    const int operations = 100000;
    
    std::cout << "\nArray Queue:" << std::endl;
    QueueUtils::performanceBenchmark<ArrayQueue<int>>(operations);
    
    std::cout << "\nLinked Queue:" << std::endl;
    QueueUtils::performanceBenchmark<LinkedQueue<int>>(operations);
}