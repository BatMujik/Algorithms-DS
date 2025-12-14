#include "Hanoi.h"
#include <iostream>

int main() {
    std::cout << "=== TOWER OF HANOI ===\n";
    int n;
    std::cout << "Enter number of disks (1..12 recommended): ";
    if (!(std::cin >> n)) { std::cout << "Invalid input\n"; return 0; }
    if (n < 0) { std::cout << "n must be non-negative\n"; return 0; }

    std::cout << "\n-- Recursive solution --\n";
    auto rec = solveHanoiRecursive(n);
    printMoves(rec);

    std::cout << "\n-- Iterative solution --\n";
    auto it = solveHanoiIterative(n);
    printMoves(it);

    return 0;
}
