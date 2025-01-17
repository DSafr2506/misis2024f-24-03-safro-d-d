#include "complex.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <cmath>


// Реализация методов класса Complex
Complex Complex::operator-() const noexcept {
    return Complex(-re, -im);
}

Complex& Complex::operator+=(const Complex& cmp1) noexcept {
    re += cmp1.re;
    im += cmp1.im;
    return *this;
}

Complex& Complex::operator+=(const double db) noexcept {
    re += db;
    return *this;
}

Complex& Complex::operator-=(const Complex& cmp1) noexcept {
    re -= cmp1.re;
    im -= cmp1.im;
    return *this;
}

Complex& Complex::operator-=(const double rhs) noexcept {
    re -= rhs;
    return *this;
}

Complex& Complex::operator*=(const Complex& cmp1) noexcept {
    double tempL = re * cmp1.re - im * cmp1.im;
    im = re * cmp1.im + im * cmp1.re;
    re = tempL;
    return *this;
}

Complex& Complex::operator*=(const double db) noexcept {
    re *= db;
    im *= db;
    return *this;
}

Complex& Complex::operator/=(const Complex& cmp1) {
    double denom = cmp1.re * cmp1.re + cmp1.im * cmp1.im;
    double tempL = (re * cmp1.re + im * cmp1.im) / denom;
    im = (im * cmp1.re - re * cmp1.im) / denom;
    re = tempL;
    return *this;
}

Complex& Complex::operator/=(const double db) {
    re /= db;
    im /= db;

    return *this;
}

// Реализация операторов вне класса
Complex operator+(const Complex& lhs, const Complex& rhs) noexcept {
    return Complex(lhs.re + rhs.re, lhs.im + rhs.im);
}

Complex operator+(const Complex& lhs, const double rhs) noexcept {
    return Complex(lhs.re + rhs, lhs.im);
}

Complex operator+(const double lhs, const Complex& rhs) noexcept {
    return Complex(lhs + rhs.re, rhs.im);
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept {
    return Complex(lhs.re - rhs.re, lhs.im - rhs.im);
}

Complex operator-(const Complex& lhs, const double rhs) noexcept {
    return Complex(lhs.re - rhs, lhs.im);
}

Complex operator-(const double lhs, const Complex& rhs) noexcept {
    return Complex(lhs - rhs.re, -rhs.im);
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept {
    return Complex(
        lhs.re * rhs.re - lhs.im * rhs.im,
        lhs.re * rhs.im + lhs.im * rhs.re
    );
}

Complex operator*(const Complex& lhs, const double rhs) noexcept {
    return Complex(lhs.re * rhs, lhs.im * rhs);
}

Complex operator*(const double lhs, const Complex& rhs) noexcept {
    return Complex(lhs * rhs.re, lhs * rhs.im);
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
    double denom = rhs.re * rhs.re + rhs.im * rhs.im;
    return Complex(
        (lhs.re * rhs.re + lhs.im * rhs.im) / denom,
        (lhs.im * rhs.re - lhs.re* rhs.im) / denom
    );
}

Complex operator/(const Complex& lhs, const double rhs) {
    return Complex(lhs.re / rhs, lhs.im / rhs);
}

Complex operator/(const double lhs, const Complex& rhs) {
    double denom = rhs.re * rhs.re + rhs.im * rhs.im;
    return Complex(
        (lhs * rhs.re) / denom,
        (-lhs * rhs.im) / denom
    );
}

bool Complex::operator==(const Complex& rhs) const noexcept {
    constexpr double eps = 2 * std::numeric_limits<double>::epsilon();
    return std::abs(re - rhs.re) <= eps && std::abs(im - rhs.im) <= eps;
}

bool Complex::operator!=(const Complex& rhs) const noexcept {
    return !(*this == rhs);
}


std::ostream& Complex::WriteTo(std::ostream& ostrm) const noexcept {
    ostrm << leftBrace << re << separator << im << rightBrace;
    return ostrm;
}

std::istream& Complex::ReadFrom(std::istream& istrm) noexcept {
    char left_brace = 0;
    char right_brace = 0;
    char sep = 0;
    double real_part = 0.0;
    double imag_part = 0.0;

    if (istrm >> left_brace && left_brace == leftBrace &&
        istrm >> real_part &&
        istrm >> sep && sep == separator &&
        istrm >> imag_part &&
        istrm >> right_brace && right_brace == rightBrace) {
        re = real_part;
        im = imag_part;
    }
    else {
        istrm.setstate(std::ios::failbit);
    }

    return istrm;
}

