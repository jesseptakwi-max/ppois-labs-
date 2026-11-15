
#include "Polynomial.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

namespace {
constexpr double EPSILON = 1e-12;
constexpr std::size_t MAX_DEGREE = 10000;
}

Polynomial::Polynomial() : coeffs_{0.0} {}

Polynomial::Polynomial(const std::vector<double>& coeffs)
    : coeffs_(coeffs) {
    trim();
}

Polynomial::Polynomial(std::initializer_list<double> coeffs)
    : coeffs_(coeffs) {
    trim();
}

Polynomial::Polynomial(const Polynomial& other)
    : coeffs_(other.coeffs_) {}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coeffs_ = other.coeffs_;
    }
    return *this;
}

bool Polynomial::operator==(const Polynomial& other) const {
    if (degree() != other.degree()) {
        return false;
    }

    for (std::size_t i = 0; i <= degree(); ++i) {
        if (std::abs((*this)[i] - other[i]) >= EPSILON) {
            return false;
        }
    }

    return true;
}

bool Polynomial::operator!=(const Polynomial& other) const {
    return !(*this == other);
}

double Polynomial::operator[](std::size_t degree) const {
    if (degree >= coeffs_.size()) {
        return 0.0;
    }
    return coeffs_[degree];
}

double& Polynomial::operator[](std::size_t degree) {
    if (degree > MAX_DEGREE) {
        throw std::out_of_range("Polynomial degree is too large");
    }

    if (degree >= coeffs_.size()) {
        coeffs_.resize(degree + 1, 0.0);
    }

    return coeffs_[degree];
}

double Polynomial::operator()(double x) const {
    double result = 0.0;

    for (std::size_t i = coeffs_.size(); i > 0; --i) {
        result = result * x + coeffs_[i - 1];
    }

    return result;
}

Polynomial Polynomial::operator+(const Polynomial& rhs) const {
    const std::size_t size =
        std::max(coeffs_.size(), rhs.coeffs_.size());

    std::vector<double> result(size, 0.0);

    for (std::size_t i = 0; i < size; ++i) {
        result[i] = (*this)[i] + rhs[i];
    }

    return Polynomial(result);
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    *this = *this + rhs;
    return *this;
}

Polynomial Polynomial::operator-(const Polynomial& rhs) const {
    const std::size_t size =
        std::max(coeffs_.size(), rhs.coeffs_.size());

    std::vector<double> result(size, 0.0);

    for (std::size_t i = 0; i < size; ++i) {
        result[i] = (*this)[i] - rhs[i];
    }

    return Polynomial(result);
}

Polynomial& Polynomial::operator-=(const Polynomial& rhs) {
    *this = *this - rhs;
    return *this;
}

Polynomial Polynomial::operator*(const Polynomial& rhs) const {
    std::vector<double> result(
        coeffs_.size() + rhs.coeffs_.size() - 1, 0.0);

    for (std::size_t i = 0; i < coeffs_.size(); ++i) {
        for (std::size_t j = 0; j < rhs.coeffs_.size(); ++j) {
            result[i + j] += coeffs_[i] * rhs.coeffs_[j];
        }
    }

    return Polynomial(result);
}

Polynomial& Polynomial::operator*=(const Polynomial& rhs) {
    *this = *this * rhs;
    return *this;
}

Polynomial Polynomial::operator/(const Polynomial& rhs) const {
    if (rhs.degree() == 0 && std::abs(rhs[0]) < EPSILON) {
        throw std::runtime_error("Division by zero polynomial");
    }

    Polynomial dividend(*this);
    const Polynomial divisor(rhs);

    if (dividend.degree() < divisor.degree()) {
        return Polynomial();
    }

    std::vector<double> quotient(
        dividend.degree() - divisor.degree() + 1, 0.0);

    while (dividend.degree() >= divisor.degree()) {
        if (dividend.degree() == 0 &&
            std::abs(dividend[0]) < EPSILON) {
            break;
        }

        const std::size_t difference =
            dividend.degree() - divisor.degree();

        const double factor =
            dividend[dividend.degree()] /
            divisor[divisor.degree()];

        quotient[difference] = factor;

        for (std::size_t i = 0; i <= divisor.degree(); ++i) {
            dividend[difference + i] -= factor * divisor[i];
        }

        dividend.trim();
    }

    return Polynomial(quotient);
}

Polynomial& Polynomial::operator/=(const Polynomial& rhs) {
    *this = *this / rhs;
    return *this;
}

std::size_t Polynomial::degree() const {
    for (std::size_t i = coeffs_.size(); i > 1; --i) {
        if (std::abs(coeffs_[i - 1]) >= EPSILON) {
            return i - 1;
        }
    }

    return 0;
}

void Polynomial::trim() {
    while (coeffs_.size() > 1 &&
           std::abs(coeffs_.back()) < EPSILON) {
        coeffs_.pop_back();
    }

    if (coeffs_.empty()) {
        coeffs_.push_back(0.0);
    }
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    os << p.degree() << ' ';

    for (std::size_t i = 0; i <= p.degree(); ++i) {
        os << p[i] << ' ';
    }

    return os;
}

std::istream& operator>>(std::istream& is, Polynomial& p) {
    std::size_t degree;

    if (!(is >> degree)) {
        return is;
    }

    if (degree > MAX_DEGREE) {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::vector<double> coefficients(degree + 1);

    for (std::size_t i = 0; i <= degree; ++i) {
        if (!(is >> coefficients[i])) {
            return is;
        }
    }

    p = Polynomial(coefficients);
    return is;
}
