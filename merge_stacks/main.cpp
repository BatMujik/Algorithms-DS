#include "MergeStacks.h"
#include <iostream>

void printStack(Stack s) {
    std::cout << "Top -> ";
    while (!s.isEmpty()) {
        std::cout << s.top() << ' ';
        s.pop();
    }
    std::cout << "<- Bottom\n";
}

int main() {
    std::cout << "=== MERGE STACKS DEMO ===\n";
    Stack a, b;
    // a bottom->top: 1,2,3
    a.push(1); a.push(2); a.push(3);
    // b bottom->top: 10,20
    b.push(10); b.push(20);

    std::cout << "Stack A: "; printStack(a);
    std::cout << "Stack B: "; printStack(b);

    auto merged = mergePreserveOrder(a, b);
    std::cout << "Merged (preserve order A then B): "; printStack(merged);

    auto inter = mergeInterleave(a, b);
    std::cout << "Merged (interleave from bottoms): "; printStack(inter);

    return 0;
}
