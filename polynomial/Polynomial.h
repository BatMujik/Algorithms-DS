#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <initializer_list>

// Polynomial represented by coefficients from constant term up (a0, a1, a2, ...)
class Polynomial {
private:
    std::vector<double> coeffs; // coeffs[i] is coefficient for x^i
    void trim();

public:
    Polynomial() = default;
    explicit Polynomial(size_t degree) : coeffs(degree + 1, 0.0) {}
    explicit Polynomial(const std::vector<double>& c) : coeffs(c) { trim(); }
    explicit Polynomial(std::vector<double>&& c) : coeffs(std::move(c)) { trim(); }
    Polynomial(std::initializer_list<double> c) : coeffs(c) { trim(); }

    int degree() const; // -1 if zero polynomial
    double get(int i) const; // coefficient of x^i (0 if out of range)
    void set(int i, double value); // expands if needed

    double evaluate(double x) const; // Horner's method

    Polynomial derivative() const;
    Polynomial integral(double constant = 0.0) const;

    Polynomial& operator+=(const Polynomial& rhs);
    Polynomial& operator-=(const Polynomial& rhs);
    Polynomial& operator*=(const Polynomial& rhs);

    friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs) { lhs += rhs; return lhs; }
    friend Polynomial operator-(Polynomial lhs, const Polynomial& rhs) { lhs -= rhs; return lhs; }
    friend Polynomial operator*(Polynomial lhs, const Polynomial& rhs) { lhs *= rhs; return lhs; }

    std::string toString() const; // human-readable form

    const std::vector<double>& coefficients() const { return coeffs; }
};
