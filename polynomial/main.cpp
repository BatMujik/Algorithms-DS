#include "Polynomial.h"
#include <iostream>

int main() {
    std::cout << "=== POLYNOMIAL DEMO ===\n";

    Polynomial p1({1, -3, 2}); // 2x^2 - 3x + 1
    Polynomial p2({0, 4});     // 4x

    std::cout << "p1(x) = " << p1.toString() << "\n";
    std::cout << "p2(x) = " << p2.toString() << "\n";

    auto sum = p1 + p2;
    auto diff = p1 - p2;
    auto prod = p1 * p2;

    std::cout << "p1 + p2 = " << sum.toString() << "\n";
    std::cout << "p1 - p2 = " << diff.toString() << "\n";
    std::cout << "p1 * p2 = " << prod.toString() << "\n";

    double x = 2.0;
    std::cout << "p1(" << x << ") = " << p1.evaluate(x) << "\n";

    auto dp1 = p1.derivative();
    std::cout << "p1'(x) = " << dp1.toString() << "\n";

    auto ip1 = p1.integral(5.0);
    std::cout << "Integral(p1) + C, C=5: " << ip1.toString() << "\n";

    return 0;
}
