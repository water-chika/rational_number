#include <rational_number.hpp>
#include <iostream>

using namespace water::rational_number;


int main() {
	using Q = water::rational_number::rational_number<int32_t,uint32_t>;
	auto a = Q{10, 20};
	auto b = Q{ 20, 10 };
	std::cout << a << "+" << b << "=" << normalize(a + b) << std::endl;
	std::cout << a << "-" << b << "=" << normalize(a - b) << std::endl;
	std::cout << a << "*" << b << "=" << normalize(a * b) << std::endl;
	std::cout << a << "/" << b << "=" << normalize(a / b) << std::endl;
	return 0;
}
