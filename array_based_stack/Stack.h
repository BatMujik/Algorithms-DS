#pragma once

class Stack {
private:
    static const int MAX_SIZE = 500;
    int arr[MAX_SIZE];
    int topIndex;
public:
    Stack();
    void push(int value);
    void pop();
    int top();
    bool isEmpty();
    int size();
    void clear();
};
