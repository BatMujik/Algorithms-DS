#include "LCS.h"
#include <iostream>

int main() {
    std::cout << "=== LONGEST COMMON SUBSEQUENCE DEMO ===\n";
    std::string a = "AGGTAB";
    std::string b = "GXTXAYB";
    printLCS(a, b);

    std::cout << "\nTop-down length only: " << lcsTopDownLength(a, b) << "\n";

    std::cout << "\nAnother example:\n";
    a = "ABCBDAB"; b = "BDCABA";
    printLCS(a, b);

    return 0;
}
