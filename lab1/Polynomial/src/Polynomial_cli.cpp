#include <iostream> 
#include <vector>
 #include "Polynomial.h"
Polynomial readPoly() { std::size_t deg; std::cout << "Enter degree: "; std::cin >> deg;
std::vector<double> c(deg + 1);
for (std::size_t i = 0; i <= deg; ++i) {
    std::cout << "Coefficient for x^" << i << ": ";
    std::cin >> c[i];
}
return Polynomial(c);}
int main() { Polynomial A, B; bool hasA = false, hasB = false;
while (true) {
    std::cout << "\n=== Polynomial Menu ===\n";
    std::cout << "1. Create A\n";
    std::cout << "2. Create B\n";
    std::cout << "3. Evaluate A at x\n";
    std::cout << "4. A + B\n";
    std::cout << "5. A - B\n";
    std::cout << "6. A * B\n";
    std::cout << "7. A / B\n";
    std::cout << "8. Print A\n";
    std::cout << "9. Print B\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";

    int ch;
    std::cin >> ch;
    if (!std::cin) {
        std::cout << "Invalid input, exiting.\n";
        break;
    }

    if (ch == 0) break;

    switch (ch) {
    case 1:
        A = readPoly();
        hasA = true;
        break;
    case 2:
        B = readPoly();
        hasB = true;
        break;
    case 3:
        if (!hasA) {
            std::cout << "Create A first.\n";
            break;
        }
        double x;
        std::cout << "x = ";
        std::cin >> x;
        std::cout << "A(" << x << ") = " << A(x) << "\n";
        break;
    case 4:
        if (hasA && hasB) {
            Polynomial C = A + B;
            std::cout << "A + B = " << C << "\n";
        } else {
            std::cout << "Create both A and B first.\n";
        }
        break;
    case 5:
        if (hasA && hasB) {
            Polynomial C = A - B;
            std::cout << "A - B = " << C << "\n";
        } else {
            std::cout << "Create both A and B first.\n";
        }
        break;
    case 6:
        if (hasA && hasB) {
            Polynomial C = A * B;
            std::cout << "A * B = " << C << "\n";
        } else {
            std::cout << "Create both A and B first.\n";
        }
        break;
    case 7:
        if (hasA && hasB) {
            try {
                Polynomial C = A / B;
                std::cout << "A / B (quotient) = " << C << "\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        } else {
            std::cout << "Create both A and B first.\n";
        }
        break;
    case 8:
        if (hasA) std::cout << "A = " << A << "\n";
        else std::cout << "Create A first.\n";
        break;
    case 9:
        if (hasB) std::cout << "B = " << B << "\n";
        else std::cout << "Create B first.\n";
        break;
    default:
        std::cout << "Unknown choice.\n";
        break;
    }
}

return 0;
}