#pragma once

#include <concepts>
#include <numeric>
#include <type_traits>

namespace water {
	namespace rational_number {
		namespace concept_helper {
			template<class Rational_Number>
			concept rational_number = requires (Rational_Number rational_number) {
				rational_number.numerator();
				rational_number.denominator();
			};
		}
		template<std::integral Integral, std::unsigned_integral Unsigned_Integral>
		class rational_number {
		public:
			rational_number() : m_numerator{ 0 }, m_denominator{ 1 } {}
			rational_number(Integral n) : m_numerator{ n }, m_denominator{ 1 } {}
			rational_number(Integral numerator, Unsigned_Integral denominator)
				: m_numerator{ numerator }, m_denominator{ denominator } {}
			auto& numerator() {
				return m_numerator;
			}
			auto numerator() const {
				return m_numerator;
			}
			auto& denominator() {
				return m_denominator;
			}
			auto denominator() const {
				return m_denominator;
			}
		private:
			Integral m_numerator;
			Unsigned_Integral m_denominator;
		};
		auto operator+(concept_helper::rational_number auto&& lhs,
			concept_helper::rational_number auto&& rhs) {
			auto res = lhs;
			res.numerator() = lhs.numerator() * rhs.denominator() + lhs.denominator() * rhs.numerator();
			res.denominator() = lhs.denominator() * rhs.denominator();
			return res;
		}
		auto operator-(concept_helper::rational_number auto&& lhs,
			concept_helper::rational_number auto&& rhs) {
			auto res = lhs;
			res.numerator() = lhs.numerator() * rhs.denominator() - lhs.denominator() * rhs.numerator();
			res.denominator() = lhs.denominator() * rhs.denominator();
			return res;
		}
		auto operator*(concept_helper::rational_number auto&& lhs,
			concept_helper::rational_number auto&& rhs) {
			auto res = lhs;
			res.numerator() *= rhs.numerator();
			res.denominator() *= rhs.denominator();
			return res;
		}
		auto normalize(concept_helper::rational_number auto&& num) {
			auto res = num;
			auto d = std::gcd(num.denominator(), num.numerator());
			res.numerator() /= d;
			res.denominator() /= d;
			return res;
		}
		auto operator/(concept_helper::rational_number auto&& lhs,
			concept_helper::rational_number auto&& rhs) {
			auto res = lhs;
			res.numerator() *= rhs.denominator();
			res.denominator() *= rhs.numerator();
			return res;
		}
	}
}