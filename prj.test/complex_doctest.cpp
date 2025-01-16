#include <complex/complex.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include"doctest/doctest.h"

TEST_SUITE("Complex") {

    TEST_CASE("Default Constructor") {
        Complex c;
        CHECK(c.re == 0.0);
        CHECK(c.im == 0.0);
    }

    TEST_CASE("Parameterized Constructors") {
        Complex c1(5.0);
        CHECK(c1.re == 5.0);
        CHECK(c1.im == 0.0);

        Complex c2(3.0, 4.0);
        CHECK(c2.re == 3.0);
        CHECK(c2.im == 4.0);
    }

    TEST_CASE("Equality Operators") {
        Complex c1(1.0, 2.0);
        Complex c2(1.0, 2.0);
        Complex c3(2.0, 3.0);

        CHECK(c1 == c2);
        CHECK(c1 != c3);
    }

    TEST_CASE("Unary Minus") {
        Complex c(1.0, -2.0);
        Complex negC = -c;

        CHECK(negC.re == -1.0);
        CHECK(negC.im == 2.0);
    }

    TEST_CASE("Arithmetic Operations") {
        Complex c1(1.0, 2.0);
        Complex c2(3.0, 4.0);

        SUBCASE("Addition") {
            Complex result = c1 + c2;
            CHECK(result.re == 4.0);
            CHECK(result.im == 6.0);

            result = c1 + 5.0;
            CHECK(result.re == 6.0);
            CHECK(result.im == 2.0);

            result = 5.0 + c1;
            CHECK(result.re == 6.0);
            CHECK(result.im == 2.0);
        }

        SUBCASE("Subtraction") {
            Complex result = c1 - c2;
            CHECK(result.re == -2.0);
            CHECK(result.im == -2.0);

            result = c1 - 1.0;
            CHECK(result.re == 0.0);
            CHECK(result.im == 2.0);

            result = 5.0 - c1;
            CHECK(result.re == 4.0);
            CHECK(result.im == -2.0);
        }

        SUBCASE("Multiplication") {
            Complex result = c1 * c2;
            CHECK(result.re == -5.0);
            CHECK(result.im == 10.0);

            result = c1 * 2.0;
            CHECK(result.re == 2.0);
            CHECK(result.im == 4.0);

            result = 2.0 * c1;
            CHECK(result.re == 2.0);
            CHECK(result.im == 4.0);
        }

        SUBCASE("Division") {
            Complex result = c1 / c2;
            CHECK(result.re == doctest::Approx(0.44));
            CHECK(result.im == doctest::Approx(0.08));

            result = c1 / 2.0;
            CHECK(result.re == 0.5);
            CHECK(result.im == 1.0);
        }
    }

    TEST_CASE("Compound Assignment Operators") {
        Complex c(1.0, 2.0);
        Complex c2(3.0, 4.0);

        SUBCASE("Addition Assignment") {
            c += c2;
            CHECK(c.re == 4.0);
            CHECK(c.im == 6.0);

            c += 1.0;
            CHECK(c.re == 5.0);
            CHECK(c.im == 6.0);
        }

        SUBCASE("Subtraction Assignment") {
            c -= c2;
            CHECK(c.re == -2.0);
            CHECK(c.im == -2.0);

            c -= 1.0;
            CHECK(c.re == -3.0);
            CHECK(c.im == -2.0);
        }

        SUBCASE("Multiplication Assignment") {
            c *= c2;
            CHECK(c.re == -5.0);
            CHECK(c.im == 10.0);

            c *= 2.0;
            CHECK(c.re == -10.0);
            CHECK(c.im == 20.0);
        }

        SUBCASE("Division Assignment") {
            c /= c2;
            CHECK(c.re == doctest::Approx(0.44));
            CHECK(c.im == doctest::Approx(0.08));

            c /= 2.0;
            CHECK(c.re == doctest::Approx(0.22));
            CHECK(c.im == doctest::Approx(0.04));
        }
    }

    TEST_CASE("Stream Operations") {
        SUBCASE("WriteTo") {
            Complex c(1.0, -2.0);
            std::ostringstream oss;
            oss << c;
            CHECK(oss.str() == "{1,-2}");
        }

        SUBCASE("ReadFrom") {
            Complex c;
            std::istringstream iss("{3.5,4.2}");
            iss >> c;
            CHECK(c.re == 3.5);
            CHECK(c.im == 4.2);

            std::istringstream invalid("{3.5;4.2}");
            invalid >> c;
            CHECK(invalid.fail());
        }
    }
}
