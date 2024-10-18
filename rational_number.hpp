#pragma once

#include <concepts>
#include <numeric>
#include <type_traits>
#include <iostream>
#include <iomanip>

namespace water {
	namespace rational_number {
		template<class T>
		T to_number(std::string str) = delete;
		template<>
		inline int32_t to_number<int32_t>(std::string str) {
			char* end_p;
			return strtol(str.c_str(), &end_p, 10);
		}
		inline int32_t pow(int32_t d, int32_t n) {
			int32_t res = 1;
			while (n-- > 0) {
				res *= d;
			}
			return res;
		}

		namespace concept_helper {
			template<class Rational_Number>
			concept rational_number = requires (Rational_Number rational_number) {
				rational_number.numerator();
				rational_number.denominator();
			};
		}
		template<std::integral Numerator, std::integral Denominator>
		class rational_number {
		public:
			rational_number() : m_numerator{ 0 }, m_denominator{ 1 } {}
			rational_number(Numerator n) : m_numerator{ n }, m_denominator{ 1 } {}
			rational_number(Numerator numerator, Denominator denominator)
				: m_numerator{ numerator }, m_denominator{ denominator } 
            {
                Denominator gcd = std::gcd(numerator, denominator);
                m_numerator /= Numerator{gcd};
                m_denominator /= gcd;
            }
            rational_number(std::floating_point auto f)
                : rational_number{static_cast<Numerator>(f*1024), 1024}
            {
            }
			static rational_number from_string(const std::string& str) {
				auto dot_iter = std::ranges::find(str, '.');
				std::string_view n_str{ str.begin(), dot_iter};
				auto n = to_number<Numerator>(std::string{ n_str });
				if (dot_iter != str.end()) {
					auto d = to_number<Numerator>(std::string{ dot_iter + 1, str.end() });
					auto count = str.end() - dot_iter - 1;
					return rational_number{ n } + rational_number{ d, pow(Denominator{10},count) };
				}
				return rational_number{ n };
			}
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
			Numerator m_numerator;
			Denominator m_denominator;
		};

		inline auto& operator<<(std::ostream& out, const water::rational_number::concept_helper::rational_number auto& q) {
			if (q.denominator() == 1) {
				return out << q.numerator();
			}
			else {
				return out << "(" << q.numerator() << "/" << q.denominator() << ")";
			}
		}
		inline auto normalize(concept_helper::rational_number auto&& num) {
			auto res = num;
			using Numerator = std::remove_cvref_t<decltype(num.numerator())>;
			Numerator d = std::gcd(num.denominator(), num.numerator());
			res.numerator() /= d;
			res.denominator() /= d;
			return res;
		}
		inline auto operator+(concept_helper::rational_number auto&& lhs,
			concept_helper::rational_number auto&& rhs) {
			auto res = lhs;
			res.numerator() = lhs.numerator() * rhs.denominator() + lhs.denominator() * rhs.numerator();
			res.denominator() = lhs.denominator() * rhs.denominator();
			return normalize(res);
		}
		inline auto operator+(concept_helper::rational_number auto&& lhs,
			std::integral auto rhs) {
			auto res = lhs;
			res.numerator() = lhs.numerator() + lhs.denominator() * rhs;
			res.denominator() = lhs.denominator();
			return normalize(res);
		}
        inline auto& operator+=(concept_helper::rational_number auto& lhs,
                concept_helper::rational_number auto&& rhs) {
            lhs = lhs + rhs;
            return lhs;
        }
		inline auto operator-(concept_helper::rational_number auto&& lhs,
			concept_helper::rational_number auto&& rhs) {
			auto res = lhs;
			using Numerator = std::remove_cvref_t<decltype(lhs.numerator())>;
			res.numerator() = lhs.numerator() * static_cast<Numerator>(rhs.denominator()) - static_cast<Numerator>(lhs.denominator()) * rhs.numerator();
			res.denominator() = lhs.denominator() * rhs.denominator();
			return normalize(res);
		}
		inline auto operator*(concept_helper::rational_number auto&& lhs,
			concept_helper::rational_number auto&& rhs) {
			auto res = lhs;
			res.numerator() *= rhs.numerator();
			res.denominator() *= rhs.denominator();
			return normalize(res);
		}
		inline auto operator*(concept_helper::rational_number auto&& lhs,
			std::integral auto rhs) {
			auto res = lhs;
			res.numerator() *= rhs;
			return normalize(res);
		}
		inline auto operator/(concept_helper::rational_number auto&& lhs,
			concept_helper::rational_number auto&& rhs) {
			auto res = lhs;
			using Numerator = std::remove_cvref_t<decltype(lhs.numerator())>;
			res.numerator() *= static_cast<Numerator>(rhs.denominator());
			if (rhs.numerator() < 0) {
				res.numerator() = - res.numerator();
			}
			res.denominator() *= std::abs(rhs.numerator());
			return normalize(res);
		}
		inline auto operator==(concept_helper::rational_number auto&& lhs,
			concept_helper::rational_number auto&& rhs) {
			return lhs.numerator() * rhs.denominator() == rhs.numerator() * lhs.denominator();
		}
		inline auto operator==(concept_helper::rational_number auto&& lhs, std::integral auto&& rhs) {
			return lhs.numerator() == rhs * lhs.denominator();
		}
		inline auto operator/(std::integral auto&& lhs, concept_helper::rational_number auto&& rhs) {
			std::remove_cvref_t<decltype(rhs)> res{};
			res.numerator() = lhs*rhs.denominator();
			if (rhs.numerator() < 0) {
				res.numerator() = -res.numerator();
			}
			res.denominator() = std::abs(rhs.numerator());
			return normalize(res);
		}
		inline auto& operator*=(concept_helper::rational_number auto&& lhs, concept_helper::rational_number auto&& rhs) {
			lhs.numerator() *= rhs.numerator();
			lhs.denominator() *= rhs.denominator();
			lhs = normalize(lhs);
			return lhs;
		}
		inline auto& operator-=(concept_helper::rational_number auto&& lhs, concept_helper::rational_number auto&& rhs) {
			lhs = lhs - rhs;
			lhs = normalize(lhs);
			return lhs;
		}
	}
}
