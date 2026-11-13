#include "Polynomial.h"
 #include <cmath> 
 #include <stdexcept> 
 #include <algorithm>

Polynomial::Polynomial() : coeffs_{0.0} {}

Polynomial::Polynomial(const std::vector<double>& coeffs) : coeffs_(coeffs) { 
    trim();
 }

 Polynomial::Polynomial(std::initializer_list<double> coeffs) 
 : coeffs_(coeffs) { 
    trim(); 
}

Polynomial::Polynomial(const Polynomial& other) : coeffs_(other.coeffs_) {}

Polynomial& Polynomial::operator=(const Polynomial& other) { 
    if (this != &other) { 
        coeffs_ = other.coeffs_; 
    }
    return *this; 
}

bool Polynomial::operator==(const Polynomial& other) const { 
    return coeffs_ == other.coeffs_; 
}

bool Polynomial::operator!=(const Polynomial& other) const { 
    return !(*this == other); 
}

double Polynomial::operator[](std::size_t degree) const { 
    if (degree >= coeffs_.size()) return 0.0; 
    return coeffs_[degree]; 
}

double& Polynomial::operator[](std::size_t degree) { 
    if (degree >= coeffs_.size()) { 
        coeffs_.resize(degree + 1, 0.0);
     } 
     return coeffs_[degree]; 
    }

double Polynomial::operator()(double x) const { 
    double result = 0.0; 
    double power = 1.0; 
    for (double c : coeffs_) { 
        result += c * power; 
        power *= x; 
    } 
    return result; 
}

Polynomial Polynomial::operator+(const Polynomial& rhs) const { 
    std::size_t maxDeg = std::max(coeffs_.size(), rhs.coeffs_.size()); 
    std::vector<double> result(maxDeg, 0.0);

    for (std::size_t i = 0; i < maxDeg; ++i) {
    double a = (i < coeffs_.size()) ? coeffs_[i] : 0.0;
    double b = (i < rhs.coeffs_.size()) ? rhs.coeffs_[i] : 0.0;
    result[i] = a + b;
}
return Polynomial(result);
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) { 
    *this = *this + rhs; 
    return *this; 
}

Polynomial Polynomial::operator-(const Polynomial& rhs) const { 
    std::size_t maxDeg = std::max(coeffs_.size(), rhs.coeffs_.size()); 
    std::vector<double> result(maxDeg, 0.0);

for (std::size_t i = 0; i < maxDeg; ++i) {
    double a = (i < coeffs_.size()) ? coeffs_[i] : 0.0;
    double b = (i < rhs.coeffs_.size()) ? rhs.coeffs_[i] : 0.0;
    result[i] = a - b;
}
return Polynomial(result);
}

Polynomial& Polynomial::operator-=(const Polynomial& rhs) { 
    *this = *this - rhs; return *this; 
}

Polynomial Polynomial::operator*(const Polynomial& rhs) const { 
    std::size_t degA = coeffs_.size(); 
    std::size_t degB = rhs.coeffs_.size(); 
    std::vector<double> result(degA + degB - 1, 0.0);

    for (std::size_t i = 0; i < degA; ++i) {
    
        for (std::size_t j = 0; j < degB; ++j) {
        
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
    if (rhs.degree() == 0 && std::abs(rhs[0]) < 1e-12) { 
        throw std::runtime_error("Division by zero polynomial"); 
    }
     
Polynomial dividend(*this);
Polynomial divisor(rhs);

int diffDeg = static_cast<int>(dividend.degree()) -
              static_cast<int>(divisor.degree());
std::size_t qSize = (diffDeg >= 0) ? static_cast<std::size_t>(diffDeg + 1) : 1;
std::vector<double> quotient(qSize, 0.0);

while (dividend.degree() >= divisor.degree() &&
       !(dividend.degree() == 0 && std::abs(dividend[0]) < 1e-12)) {

    std::size_t diff = dividend.degree() - divisor.degree();
    double factor = dividend[dividend.degree()] / divisor[divisor.degree()];
    quotient[diff] = factor;

    for (std::size_t i = 0; i <= divisor.degree(); ++i) {
        dividend[diff + i] -= factor * divisor[i];
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
    if (coeffs_.empty()) return 0; 
    return coeffs_.size() - 1; 
}

void Polynomial::trim() { 
    while (coeffs_.size() > 1 && std::abs(coeffs_.back()) < 1e-12) { 
        coeffs_.pop_back(); 
    } 
     if (coeffs_.empty()) coeffs_.push_back(0.0); 

    }
std::ostream& operator<<(std::ostream& os, const Polynomial& p) { 
    os << p.degree() << " "; 
    for (std::size_t i = 0; i <= p.degree(); ++i) { 
        os << p[i] << " "; 
    } 
        return os; 
    }
    std::istream& operator>>(std::istream& is, Polynomial& p) { 
        std::size_t deg; 
        if (!(is >> deg)) return is; 
        std::vector<double> coeffs(deg + 1, 0.0); 
        for (std::size_t i = 0; i <= deg; ++i) { 
            is >> coeffs[i]; 
        }
         p = Polynomial(coeffs); 
         return is;
        
        }