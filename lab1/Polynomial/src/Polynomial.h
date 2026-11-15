/**
 * @file Polynomial.h
 * @brief Declaration of the Polynomial class.
 *
 * Defines a single-variable polynomial with arithmetic,
 * comparison, evaluation and stream input/output operations.
 */

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <iostream>
#include <initializer_list>

/**
 * @brief Represents a single-variable polynomial.
 *
 * Coefficients are stored in order of increasing degree.
 * The coefficient at index i belongs to the term x^i.
 */
class Polynomial {
public:
    /**
     * @brief Default constructor. Creates a zero polynomial.
     */
    Polynomial();

    /**
     * @brief Creates a polynomial from a vector of coefficients.
     * @param coeffs Coefficients ordered from degree 0 upwards.
     */
    explicit Polynomial(const std::vector<double>& coeffs);

    /**
     * @brief Creates a polynomial from an initializer list.
     * @param coeffs Coefficients ordered from degree 0 upwards.
     */
    Polynomial(std::initializer_list<double> coeffs);

    /**
     * @brief Copy constructor.
     * @param other The polynomial to copy.
     */
    Polynomial(const Polynomial& other);

    /**
     * @brief Copy assignment operator.
     * @param other The polynomial to copy.
     * @return Reference to this polynomial.
     */
    Polynomial& operator=(const Polynomial& other);

    /**
     * @brief Checks whether two polynomials are equal.
     * @param other The polynomial to compare with.
     * @return true if equal, otherwise false.
     */
    bool operator==(const Polynomial& other) const;

    /**
     * @brief Checks whether two polynomials are different.
     * @param other The polynomial to compare with.
     * @return true if different, otherwise false.
     */
    bool operator!=(const Polynomial& other) const;

    /**
     * @brief Gets a coefficient without modifying it.
     * @param degree Degree of the requested term.
     * @return The coefficient at that degree.
     */
    double operator[](std::size_t degree) const;

    /**
     * @brief Gets a modifiable reference to a coefficient.
     * @param degree Degree of the requested term.
     * @return Reference to the coefficient.
     */
    double& operator[](std::size_t degree);

    /**
     * @brief Evaluates the polynomial at a given point.
     * @param x Value of the variable.
     * @return Value of the polynomial at x.
     */
    double operator()(double x) const;

    /**
     * @brief Adds two polynomials.
     * @param rhs Polynomial to add.
     * @return A new polynomial equal to the sum.
     */
    Polynomial operator+(const Polynomial& rhs) const;

    /**
     * @brief Adds another polynomial in place.
     * @param rhs Polynomial to add.
     * @return Reference to this polynomial.
     */
    Polynomial& operator+=(const Polynomial& rhs);

    /**
     * @brief Subtracts another polynomial.
     * @param rhs Polynomial to subtract.
     * @return A new polynomial equal to the difference.
     */
    Polynomial operator-(const Polynomial& rhs) const;

    /**
     * @brief Subtracts another polynomial in place.
     * @param rhs Polynomial to subtract.
     * @return Reference to this polynomial.
     */
    Polynomial& operator-=(const Polynomial& rhs);

    /**
     * @brief Multiplies two polynomials.
     * @param rhs Polynomial to multiply by.
     * @return A new polynomial equal to the product.
     */
    Polynomial operator*(const Polynomial& rhs) const;

    /**
     * @brief Multiplies another polynomial in place.
     * @param rhs Polynomial to multiply by.
     * @return Reference to this polynomial.
     */
    Polynomial& operator*=(const Polynomial& rhs);

    /**
     * @brief Divides this polynomial by another.
     * @param rhs Divisor polynomial.
     * @return A new polynomial equal to the quotient.
     * @throws std::runtime_error if the divisor is zero.
     */
    Polynomial operator/(const Polynomial& rhs) const;

    /**
     * @brief Divides this polynomial by another in place.
     * @param rhs Divisor polynomial.
     * @return Reference to this polynomial.
     * @throws std::runtime_error if the divisor is zero.
     */
    Polynomial& operator/=(const Polynomial& rhs);

    /**
     * @brief Gets the degree of the polynomial.
     * @return Highest power of x with a non-zero coefficient.
     */
    std::size_t degree() const;

    /**
     * @brief Writes the polynomial to an output stream.
     * @param os Output stream.
     * @param p Polynomial to write.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);

    /**
     * @brief Reads a polynomial from an input stream.
     * @param is Input stream.
     * @param p Polynomial to populate.
     * @return Reference to the input stream.
     */
    friend std::istream& operator>>(std::istream& is, Polynomial& p);

private:
    /// Coefficients stored in increasing order of degree.
    std::vector<double> coeffs_;

    /**
     * @brief Removes unnecessary trailing zero coefficients.
     *
     * Keeps the coefficient vector in normalized form.
     */
    void trim();
};

#endif // POLYNOMIAL_H