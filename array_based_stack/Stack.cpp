#include "Stack.h"
#include <iostream>
using namespace std;

Stack::Stack() { topIndex = -1; }

void Stack::push(int value) {
    if (topIndex >= MAX_SIZE - 1) {
        cout << "Stack overflow!" << endl;
        return;
    }
    arr[++topIndex] = value;
}

void Stack::pop() {
    if (topIndex < 0) {
        cout << "Stack is empty!" << endl;
        return;
    }
    topIndex--;
}

int Stack::top() {
    if (topIndex < 0) {
        cout << "Stack is empty!" << endl;
        return -1;
    }
    return arr[topIndex];
}

bool Stack::isEmpty() {
    return topIndex < 0;
}

int Stack::size() {
    return topIndex + 1;
}

void Stack::clear() {
    topIndex = -1;
}
