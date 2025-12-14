#include "Polynomial.h"
#include <sstream>
#include <cmath>

void Polynomial::trim() {
    while (!coeffs.empty() && std::abs(coeffs.back()) < 1e-12) coeffs.pop_back();
}

int Polynomial::degree() const {
    return coeffs.empty() ? -1 : static_cast<int>(coeffs.size()) - 1;
}

double Polynomial::get(int i) const {
    if (i < 0 || i >= static_cast<int>(coeffs.size())) return 0.0;
    return coeffs[i];
}

void Polynomial::set(int i, double value) {
    if (i < 0) throw std::out_of_range("negative index");
    if (i >= static_cast<int>(coeffs.size())) coeffs.resize(i + 1, 0.0);
    coeffs[i] = value;
    trim();
}

double Polynomial::evaluate(double x) const {
    double result = 0.0;
    for (int i = degree(); i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}

Polynomial Polynomial::derivative() const {
    if (degree() <= 0) return Polynomial();
    std::vector<double> d(static_cast<size_t>(degree()));
    for (int i = 1; i <= degree(); ++i) d[static_cast<size_t>(i - 1)] = coeffs[i] * i;
    return Polynomial(std::move(d));
}

Polynomial Polynomial::integral(double constant) const {
    std::vector<double> in(static_cast<size_t>(degree() + 2), 0.0);
    in[0] = constant;
    for (int i = 0; i <= degree(); ++i) in[static_cast<size_t>(i + 1)] = coeffs[i] / (i + 1);
    return Polynomial(std::move(in));
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    size_t n = std::max(coeffs.size(), rhs.coefficients().size());
    coeffs.resize(n, 0.0);
    for (size_t i = 0; i < rhs.coefficients().size(); ++i) coeffs[i] += rhs.coefficients()[i];
    trim();
    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& rhs) {
    size_t n = std::max(coeffs.size(), rhs.coefficients().size());
    coeffs.resize(n, 0.0);
    for (size_t i = 0; i < rhs.coefficients().size(); ++i) coeffs[i] -= rhs.coefficients()[i];
    trim();
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& rhs) {
    if (degree() == -1 || rhs.degree() == -1) { coeffs.clear(); return *this; }
    std::vector<double> prod(static_cast<size_t>(degree() + rhs.degree() + 1), 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        for (size_t j = 0; j < rhs.coefficients().size(); ++j) {
            prod[i + j] += coeffs[i] * rhs.coefficients()[j];
        }
    }
    coeffs = std::move(prod);
    trim();
    return *this;
}

std::string Polynomial::toString() const {
    if (degree() == -1) return "0";
    std::ostringstream oss;
    bool first = true;
    for (int i = degree(); i >= 0; --i) {
        double c = coeffs[i];
        if (std::abs(c) < 1e-12) continue;
        if (!first) oss << (c >= 0 ? " + " : " - ");
        else if (c < 0) oss << "-";
        double absC = std::abs(c);
        if (i == 0) {
            oss << absC;
        } else if (i == 1) {
            if (absC != 1.0) oss << absC << "*x"; else oss << "x";
        } else {
            if (absC != 1.0) oss << absC << "*x^" << i; else oss << "x^" << i;
        }
        first = false;
    }
    if (first) return "0"; // all zeros
    return oss.str();
}
