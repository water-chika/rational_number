#include <rational_number.hpp>
#include <iostream>

using namespace water::rational_number;

auto& operator<<(std::ostream& out, const concept_helper::rational_number auto& q) {
	return out << " (" << q.numerator() << "/" << q.denominator() << ") ";
}

int main() {
	using Q = water::rational_number::rational_number<int>;
	auto a = Q{10, 20};
	auto b = Q{ 20, 10 };
	std::cout << a << "+" << b << "=" << a + b << std::endl;
	return 0;
}