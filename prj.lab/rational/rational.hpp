#pragma once
#ifndef RATIONAL_RATIONAL_HPP_20241113
#define RATIONAL_RATIONAL_HPP_20241113

#include <cstdint>
#include <iosfwd>
#include <algorithm>
class Rational {
public:
	Rational() = default;
	Rational(const Rational&) = default;
	//Rational(Rational&&) = default;
	explicit Rational(const std::int32_t num) noexcept : num_(num) { }
	Rational(const std::int32_t num, const std::int32_t den);
	~Rational() = default;
	Rational& operator=(const Rational&) = default;
	//Rational& operator=(Rational&&) = default;

	[[nodiscard]] std::int32_t num() const noexcept { return num_; }
	[[nodiscard]] std::int32_t den() const noexcept { return den_; }

	[[nodiscard]] bool operator==(const Rational& rhs) const noexcept;
	[[nodiscard]] bool operator!=(const Rational& rhs) const noexcept;
	[[nodiscard]] bool operator<(const Rational& rhs) const noexcept;
	[[nodiscard]] bool operator<=(const Rational& rhs) const noexcept;
	[[nodiscard]] bool operator>(const Rational& rhs) const noexcept;
	[[nodiscard]] bool operator>=(const Rational& rhs) const noexcept;

	[[nodiscard]] Rational operator-() const noexcept { return { -num_, den_ }; }

	Rational& operator+=(const Rational& rhs) noexcept;
	Rational& operator-=(const Rational& rhs) noexcept;
	Rational& operator*=(const Rational& rhs) noexcept;
	Rational& operator/=(const Rational& rhs);

	Rational& operator+=(const int32_t& rhs) noexcept;
	Rational& operator-=(const int32_t& rhs) noexcept;
	Rational& operator*=(const int32_t& rhs) noexcept;
	Rational& operator/=(const int32_t& rhs);

	//! \brief ��������������� ����� � ����� ostrm ������������� ����� � ���� num/den.
	//!
	//! \param[in,out] ostrm - �����
	//! \retval �����
	std::ostream& WriteTo(std::ostream& ostrm) const noexcept;

	//! \brief ��������������� ���� �� ������ istrm ������������ ����� � ���� num/den.
	//!
	//! \param[in,out] istrm - �����
	//! \retval �����
	std::istream& ReadFrom(std::istream& istrm);

private:
	std::int32_t num_ = 0; //!< ���������
	std::int32_t den_ = 1; //!< �����������, > 0

	void Normalize() noexcept;
};

[[nodiscard]] Rational operator+(const Rational& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator-(const Rational& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator*(const Rational& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator/(const Rational& lhs, const Rational& rhs);

[[nodiscard]] Rational operator+(const Rational& lhs, const int32_t& rhs) noexcept;
[[nodiscard]] Rational operator-(const Rational& lhs, const int32_t& rhs) noexcept;
[[nodiscard]] Rational operator*(const Rational& lhs, const int32_t& rhs) noexcept;
[[nodiscard]] Rational operator/(const Rational& lhs, const int32_t& rhs);

[[nodiscard]] Rational operator+(const int32_t& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator-(const int32_t& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator*(const int32_t& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator/(const int32_t& lhs, const Rational& rhs);

inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept {
	return rhs.WriteTo(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, Rational& rhs) {
	return rhs.ReadFrom(istrm);
}
#endif
