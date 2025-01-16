#include <rational/rational.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_SUITE("Rational") {

    TEST_CASE("[rational] - constructors") {
        CHECK(Rational() == Rational(0));
        CHECK(Rational(0, 1) == Rational(0, 5));
        CHECK_THROWS_AS(Rational(1, 0), std::invalid_argument);
    }

    TEST_CASE("Default Constructor") {
        Rational c;
        CHECK(c.num() == 0);
        CHECK(c.den() == 1);
    }

    TEST_CASE("Parameterized Constructors") {
        Rational c1(5);
        CHECK(c1.num() == 5);
        CHECK(c1.den() == 1);

        Rational c2(3, 4);
        CHECK(c2.num() == 3);
        CHECK(c2.den() == 4);

        CHECK_THROWS_AS(Rational(1, 0), std::invalid_argument);
    }

    TEST_CASE("Equality Operators") {
        Rational c1(1, 2);
        Rational c2(1, 2);
        Rational c3(2, 3);

        CHECK(c1 == c2);
        CHECK(c1 != c3);
    }

    TEST_CASE("Unary Minus") {
        Rational c(1, -2);
        Rational negC = -c;

        CHECK(negC.num() == 1);
        CHECK(negC.den() == 2);
        CHECK(c.num() == -1);
        CHECK(c.den() == 2);
    }

    TEST_CASE("Arithmetic Operations") {
        Rational c1(1, 2);
        Rational c2(3, 4);

        SUBCASE("Addition") {
            Rational result = c1 + c2;
            CHECK(result.num() == 5);
            CHECK(result.den() == 4);

            result = c1 + 5;
            CHECK(result.num() == 11);
            CHECK(result.den() == 2);
        }

        SUBCASE("Subtraction") {
            Rational result = c1 - c2;
            CHECK(result.num() == -1);
            CHECK(result.den() == 4);

            result = c1 - 1;
            CHECK(result.num() == -1);
            CHECK(result.den() == 2);
        }

        SUBCASE("Multiplication") {
            Rational result = c1 * c2;
            CHECK(result.num() == 3);
            CHECK(result.den() == 8);

            result = c1 * 2;
            CHECK(result.num() == 1);
            CHECK(result.den() == 1);
        }

        SUBCASE("Division") {
            Rational result = c1 / c2;
            CHECK(result.num() == 2);
            CHECK(result.den() == 3);

            CHECK_THROWS_AS(c1 / Rational(0, 1), std::invalid_argument);
        }
    }

    TEST_CASE("Compound Assignment Operators") {
        Rational c(1, 2);
        Rational c2(3, 4);

        SUBCASE("Addition Assignment") {
            c += c2;
            CHECK(c.num() == 5);
            CHECK(c.den() == 4);

            c += 1;
            CHECK(c.num() == 9);
            CHECK(c.den() == 4);
        }

        SUBCASE("Subtraction Assignment") {
            c -= c2;
            CHECK(c.num() == -1);
            CHECK(c.den() == 4);

            c -= 1;
            CHECK(c.num() == -5);
            CHECK(c.den() == 4);
        }

        SUBCASE("Multiplication Assignment") {
            c *= c2;
            CHECK(c.num() == 3);
            CHECK(c.den() == 8);

            c *= 2;
            CHECK(c.num() == 3);
            CHECK(c.den() == 4);
        }

        SUBCASE("Division Assignment") {
            c /= c2;
            CHECK(c.num() == 2);
            CHECK(c.den() == 3);

            c /= 2;
            CHECK(c.num() == 1);
            CHECK(c.den() == 3);
        }
    }

    TEST_CASE("Stream Operations") {
        SUBCASE("WriteTo") {
            Rational c(1, -2);
            std::ostringstream oss;
            oss << c;
            CHECK(oss.str() == "-1/2");
        }

        SUBCASE("ReadFrom") {
            Rational c;
            std::istringstream iss("3/4");
            iss >> c;
            CHECK(c.num() == 3);
            CHECK(c.den() == 4);

            std::istringstream invalid("3|4");
            invalid >> c;
            CHECK(invalid.fail());
        }
    }
}
