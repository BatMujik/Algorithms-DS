#pragma once
#include <stdexcept>
#include <iostream>

// Singly Circular Linked List (Cyclic List)
// Maintains `tail` pointer; when non-empty, `tail->next` points to head.
// All operations are O(1) or O(n) where noted.

template<typename T>
class CyclicList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& v) : data(v), next(nullptr) {}
        Node(T&& v) : data(std::move(v)), next(nullptr) {}
    };

    Node* tail; // tail->next is head when not empty
    size_t count;

    Node* head() const { return tail ? tail->next : nullptr; }

public:
    CyclicList() : tail(nullptr), count(0) {}
    CyclicList(const CyclicList& other) : tail(nullptr), count(0) {
        if (other.isEmpty()) return;
        Node* cur = other.tail->next; // start at head
        size_t n = other.count;
        for (size_t i = 0; i < n; ++i) {
            pushBack(cur->data);
            cur = cur->next;
        }
    }
    CyclicList(CyclicList&& other) noexcept : tail(other.tail), count(other.count) {
        other.tail = nullptr;
        other.count = 0;
    }
    CyclicList& operator=(const CyclicList& other) {
        if (this == &other) return *this;
        clear();
        if (other.isEmpty()) return *this;
        Node* cur = other.tail->next;
        size_t n = other.count;
        for (size_t i = 0; i < n; ++i) {
            pushBack(cur->data);
            cur = cur->next;
        }
        return *this;
    }
    CyclicList& operator=(CyclicList&& other) noexcept {
        if (this == &other) return *this;
        clear();
        tail = other.tail;
        count = other.count;
        other.tail = nullptr;
        other.count = 0;
        return *this;
    }
    ~CyclicList() { clear(); }

    bool isEmpty() const { return count == 0; }
    size_t size() const { return count; }

    // Front is head (tail->next when not empty)
    const T& front() const {
        if (isEmpty()) throw std::runtime_error("List is empty");
        return tail->next->data;
    }
    T& front() {
        if (isEmpty()) throw std::runtime_error("List is empty");
        return tail->next->data;
    }
    const T& back() const {
        if (isEmpty()) throw std::runtime_error("List is empty");
        return tail->data;
    }
    T& back() {
        if (isEmpty()) throw std::runtime_error("List is empty");
        return tail->data;
    }

    void pushFront(const T& value) {
        Node* n = new Node(value);
        if (!tail) {
            tail = n;
            tail->next = tail;
        } else {
            n->next = tail->next; // old head
            tail->next = n;       // new head
        }
        ++count;
    }
    void pushFront(T&& value) {
        Node* n = new Node(std::move(value));
        if (!tail) {
            tail = n;
            tail->next = tail;
        } else {
            n->next = tail->next;
            tail->next = n;
        }
        ++count;
    }

    void pushBack(const T& value) {
        Node* n = new Node(value);
        if (!tail) {
            tail = n;
            tail->next = tail;
        } else {
            n->next = tail->next; // head
            tail->next = n;
            tail = n;
        }
        ++count;
    }
    void pushBack(T&& value) {
        Node* n = new Node(std::move(value));
        if (!tail) {
            tail = n;
            tail->next = tail;
        } else {
            n->next = tail->next;
            tail->next = n;
            tail = n;
        }
        ++count;
    }

    T popFront() {
        if (isEmpty()) throw std::runtime_error("Cannot pop from empty list");
        Node* h = tail->next;
        T val = std::move(h->data);
        if (h == tail) { // single node
            delete h;
            tail = nullptr;
        } else {
            tail->next = h->next;
            delete h;
        }
        --count;
        return val;
    }

    T popBack() {
        if (isEmpty()) throw std::runtime_error("Cannot pop from empty list");
        Node* h = tail->next;
        if (h == tail) {
            T val = std::move(tail->data);
            delete tail;
            tail = nullptr;
            --count;
            return val;
        }
        // find node before tail
        Node* prev = h;
        while (prev->next != tail) prev = prev->next;
        T val = std::move(tail->data);
        prev->next = tail->next; // new tail next points to head
        delete tail;
        tail = prev;
        --count;
        return val;
    }

    // Insert at position [0..count]. 0 -> front, count -> back.
    void insertAt(size_t index, const T& value) {
        if (index > count) throw std::out_of_range("Index out of range");
        if (index == 0) { pushFront(value); return; }
        if (index == count) { pushBack(value); return; }
        Node* cur = tail->next; // head
        for (size_t i = 0; i < index - 1; ++i) cur = cur->next;
        Node* n = new Node(value);
        n->next = cur->next;
        cur->next = n;
        ++count;
    }
    void insertAt(size_t index, T&& value) {
        if (index > count) throw std::out_of_range("Index out of range");
        if (index == 0) { pushFront(std::move(value)); return; }
        if (index == count) { pushBack(std::move(value)); return; }
        Node* cur = tail->next;
        for (size_t i = 0; i < index - 1; ++i) cur = cur->next;
        Node* n = new Node(std::move(value));
        n->next = cur->next;
        cur->next = n;
        ++count;
    }

    // Remove at position [0..count-1]
    T removeAt(size_t index) {
        if (index >= count) throw std::out_of_range("Index out of range");
        if (index == 0) return popFront();
        // find node before index
        Node* cur = tail->next;
        for (size_t i = 0; i < index - 1; ++i) cur = cur->next;
        Node* victim = cur->next;
        T val = std::move(victim->data);
        cur->next = victim->next;
        if (victim == tail) {
            tail = cur; // removed last; fix tail
        }
        delete victim;
        --count;
        return val;
    }

    // Find first index of value, -1 if not found (O(n))
    long long find(const T& value) const {
        if (isEmpty()) return -1;
        Node* cur = tail->next; // head
        for (size_t i = 0; i < count; ++i) {
            if (cur->data == value) return static_cast<long long>(i);
            cur = cur->next;
        }
        return -1;
    }

    void clear() {
        if (!tail) return;
        Node* h = tail->next;
        tail->next = nullptr; // break cycle to ease deletion
        while (h) {
            Node* nxt = h->next;
            delete h;
            h = nxt;
        }
        tail = nullptr;
        count = 0;
    }

    void display() const {
        std::cout << "CyclicList: ";
        if (isEmpty()) { std::cout << "EMPTY\n"; return; }
        Node* cur = tail->next; // head
        for (size_t i = 0; i < count; ++i) {
            std::cout << cur->data << ' ';
            cur = cur->next;
        }
        std::cout << "\n";
    }

    // For debugging: show first k elements going around the cycle
    void displayCycle(size_t k) const {
        if (isEmpty()) { std::cout << "EMPTY\n"; return; }
        Node* cur = tail->next;
        for (size_t i = 0; i < k; ++i) {
            std::cout << cur->data << ' ';
            cur = cur->next;
        }
        std::cout << "\n";
    }
};
