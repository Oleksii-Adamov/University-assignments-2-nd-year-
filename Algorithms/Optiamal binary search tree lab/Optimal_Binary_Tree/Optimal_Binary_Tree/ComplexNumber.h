#pragma once
#include <iostream>
class ComplexNumber {
public:
	int a;
	int b;
	friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& num);
	ComplexNumber(std::string str) {
		std::string a_string;
		bool sign_passe
		for (std::size_t i = 0; i < str.size(); i++) {
			if (a_string)
		}
	}
};

std::ostream& operator<<(std::ostream& os, const ComplexNumber& num) {
	os << num.a;
	if (num.b > 0) os << "+";
	else os << "-";
	os << abs(num.b) << "i";
}