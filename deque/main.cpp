#include "Deque.h"
#include <iostream>
#include <string>

// Function declarations
void testArrayDeque();
void testLinkedDeque();
void testDequeAlgorithms();
void performanceBenchmarks();
void interactiveMode();
void demonstrateDeque();

int main() {
    std::cout << "=== DEQUE (DOUBLE-ENDED QUEUE) DATA STRUCTURE IMPLEMENTATION ===" << std::endl;
    std::cout << "Features:" << std::endl;
    std::cout << "- Array-based circular deque with dynamic resizing" << std::endl;
    std::cout << "- Doubly linked list-based deque" << std::endl;
    std::cout << "- Insertion/deletion at both ends in O(1) time" << std::endl;
    std::cout << "- Random access support (O(1) for array, O(n) for linked)" << std::endl;
    std::cout << "- Copy/Move semantics (Rule of 5)" << std::endl;
    std::cout << "- Deque algorithms: sliding window maximum, palindrome check" << std::endl;
    std::cout << "- Rotation and reversal operations" << std::endl;
    
    while (true) {
        std::cout << "\n========= DEQUE MENU =========" << std::endl;
        std::cout << "1. Test Array Deque" << std::endl;
        std::cout << "2. Test Linked Deque" << std::endl;
        std::cout << "3. Test Deque Algorithms" << std::endl;
        std::cout << "4. Performance Benchmarks" << std::endl;
        std::cout << "5. Interactive Mode" << std::endl;
        std::cout << "6. Deque Demonstration" << std::endl;
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
                    testArrayDeque();
                    break;
                case 2:
                    testLinkedDeque();
                    break;
                case 3:
                    testDequeAlgorithms();
                    break;
                case 4:
                    performanceBenchmarks();
                    break;
                case 5:
                    interactiveMode();
                    break;
                case 6:
                    demonstrateDeque();
                    break;
                case 7:
                    testArrayDeque();
                    testLinkedDeque();
                    testDequeAlgorithms();
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

void demonstrateDeque() {
    std::cout << "\n========= DEQUE DEMONSTRATION =========" << std::endl;
    std::cout << "This demonstrates the key features of deque data structure." << std::endl;
    
    ArrayDeque<int> deque;
    
    std::cout << "\n--- Step 1: Pushing elements to both ends ---" << std::endl;
    std::cout << "pushBack(10), pushBack(20), pushFront(5), pushFront(1)" << std::endl;
    deque.pushBack(10);
    deque.pushBack(20);
    deque.pushFront(5);
    deque.pushFront(1);
    deque.display();
    
    std::cout << "\n--- Step 2: Accessing elements ---" << std::endl;
    std::cout << "front() = " << deque.front() << std::endl;
    std::cout << "back() = " << deque.back() << std::endl;
    std::cout << "deque[1] = " << deque[1] << " (random access)" << std::endl;
    
    std::cout << "\n--- Step 3: Popping from both ends ---" << std::endl;
    std::cout << "popFront() = " << deque.popFront() << std::endl;
    std::cout << "popBack() = " << deque.popBack() << std::endl;
    deque.display();
    
    std::cout << "\n--- Step 4: Adding more elements to trigger resize ---" << std::endl;
    for (int i = 1; i <= 8; ++i) {
        if (i % 2 == 0) {
            deque.pushBack(i * 10);
            std::cout << "pushBack(" << (i * 10) << ") ";
        } else {
            deque.pushFront(i * 10);
            std::cout << "pushFront(" << (i * 10) << ") ";
        }
    }
    std::cout << std::endl;
    deque.displayDetails();
    
    std::cout << "\n--- Step 5: Demonstrating bidirectional iteration ---" << std::endl;
    std::cout << "Forward: ";
    for (int i = 0; i < deque.size(); ++i) {
        std::cout << deque[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Backward: ";
    for (int i = deque.size() - 1; i >= 0; --i) {
        std::cout << deque[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\nDeque characteristics:" << std::endl;
    std::cout << "- O(1) insertion/deletion at both ends" << std::endl;
    std::cout << "- O(1) random access (array-based)" << std::endl;
    std::cout << "- Dynamic resizing when needed" << std::endl;
    std::cout << "- Useful for algorithms requiring double-ended access" << std::endl;
}

void interactiveMode() {
    std::cout << "\n========= INTERACTIVE DEQUE MODE =========" << std::endl;
    std::cout << "Choose deque type:" << std::endl;
    std::cout << "1. Array Deque" << std::endl;
    std::cout << "2. Linked Deque" << std::endl;
    std::cout << "Choice: ";
    
    int dequeType;
    std::cin >> dequeType;
    std::cin.ignore();
    
    if (dequeType == 1) {
        ArrayDeque<int> deque;
        
        while (true) {
            std::cout << "\n--- Array Deque Operations ---" << std::endl;
            std::cout << "1. Push Front" << std::endl;
            std::cout << "2. Push Back" << std::endl;
            std::cout << "3. Pop Front" << std::endl;
            std::cout << "4. Pop Back" << std::endl;
            std::cout << "5. Front" << std::endl;
            std::cout << "6. Back" << std::endl;
            std::cout << "7. Random Access" << std::endl;
            std::cout << "8. Display" << std::endl;
            std::cout << "9. Display Details" << std::endl;
            std::cout << "10. Display Reverse" << std::endl;
            std::cout << "11. Size" << std::endl;
            std::cout << "12. Is Empty" << std::endl;
            std::cout << "13. Clear" << std::endl;
            std::cout << "0. Back to main menu" << std::endl;
            std::cout << "Choice: ";
            
            int operation;
            std::cin >> operation;
            std::cin.ignore();
            
            try {
                switch (operation) {
                    case 1: {
                        std::cout << "Enter value to push front: ";
                        int value;
                        std::cin >> value;
                        std::cin.ignore();
                        deque.pushFront(value);
                        std::cout << "Pushed " << value << " to front" << std::endl;
                        break;
                    }
                    case 2: {
                        std::cout << "Enter value to push back: ";
                        int value;
                        std::cin >> value;
                        std::cin.ignore();
                        deque.pushBack(value);
                        std::cout << "Pushed " << value << " to back" << std::endl;
                        break;
                    }
                    case 3: {
                        int value = deque.popFront();
                        std::cout << "Popped from front: " << value << std::endl;
                        break;
                    }
                    case 4: {
                        int value = deque.popBack();
                        std::cout << "Popped from back: " << value << std::endl;
                        break;
                    }
                    case 5:
                        std::cout << "Front: " << deque.front() << std::endl;
                        break;
                    case 6:
                        std::cout << "Back: " << deque.back() << std::endl;
                        break;
                    case 7: {
                        std::cout << "Enter index: ";
                        int index;
                        std::cin >> index;
                        std::cin.ignore();
                        std::cout << "deque[" << index << "] = " << deque[index] << std::endl;
                        break;
                    }
                    case 8:
                        deque.display();
                        break;
                    case 9:
                        deque.displayDetails();
                        break;
                    case 10:
                        deque.displayReverse();
                        break;
                    case 11:
                        std::cout << "Size: " << deque.size() << std::endl;
                        break;
                    case 12:
                        std::cout << "Is empty: " << (deque.isEmpty() ? "Yes" : "No") << std::endl;
                        break;
                    case 13:
                        deque.clear();
                        std::cout << "Deque cleared." << std::endl;
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
        
    } else if (dequeType == 2) {
        LinkedDeque<int> deque;
        
        while (true) {
            std::cout << "\n--- Linked Deque Operations ---" << std::endl;
            std::cout << "1. Push Front" << std::endl;
            std::cout << "2. Push Back" << std::endl;
            std::cout << "3. Pop Front" << std::endl;
            std::cout << "4. Pop Back" << std::endl;
            std::cout << "5. Front" << std::endl;
            std::cout << "6. Back" << std::endl;
            std::cout << "7. Random Access" << std::endl;
            std::cout << "8. Display" << std::endl;
            std::cout << "9. Display Reverse" << std::endl;
            std::cout << "10. Size" << std::endl;
            std::cout << "11. Is Empty" << std::endl;
            std::cout << "12. Clear" << std::endl;
            std::cout << "0. Back to main menu" << std::endl;
            std::cout << "Choice: ";
            
            int operation;
            std::cin >> operation;
            std::cin.ignore();
            
            try {
                switch (operation) {
                    case 1: {
                        std::cout << "Enter value to push front: ";
                        int value;
                        std::cin >> value;
                        std::cin.ignore();
                        deque.pushFront(value);
                        std::cout << "Pushed " << value << " to front" << std::endl;
                        break;
                    }
                    case 2: {
                        std::cout << "Enter value to push back: ";
                        int value;
                        std::cin >> value;
                        std::cin.ignore();
                        deque.pushBack(value);
                        std::cout << "Pushed " << value << " to back" << std::endl;
                        break;
                    }
                    case 3: {
                        int value = deque.popFront();
                        std::cout << "Popped from front: " << value << std::endl;
                        break;
                    }
                    case 4: {
                        int value = deque.popBack();
                        std::cout << "Popped from back: " << value << std::endl;
                        break;
                    }
                    case 5:
                        std::cout << "Front: " << deque.front() << std::endl;
                        break;
                    case 6:
                        std::cout << "Back: " << deque.back() << std::endl;
                        break;
                    case 7: {
                        std::cout << "Enter index: ";
                        int index;
                        std::cin >> index;
                        std::cin.ignore();
                        std::cout << "deque[" << index << "] = " << deque[index] << std::endl;
                        break;
                    }
                    case 8:
                        deque.display();
                        break;
                    case 9:
                        deque.displayReverse();
                        break;
                    case 10:
                        std::cout << "Size: " << deque.size() << std::endl;
                        break;
                    case 11:
                        std::cout << "Is empty: " << (deque.isEmpty() ? "Yes" : "No") << std::endl;
                        break;
                    case 12:
                        deque.clear();
                        std::cout << "Deque cleared." << std::endl;
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
        std::cout << "Invalid deque type choice." << std::endl;
    }
}