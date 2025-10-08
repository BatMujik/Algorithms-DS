#include <iostream>
#include "Stack.h"
using namespace std;

int main() {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Top element: " << s.top() << endl;
    s.pop();
    cout << "Top element after pop: " << s.top() << endl;

    cout << "Stack size: " << s.size() << endl;
    cout << "Is stack empty? " << (s.isEmpty() ? "Yes" : "No") << endl;

    s.clear();
    cout << "Stack cleared. Is stack empty? " << (s.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}
