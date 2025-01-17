#include "rational.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <algorithm>

// Реализация методов класса Rational
Rational::Rational(const std::int32_t num, const std::int32_t den)
    : num_(num), den_(den) {
    if (0 == den_) {
        throw std::invalid_argument("Zero denominator in Rational constructor");
    }
    Normalize();
}
int32_t gcd(int32_t a, int32_t b) {
    while (b != 0) {
        int32_t temp = b;
        b = a % b;
        a = temp;
    }
    return std::abs(a);
}


void Rational::Normalize() noexcept {
    int32_t a = gcd(num_, den_);
    num_ /= a;
    den_ /= a;
    if (den_ < 0) {
        num_ = -num_;
        den_ = -den_;
    }
}

Rational& Rational::operator+=(const Rational& rhs) noexcept {
    num_ = num_ * rhs.den_ + rhs.num_ * den_;
    den_ *= rhs.den_;
    Normalize();
    return *this;
}

Rational& Rational::operator+=(const int32_t& rhs) noexcept {
    return *this += Rational(rhs);
}

Rational& Rational::operator-=(const Rational& rhs) noexcept {
    num_ = num_ * rhs.den_ - rhs.num_ * den_;
    den_ *= rhs.den_;
    Normalize();
    return *this;
}

Rational& Rational::operator-=(const int32_t& rhs) noexcept {
    return *this -= Rational(rhs);
}

Rational& Rational::operator*=(const Rational& rhs) noexcept {
    num_ *= rhs.num_;
    den_ *= rhs.den_;
    Normalize();
    return *this;
}

Rational& Rational::operator*=(const int32_t& rhs) noexcept {
    return *this *= Rational(rhs);
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.num_ == 0) {
        throw std::invalid_argument("Division by zero");
    }
    num_ *= rhs.den_;
    den_ *= rhs.num_;
    Normalize();
    return *this;
}

Rational& Rational::operator/=(const int32_t& rhs) {
    if (rhs == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return *this /= Rational(rhs);
}

bool Rational::operator==(const Rational& rhs) const noexcept {
    return (num_ == rhs.num_ && den_ == rhs.den_);
}

bool Rational::operator!=(const Rational& rhs) const noexcept {
    return !(*this == rhs);
}

Rational operator+(const Rational& lhs, const Rational& rhs) noexcept {
    Rational s(lhs);
    return s += rhs;
}

Rational operator+(const Rational& lhs, const int32_t& rhs) noexcept {
    Rational s(lhs);
    return s += rhs;
}

Rational operator+(const int32_t& lhs, const Rational& rhs) noexcept {
    Rational s(rhs);
    return s += lhs;
}

Rational operator-(const Rational& lhs, const Rational& rhs) noexcept {
    Rational s(lhs);
    return s -= rhs;
}

Rational operator-(const Rational& lhs, const int32_t& rhs) noexcept {
    Rational s(lhs);
    return s -= rhs;
}

Rational operator-(const int32_t& lhs, const Rational& rhs) noexcept {
    return Rational(lhs) -= rhs;
}

Rational operator*(const Rational& lhs, const Rational& rhs) noexcept {
    Rational s(lhs);
    return s *= rhs;
}

Rational operator*(const Rational& lhs, const int32_t& rhs) noexcept {
    Rational s(lhs);
    return s *= rhs;
}

Rational operator*(const int32_t& lhs, const Rational& rhs) noexcept {
    Rational s(rhs);
    return s *= lhs;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational s(lhs);
    return s /= rhs;
}

Rational operator/(const Rational& lhs, const int32_t& rhs) {
    Rational s(lhs);
    return s /= rhs;
}

Rational operator/(const int32_t& lhs, const Rational& rhs) {
    return Rational(lhs) /= rhs;
}

std::ostream& Rational::WriteTo(std::ostream& ostrm) const noexcept {
    char del = '/';
    ostrm << num_ << del << den_;
    return ostrm;
}

std::istream& Rational::ReadFrom(std::istream& istrm) {
    char slash = '\0';
    int32_t numerator = 0;
    int32_t denominator = 1;

    // Считываем числитель и символ '/'
    if (istrm >> numerator) {
        slash = istrm.get();  // Читаем следующий символ вручную
        if (slash == '/') {
            // Проверяем, что следующий символ не пробел
            if (istrm.peek() == ' ') {
                istrm.setstate(std::ios_base::failbit);
                return istrm;
            }

            // Считываем знаменатель
            if (istrm >> denominator) {
                if (denominator == 0) {
                    throw std::invalid_argument("Zero denominator in input stream");
                }
                num_ = numerator;
                den_ = denominator;
            }
            else {
                istrm.setstate(std::ios_base::failbit);
            }
        }
        else {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    else {
        istrm.setstate(std::ios_base::failbit);
    }
    return istrm;
}




bool Rational::operator<(const Rational& rhs) const noexcept {
    return num_ * rhs.den_ < rhs.num_ * den_;
}

bool Rational::operator<=(const Rational& rhs) const noexcept {
    return *this < rhs || *this == rhs;
}

bool Rational::operator>(const Rational& rhs) const noexcept {
    return num_ * rhs.den_ > rhs.num_ * den_;
}

bool Rational::operator>=(const Rational& rhs) const noexcept {
    return *this > rhs || *this == rhs;
}
