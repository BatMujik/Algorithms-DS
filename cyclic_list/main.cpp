#include "CyclicList.h"
#include <iostream>

int main() {
    std::cout << "=== CYCLIC (CIRCULAR) LINKED LIST DEMO ===\n";

    CyclicList<int> clist;

    std::cout << "PushBack 1,2,3; PushFront 0\n";
    clist.pushBack(1);
    clist.pushBack(2);
    clist.pushBack(3);
    clist.pushFront(0);
    clist.display();
    std::cout << "Front: " << clist.front() << ", Back: " << clist.back() << "\n";

    std::cout << "InsertAt(2, 99)\n";
    clist.insertAt(2, 99);
    clist.display();

    std::cout << "removeAt(3) -> " << clist.removeAt(3) << "\n";
    clist.display();

    std::cout << "find(2) -> " << clist.find(2) << "\n";

    std::cout << "PopFront -> " << clist.popFront() << "; PopBack -> " << clist.popBack() << "\n";
    clist.display();

    std::cout << "Cycle preview (8 steps): ";
    clist.displayCycle(8);

    std::cout << "Clear\n";
    clist.clear();
    clist.display();

    std::cout << "Done.\n";
    return 0;
}
