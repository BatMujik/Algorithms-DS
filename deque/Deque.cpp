#include "Deque.h"
#include <string>
#include <chrono>
#include <random>
#include <algorithm>

// Deque utilities and algorithms
namespace DequeUtils {
    
    // Sliding window maximum using deque
    template<typename T>
    std::vector<T> slidingWindowMaximum(const std::vector<T>& arr, int window_size) {
        std::vector<T> result;
        if (arr.empty() || window_size <= 0 || window_size > static_cast<int>(arr.size())) {
            return result;
        }
        
        ArrayDeque<int> deque; // Store indices
        
        // Process first window
        for (int i = 0; i < window_size; ++i) {
            // Remove elements smaller than current element from rear
            while (!deque.isEmpty() && arr[deque.back()] <= arr[i]) {
                deque.popBack();
            }
            deque.pushBack(i);
        }
        
        // The front of deque contains the largest element of first window
        result.push_back(arr[deque.front()]);
        
        // Process remaining elements
        for (int i = window_size; i < static_cast<int>(arr.size()); ++i) {
            // Remove elements that are out of current window
            while (!deque.isEmpty() && deque.front() <= i - window_size) {
                deque.popFront();
            }
            
            // Remove elements smaller than current element from rear
            while (!deque.isEmpty() && arr[deque.back()] <= arr[i]) {
                deque.popBack();
            }
            
            deque.pushBack(i);
            result.push_back(arr[deque.front()]);
        }
        
        return result;
    }
    
    // Palindrome checker using deque
    template<typename DequeType>
    bool isPalindrome(const std::string& str) {
        DequeType deque;
        
        // Add all characters to deque (ignoring spaces and case)
        for (char c : str) {
            if (std::isalnum(c)) {
                deque.pushBack(std::tolower(c));
            }
        }
        
        // Check palindrome by comparing front and back
        while (deque.size() > 1) {
            if (deque.popFront() != deque.popBack()) {
                return false;
            }
        }
        
        return true;
    }
    
    // Reverse elements in deque
    template<typename T>
    void reverseDeque(ArrayDeque<T>& deque) {
        if (deque.size() <= 1) return;
        
        int left = 0;
        int right = deque.size() - 1;
        
        while (left < right) {
            std::swap(deque[left], deque[right]);
            ++left;
            --right;
        }
    }
    
    template<typename T>
    void reverseDeque(LinkedDeque<T>& deque) {
        if (deque.size() <= 1) return;
        
        std::vector<T> temp;
        while (!deque.isEmpty()) {
            temp.push_back(deque.popBack());
        }
        
        for (const T& item : temp) {
            deque.pushBack(item);
        }
    }
    
    // Rotate deque left by k positions
    template<typename T>
    void rotateLeft(ArrayDeque<T>& deque, int k) {
        if (deque.isEmpty() || k <= 0) return;
        
        k = k % deque.size(); // Handle k > size
        
        for (int i = 0; i < k; ++i) {
            T front = deque.popFront();
            deque.pushBack(front);
        }
    }
    
    // Rotate deque right by k positions
    template<typename T>
    void rotateRight(ArrayDeque<T>& deque, int k) {
        if (deque.isEmpty() || k <= 0) return;
        
        k = k % deque.size(); // Handle k > size
        
        for (int i = 0; i < k; ++i) {
            T back = deque.popBack();
            deque.pushFront(back);
        }
    }
    
    // Performance benchmark
    template<typename DequeType>
    void performanceBenchmark(int operations) {
        std::cout << "\n=== Performance Benchmark (" << operations << " operations) ===" << std::endl;
        
        DequeType deque;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);
        
        // Push operations (mixed front and back)
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < operations; ++i) {
            if (i % 2 == 0) {
                deque.pushBack(dis(gen));
            } else {
                deque.pushFront(dis(gen));
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Push " << operations << " elements (mixed): " << duration.count() << " μs" << std::endl;
        
        // Random access operations (only for ArrayDeque)
        if constexpr (std::is_same_v<DequeType, ArrayDeque<int>>) {
            start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < std::min(operations, static_cast<int>(deque.size())); ++i) {
                volatile int val = deque[i % deque.size()];
                (void)val; // Suppress unused variable warning
            }
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Random access " << std::min(operations, static_cast<int>(deque.size())) << " elements: " << duration.count() << " μs" << std::endl;
        }
        
        // Pop operations (mixed front and back)
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < operations && !deque.isEmpty(); ++i) {
            if (i % 2 == 0) {
                deque.popBack();
            } else {
                deque.popFront();
            }
        }
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Pop " << operations << " elements (mixed): " << duration.count() << " μs" << std::endl;
    }
}

// Test functions
void testArrayDeque() {
    std::cout << "\n========= ARRAY DEQUE TESTS =========" << std::endl;
    
    // Basic operations
    ArrayDeque<int> deque(5);
    std::cout << "\n--- Basic Operations ---" << std::endl;
    
    deque.pushBack(10);
    deque.pushBack(20);
    deque.pushFront(5);
    deque.pushFront(1);
    deque.displayDetails();
    
    std::cout << "Front: " << deque.front() << std::endl;
    std::cout << "Back: " << deque.back() << std::endl;
    std::cout << "Element at index 1: " << deque[1] << std::endl;
    
    std::cout << "Pop front: " << deque.popFront() << std::endl;
    std::cout << "Pop back: " << deque.popBack() << std::endl;
    deque.display();
    
    // Test resize
    std::cout << "\n--- Testing Resize ---" << std::endl;
    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0) {
            deque.pushBack(i * 10);
        } else {
            deque.pushFront(i * 10);
        }
    }
    deque.displayDetails();
    
    // Random access
    std::cout << "\n--- Random Access ---" << std::endl;
    for (int i = 0; i < deque.size(); ++i) {
        std::cout << "deque[" << i << "] = " << deque[i] << std::endl;
    }
    
    // Copy semantics
    std::cout << "\n--- Copy Semantics ---" << std::endl;
    ArrayDeque<int> copied_deque = deque;
    copied_deque.display();
    
    // Move semantics
    std::cout << "\n--- Move Semantics ---" << std::endl;
    ArrayDeque<int> moved_deque = std::move(copied_deque);
    moved_deque.display();
    copied_deque.display(); // Should be empty
    
    // Exception handling
    std::cout << "\n--- Exception Handling ---" << std::endl;
    ArrayDeque<int> empty_deque;
    try {
        empty_deque.popFront();
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    
    try {
        empty_deque[0];
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

void testLinkedDeque() {
    std::cout << "\n========= LINKED DEQUE TESTS =========" << std::endl;
    
    // Basic operations
    LinkedDeque<std::string> deque;
    std::cout << "\n--- Basic Operations ---" << std::endl;
    
    deque.pushBack("World");
    deque.pushBack("!");
    deque.pushFront("Hello");
    deque.pushFront("Hi");
    deque.display();
    deque.displayReverse();
    
    std::cout << "Front: " << deque.front() << std::endl;
    std::cout << "Back: " << deque.back() << std::endl;
    std::cout << "Size: " << deque.size() << std::endl;
    
    // Random access (slower for linked deque)
    std::cout << "\n--- Random Access ---" << std::endl;
    for (int i = 0; i < static_cast<int>(deque.size()); ++i) {
        std::cout << "deque[" << i << "] = " << deque[i] << std::endl;
    }
    
    std::cout << "Pop front: " << deque.popFront() << std::endl;
    std::cout << "Pop back: " << deque.popBack() << std::endl;
    deque.display();
    
    // Copy semantics
    std::cout << "\n--- Copy Semantics ---" << std::endl;
    LinkedDeque<std::string> copied_deque = deque;
    copied_deque.display();
    
    // Move semantics
    std::cout << "\n--- Move Semantics ---" << std::endl;
    LinkedDeque<std::string> moved_deque = std::move(copied_deque);
    moved_deque.display();
    copied_deque.display(); // Should be empty
    
    // Exception handling
    std::cout << "\n--- Exception Handling ---" << std::endl;
    LinkedDeque<std::string> empty_deque;
    try {
        empty_deque.back();
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

void testDequeAlgorithms() {
    std::cout << "\n========= DEQUE ALGORITHMS TESTS =========" << std::endl;
    
    // Test sliding window maximum
    std::cout << "\n--- Sliding Window Maximum ---" << std::endl;
    std::vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int window_size = 3;
    
    std::cout << "Array: ";
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    auto result = DequeUtils::slidingWindowMaximum(arr, window_size);
    std::cout << "Sliding window maximum (window size " << window_size << "): ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Test palindrome checker
    std::cout << "\n--- Palindrome Checker ---" << std::endl;
    std::vector<std::string> test_strings = {
        "racecar", "hello", "A man a plan a canal Panama", "race a car", "madam"
    };
    
    for (const std::string& str : test_strings) {
        bool is_palindrome_array = DequeUtils::isPalindrome<ArrayDeque<char>>(str);
        bool is_palindrome_linked = DequeUtils::isPalindrome<LinkedDeque<char>>(str);
        std::cout << "\"" << str << "\" - ArrayDeque: " << (is_palindrome_array ? "Yes" : "No")
                  << ", LinkedDeque: " << (is_palindrome_linked ? "Yes" : "No") << std::endl;
    }
    
    // Test reverse
    std::cout << "\n--- Deque Reversal ---" << std::endl;
    ArrayDeque<int> reverse_deque;
    for (int i = 1; i <= 5; ++i) {
        reverse_deque.pushBack(i);
    }
    
    std::cout << "Original deque: ";
    reverse_deque.display();
    
    DequeUtils::reverseDeque(reverse_deque);
    std::cout << "Reversed deque: ";
    reverse_deque.display();
    
    // Test rotation
    std::cout << "\n--- Deque Rotation ---" << std::endl;
    ArrayDeque<int> rotate_deque;
    for (int i = 1; i <= 6; ++i) {
        rotate_deque.pushBack(i);
    }
    
    std::cout << "Original deque: ";
    rotate_deque.display();
    
    ArrayDeque<int> left_rotated = rotate_deque;
    DequeUtils::rotateLeft(left_rotated, 2);
    std::cout << "Rotated left by 2: ";
    left_rotated.display();
    
    ArrayDeque<int> right_rotated = rotate_deque;
    DequeUtils::rotateRight(right_rotated, 2);
    std::cout << "Rotated right by 2: ";
    right_rotated.display();
}

void performanceBenchmarks() {
    std::cout << "\n========= PERFORMANCE BENCHMARKS =========" << std::endl;
    
    const int operations = 100000;
    
    std::cout << "\nArray Deque:" << std::endl;
    DequeUtils::performanceBenchmark<ArrayDeque<int>>(operations);
    
    std::cout << "\nLinked Deque:" << std::endl;
    DequeUtils::performanceBenchmark<LinkedDeque<int>>(operations);
}