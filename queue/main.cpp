#include "Queue.h"
#include <iostream>
#include <string>

// Function declarations
void testArrayQueue();
void testLinkedQueue();
void testPriorityQueue();
void testQueueAlgorithms();
void performanceBenchmarks();
void interactiveMode();

int main() {
    std::cout << "=== QUEUE DATA STRUCTURE IMPLEMENTATION ===" << std::endl;
    std::cout << "Features:" << std::endl;
    std::cout << "- Array-based circular queue with dynamic resizing" << std::endl;
    std::cout << "- Linked list-based queue" << std::endl;
    std::cout << "- Priority queue (max-heap)" << std::endl;
    std::cout << "- Copy/Move semantics (Rule of 5)" << std::endl;
    std::cout << "- Queue algorithms and utilities" << std::endl;
    std::cout << "- Performance benchmarking" << std::endl;
    
    while (true) {
        std::cout << "\n========= QUEUE MENU =========" << std::endl;
        std::cout << "1. Test Array Queue" << std::endl;
        std::cout << "2. Test Linked Queue" << std::endl;
        std::cout << "3. Test Priority Queue" << std::endl;
        std::cout << "4. Test Queue Algorithms" << std::endl;
        std::cout << "5. Performance Benchmarks" << std::endl;
        std::cout << "6. Interactive Mode" << std::endl;
        std::cout << "7. Run All Tests" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option: ";
        
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }
        
        std::cin.ignore(); // Clear the newline
        
        try {
            switch (choice) {
                case 1:
                    testArrayQueue();
                    break;
                case 2:
                    testLinkedQueue();
                    break;
                case 3:
                    testPriorityQueue();
                    break;
                case 4:
                    testQueueAlgorithms();
                    break;
                case 5:
                    performanceBenchmarks();
                    break;
                case 6:
                    interactiveMode();
                    break;
                case 7:
                    testArrayQueue();
                    testLinkedQueue();
                    testPriorityQueue();
                    testQueueAlgorithms();
                    performanceBenchmarks();
                    break;
                case 0:
                    std::cout << "Goodbye!" << std::endl;
                    return 0;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
    
    return 0;
}

void interactiveMode() {
    std::cout << "\n========= INTERACTIVE QUEUE MODE =========" << std::endl;
    std::cout << "Choose queue type:" << std::endl;
    std::cout << "1. Array Queue" << std::endl;
    std::cout << "2. Linked Queue" << std::endl;
    std::cout << "3. Priority Queue" << std::endl;
    std::cout << "Choice: ";
    
    int queueType;
    std::cin >> queueType;
    std::cin.ignore();
    
    if (queueType == 1) {
        ArrayQueue<int> queue;
        
        while (true) {
            std::cout << "\n--- Array Queue Operations ---" << std::endl;
            std::cout << "1. Enqueue" << std::endl;
            std::cout << "2. Dequeue" << std::endl;
            std::cout << "3. Front" << std::endl;
            std::cout << "4. Back" << std::endl;
            std::cout << "5. Display" << std::endl;
            std::cout << "6. Display Details" << std::endl;
            std::cout << "7. Size" << std::endl;
            std::cout << "8. Is Empty" << std::endl;
            std::cout << "0. Back to main menu" << std::endl;
            std::cout << "Choice: ";
            
            int operation;
            std::cin >> operation;
            std::cin.ignore();
            
            try {
                switch (operation) {
                    case 1: {
                        std::cout << "Enter value to enqueue: ";
                        int value;
                        std::cin >> value;
                        std::cin.ignore();
                        queue.enqueue(value);
                        std::cout << "Enqueued " << value << std::endl;
                        break;
                    }
                    case 2: {
                        int value = queue.dequeue();
                        std::cout << "Dequeued: " << value << std::endl;
                        break;
                    }
                    case 3:
                        std::cout << "Front: " << queue.front() << std::endl;
                        break;
                    case 4:
                        std::cout << "Back: " << queue.back() << std::endl;
                        break;
                    case 5:
                        queue.display();
                        break;
                    case 6:
                        queue.displayDetails();
                        break;
                    case 7:
                        std::cout << "Size: " << queue.size() << std::endl;
                        break;
                    case 8:
                        std::cout << "Is empty: " << (queue.isEmpty() ? "Yes" : "No") << std::endl;
                        break;
                    case 0:
                        return;
                    default:
                        std::cout << "Invalid choice." << std::endl;
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        
    } else if (queueType == 2) {
        LinkedQueue<int> queue;
        
        while (true) {
            std::cout << "\n--- Linked Queue Operations ---" << std::endl;
            std::cout << "1. Enqueue" << std::endl;
            std::cout << "2. Dequeue" << std::endl;
            std::cout << "3. Front" << std::endl;
            std::cout << "4. Back" << std::endl;
            std::cout << "5. Display" << std::endl;
            std::cout << "6. Size" << std::endl;
            std::cout << "7. Is Empty" << std::endl;
            std::cout << "0. Back to main menu" << std::endl;
            std::cout << "Choice: ";
            
            int operation;
            std::cin >> operation;
            std::cin.ignore();
            
            try {
                switch (operation) {
                    case 1: {
                        std::cout << "Enter value to enqueue: ";
                        int value;
                        std::cin >> value;
                        std::cin.ignore();
                        queue.enqueue(value);
                        std::cout << "Enqueued " << value << std::endl;
                        break;
                    }
                    case 2: {
                        int value = queue.dequeue();
                        std::cout << "Dequeued: " << value << std::endl;
                        break;
                    }
                    case 3:
                        std::cout << "Front: " << queue.front() << std::endl;
                        break;
                    case 4:
                        std::cout << "Back: " << queue.back() << std::endl;
                        break;
                    case 5:
                        queue.display();
                        break;
                    case 6:
                        std::cout << "Size: " << queue.size() << std::endl;
                        break;
                    case 7:
                        std::cout << "Is empty: " << (queue.isEmpty() ? "Yes" : "No") << std::endl;
                        break;
                    case 0:
                        return;
                    default:
                        std::cout << "Invalid choice." << std::endl;
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        
    } else if (queueType == 3) {
        PriorityQueue<int> queue;
        
        while (true) {
            std::cout << "\n--- Priority Queue Operations ---" << std::endl;
            std::cout << "1. Enqueue" << std::endl;
            std::cout << "2. Dequeue (highest priority)" << std::endl;
            std::cout << "3. Top (highest priority)" << std::endl;
            std::cout << "4. Display" << std::endl;
            std::cout << "5. Size" << std::endl;
            std::cout << "6. Is Empty" << std::endl;
            std::cout << "0. Back to main menu" << std::endl;
            std::cout << "Choice: ";
            
            int operation;
            std::cin >> operation;
            std::cin.ignore();
            
            try {
                switch (operation) {
                    case 1: {
                        std::cout << "Enter value to enqueue: ";
                        int value;
                        std::cin >> value;
                        std::cin.ignore();
                        queue.enqueue(value);
                        std::cout << "Enqueued " << value << std::endl;
                        break;
                    }
                    case 2: {
                        int value = queue.dequeue();
                        std::cout << "Dequeued (highest priority): " << value << std::endl;
                        break;
                    }
                    case 3:
                        std::cout << "Top (highest priority): " << queue.top() << std::endl;
                        break;
                    case 4:
                        queue.display();
                        break;
                    case 5:
                        std::cout << "Size: " << queue.size() << std::endl;
                        break;
                    case 6:
                        std::cout << "Is empty: " << (queue.isEmpty() ? "Yes" : "No") << std::endl;
                        break;
                    case 0:
                        return;
                    default:
                        std::cout << "Invalid choice." << std::endl;
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        
    } else {
        std::cout << "Invalid queue type choice." << std::endl;
    }
}