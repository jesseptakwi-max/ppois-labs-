#include <cassert> 
#include "Polynomial.h"
int main() { Polynomial p{1.0, 2.0, 3.0}; // 1 + 2x + 3x^2
assert(p.degree() == 2);
assert(p(0.0) == 1.0);
assert(p(1.0) == 6.0);   // 1 + 2 + 3
assert(p(2.0) == 17.0);  // 1 + 4 + 12

Polynomial q{0.0, 1.0};  // x
Polynomial r = p + q;
assert(r[1] == 3.0);     // 2 + 1

Polynomial m = p * q;    // multiply by x
assert(m.degree() == 3);
assert(m[0] == 0.0);
assert(m[1] == 1.0);
assert(m[2] == 2.0);
assert(m[3] == 3.0);

Polynomial div = m / q;
assert(div == p);

return 0;}