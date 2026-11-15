
#include "Polynomial.h"

#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <stdexcept>
#include <vector>

TEST_CASE("Polynomial construction and basic properties") {
    Polynomial zero;

    REQUIRE(zero.degree() == 0);
    REQUIRE(zero[0] == 0.0);
    REQUIRE(zero[10] == 0.0);

    Polynomial p{1.0, 2.0, 3.0};

    REQUIRE(p.degree() == 2);
    REQUIRE(p(0.0) == 1.0);
    REQUIRE(p(1.0) == 6.0);
    REQUIRE(p(2.0) == 17.0);

    Polynomial fromVector(std::vector<double>{1.0, 2.0, 3.0, 0.0});
    REQUIRE(fromVector == p);
}

TEST_CASE("Polynomial copying and assignment") {
    Polynomial p{1.0, 2.0, 3.0};

    Polynomial copied(p);
    REQUIRE(copied == p);
    REQUIRE_FALSE(copied != p);

    Polynomial assigned;
    assigned = p;
    REQUIRE(assigned == p);

    Polynomial* sameObject = &assigned;
    assigned = *sameObject;
    REQUIRE(assigned == p);
}

TEST_CASE("Polynomial coefficient access and degree normalization") {
    Polynomial p{1.0, 2.0, 3.0};

    p[2] = 0.0;
    REQUIRE(p.degree() == 1);
    REQUIRE(p == Polynomial({1.0, 2.0}));

    Polynomial equivalent{1.0, 2.0, 0.0};
    REQUIRE(equivalent == Polynomial({1.0, 2.0}));

    Polynomial expandable{1.0};
    expandable[3] = 4.0;

    REQUIRE(expandable.degree() == 3);
    REQUIRE(expandable[3] == 4.0);
    REQUIRE(expandable[2] == 0.0);
}

TEST_CASE("Polynomial arithmetic operations") {
    Polynomial p{1.0, 2.0, 3.0};
    Polynomial q{0.0, 1.0};

    REQUIRE((p + q) == Polynomial({1.0, 3.0, 3.0}));
    REQUIRE((p - q) == Polynomial({1.0, 1.0, 3.0}));
    REQUIRE((p * q) == Polynomial({0.0, 1.0, 2.0, 3.0}));
}

TEST_CASE("Polynomial compound arithmetic operations") {
    Polynomial q{0.0, 1.0};
    Polynomial compound{1.0, 2.0};

    compound += q;
    REQUIRE(compound == Polynomial({1.0, 3.0}));

    compound -= q;
    REQUIRE(compound == Polynomial({1.0, 2.0}));

    compound *= q;
    REQUIRE(compound == Polynomial({0.0, 1.0, 2.0}));

    compound /= q;
    REQUIRE(compound == Polynomial({1.0, 2.0}));
}

TEST_CASE("Polynomial division") {
    Polynomial p{1.0, 2.0, 3.0};
    Polynomial q{0.0, 1.0};

    REQUIRE(((p * q) / q) == p);
    REQUIRE((q / p) == Polynomial({0.0}));

    Polynomial dividend{1.0, 2.0, 3.0};
    REQUIRE((dividend / q) == Polynomial({2.0, 3.0}));

    REQUIRE_THROWS_AS(p / Polynomial{0.0}, std::runtime_error);
}

TEST_CASE("Polynomial equality and inequality") {
    Polynomial p{1.0, 2.0, 3.0};
    Polynomial unequal{1.0};

    REQUIRE(p != unequal);
    REQUIRE(unequal == Polynomial({1.0}));
}

TEST_CASE("Polynomial stream input and output") {
    Polynomial p{1.0, 2.0, 3.0};

    std::stringstream output;
    output << p;

    Polynomial parsed;
    output >> parsed;

    REQUIRE(parsed == p);

    std::stringstream input("2 1 2 3");
    Polynomial extracted;
    input >> extracted;

    REQUIRE(extracted == p);
}

TEST_CASE("Polynomial rejects incomplete and oversized input") {
    Polynomial unchanged{5.0, 6.0};

    std::stringstream incomplete("2 1 2");
    incomplete >> unchanged;

    REQUIRE(incomplete.fail());
    REQUIRE(unchanged == Polynomial({5.0, 6.0}));

    std::stringstream invalid("10001");
    invalid >> unchanged;

    REQUIRE(invalid.fail());
    REQUIRE(unchanged == Polynomial({5.0, 6.0}));
}
