#include "Polynomial.h"

#include <cassert>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <vector>

int main() {
    Polynomial zero;
    assert(zero.degree() == 0);
    assert(zero[0] == 0.0);
    assert(zero[10] == 0.0);

    Polynomial p{1.0, 2.0, 3.0};
    Polynomial pCopy(p);
    assert(pCopy == p);
    assert(!(pCopy != p));
    assert(p.degree() == 2);
    assert(p(0.0) == 1.0);
    assert(p(1.0) == 6.0);
    assert(p(2.0) == 17.0);

    Polynomial fromVector(std::vector<double>{1.0, 2.0, 3.0, 0.0});
    assert(fromVector == p); // trailing zero is trimmed
    Polynomial assigned;
    assigned = p;
    assert(assigned == p);
    Polynomial* sameObject = &assigned;
    assigned = *sameObject;
    assert(assigned == p);

    assert(p[1] == 2.0);
    Polynomial expandable{1.0};
    expandable[3] = 4.0; // mutable subscript grows the polynomial
    assert(expandable.degree() == 3);
    assert(expandable[3] == 4.0);

    Polynomial q{0.0, 1.0};
    Polynomial sum = p + q;
    assert(sum == Polynomial({1.0, 3.0, 3.0}));
    Polynomial difference = p - q;
    assert(difference == Polynomial({1.0, 1.0, 3.0}));
    Polynomial product = p * q;
    assert(product == Polynomial({0.0, 1.0, 2.0, 3.0}));

    Polynomial compound{1.0, 2.0};
    compound += q;
    assert(compound == Polynomial({1.0, 3.0}));
    compound -= q;
    assert(compound == Polynomial({1.0, 2.0}));
    compound *= q;
    assert(compound == Polynomial({0.0, 1.0, 2.0}));
    compound /= q;
    assert(compound == Polynomial({1.0, 2.0}));

    assert((product / q) == p);
    assert((q / p) == Polynomial({0.0})); // dividend degree is smaller
    bool divisionByZeroThrown = false;
    try {
        (void)(p / Polynomial{0.0});
    } catch (const std::runtime_error&) {
        divisionByZeroThrown = true;
    }
    assert(divisionByZeroThrown);

    Polynomial unequal{1.0};
    assert(p != unequal);
    assert(unequal == Polynomial({1.0}));

    std::stringstream output;
    output << p;
    Polynomial parsed;
    output >> parsed;
    assert(parsed == p);

    std::stringstream input("2 1 2 3");
    Polynomial extracted;
    input >> extracted;
    assert(extracted == p);

    return 0;
}
