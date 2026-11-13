#ifndef POLYNOMIAL_H 
#define POLYNOMIAL_H

#include <vector> 
#include <iostream> 
#include <initializer_list>
class Polynomial { public: Polynomial(); 
    explicit Polynomial(const std::vector<double>& coeffs); 
    Polynomial(std::initializer_list<double> coeffs); 
    Polynomial(const Polynomial& other); 
    Polynomial& operator=(const Polynomial& other);

bool operator==(const Polynomial& other) const;
bool operator!=(const Polynomial& other) const;

double operator[](std::size_t degree) const;
double& operator[](std::size_t degree);

double operator()(double x) const;

Polynomial operator+(const Polynomial& rhs) const;
Polynomial& operator+=(const Polynomial& rhs);

Polynomial operator-(const Polynomial& rhs) const;
Polynomial& operator-=(const Polynomial& rhs);

Polynomial operator*(const Polynomial& rhs) const;
Polynomial& operator*=(const Polynomial& rhs);

Polynomial operator/(const Polynomial& rhs) const;
Polynomial& operator/=(const Polynomial& rhs);

std::size_t degree() const;

friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
friend std::istream& operator>>(std::istream& is, Polynomial& p);

private: 
std::vector<double> coeffs_; 
void trim(); 
};

#endif