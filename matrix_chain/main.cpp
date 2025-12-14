#include "MatrixChain.h"
#include <iostream>

int main() {
    std::cout << "=== MATRIX CHAIN MULTIPLICATION (Tabular & Top-Down) ===\n";

    std::vector<int> p1 = {30, 35, 15, 5, 10, 20, 25}; // CLRS example => cost 15125
    printMCM(p1);

    std::cout << "\nAnother example:\n";
    std::vector<int> p2 = {10, 20, 30, 40};
    printMCM(p2);

    std::cout << "\nSingle matrix example:\n";
    std::vector<int> p3 = {10, 100};
    printMCM(p3);

    return 0;
}
