#include <rational_number.hpp>
#include <iostream>

using namespace water::rational_number;

auto& operator<<(std::ostream& out, const concept_helper::rational_number auto& q) {
	if (q.denominator() == 1) {
		return out << q.numerator();
	}
	else {
		return out << "(" << q.numerator() << "/" << q.denominator() << ")";
	}
}

int main() {
	using Q = water::rational_number::rational_number<int32_t,uint32_t>;
	auto a = normalize(Q{10, 20});
	auto b = normalize(Q{ 20, 10 });
	std::cout << a << "+" << b << "=" << normalize(a + b) << std::endl;
	std::cout << a << "-" << b << "=" << normalize(a - b) << std::endl;
	std::cout << a << "*" << b << "=" << normalize(a * b) << std::endl;
	std::cout << a << "/" << b << "=" << normalize(a / b) << std::endl;
	return 0;
}