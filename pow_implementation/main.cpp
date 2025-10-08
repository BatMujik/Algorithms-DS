#include <iostream>
using namespace std;

double pow(double x, int n) {
    double result = 1.0;
    long long exp = n;
    if (exp < 0) {
        x = 1 / x;
        exp = -exp;
    }
    while (exp) {
        if (exp % 2) result *= x;
        x *= x;
        exp /= 2;
    }
    return result;
}

int main() {
    cout << "pow(2, 10) = " << pow(2, 10) << endl; // 1024
    cout << "pow(2, -3) = " << pow(2, -3) << endl; // 0.125
    cout << "pow(5, 0) = " << pow(5, 0) << endl;   // 1
    return 0;
}
