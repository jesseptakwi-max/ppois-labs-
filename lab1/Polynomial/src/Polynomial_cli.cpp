
#include "Polynomial.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

namespace {
constexpr std::size_t MAX_DEGREE = 10000;

bool readPolynomial(Polynomial& polynomial) {
    std::size_t degree;

    std::cout << "Enter degree: ";

    if (!(std::cin >> degree) || degree > MAX_DEGREE) {
        std::cout << "Invalid degree. Please enter a value from 0 to "
                  << MAX_DEGREE << ".\n";
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    std::vector<double> coefficients(degree + 1);

    for (std::size_t i = 0; i <= degree; ++i) {
        std::cout << "Coefficient for x^" << i << ": ";

        if (!(std::cin >> coefficients[i])) {
            std::cout << "Invalid coefficient. Polynomial was not created.\n";
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
    }

    polynomial = Polynomial(coefficients);
    return true;
}

bool readNumber(double& value) {
    std::cout << "Enter x: ";

    if (std::cin >> value) {
        return true;
    }

    std::cout << "Invalid number.\n";
    std::cin.clear();
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

void printMenu() {
    std::cout << "\n=== Polynomial Menu ===\n"
              << "1. Create A\n"
              << "2. Create B\n"
              << "3. Evaluate A at x\n"
              << "4. A + B\n"
              << "5. A - B\n"
              << "6. A * B\n"
              << "7. A / B\n"
              << "8. Print A\n"
              << "9. Print B\n"
              << "0. Exit\n"
              << "Choice: ";
}
}

int main() {
    Polynomial A;
    Polynomial B;
    bool hasA = false;
    bool hasB = false;

    while (true) {
        printMenu();

        int choice;

        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                break;
            }

            std::cout << "Invalid menu input. Try again.\n";
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) {
            std::cout << "Goodbye!\n";
            break;
        }

        switch (choice) {
        case 1:
            hasA = readPolynomial(A);
            break;

        case 2:
            hasB = readPolynomial(B);
            break;

        case 3: {
            if (!hasA) {
                std::cout << "Create A first.\n";
                break;
            }

            double x;

            if (readNumber(x)) {
                std::cout << "A(" << x << ") = " << A(x) << '\n';
            }
            break;
        }

        case 4:
            if (hasA && hasB) {
                std::cout << "A + B = " << A + B << '\n';
            } else {
                std::cout << "Create both A and B first.\n";
            }
            break;

        case 5:
            if (hasA && hasB) {
                std::cout << "A - B = " << A - B << '\n';
            } else {
                std::cout << "Create both A and B first.\n";
            }
            break;

        case 6:
            if (hasA && hasB) {
                std::cout << "A * B = " << A * B << '\n';
            } else {
                std::cout << "Create both A and B first.\n";
            }
            break;

        case 7:
            if (!hasA || !hasB) {
                std::cout << "Create both A and B first.\n";
                break;
            }

            try {
                std::cout << "A / B (quotient) = " << A / B << '\n';
            } catch (const std::exception& error) {
                std::cout << "Error: " << error.what() << '\n';
            }
            break;

        case 8:
            if (hasA) {
                std::cout << "A = " << A << '\n';
            } else {
                std::cout << "Create A first.\n";
            }
            break;

        case 9:
            if (hasB) {
                std::cout << "B = " << B << '\n';
            } else {
                std::cout << "Create B first.\n";
            }
            break;

        default:
            std::cout << "Unknown choice. Try again.\n";
            break;
        }
    }

    return 0;
}
