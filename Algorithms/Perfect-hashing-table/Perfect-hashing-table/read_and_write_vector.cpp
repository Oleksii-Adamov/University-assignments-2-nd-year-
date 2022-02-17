#pragma once
#include "read_and_write_vector.h"

void read_vector(std::vector<double>& dest, std::ifstream& in) {
	char c;
	in >> c;
	if (c != '(') {
		std::cout << "Error: no ( in vector\n";
		exit(1);
	}
	while (true) {
		double value;
		in >> value;
		dest.push_back(value);
		std::cout << value << " ";
		in >> c;
		if (c == ')') break;
	}
	//in >> c;
	std::cout << "\n";
}

void write_vector(const std::vector<double>& src, std::ofstream& out) {
	out << '(';
	for (size_t f = 0; f < src.size() - 1; f++) {
		out << src[f] << ", ";
	}
	out << src[src.size() - 1] << ")";
}

void write_vector(const std::vector<double>& src, std::ostream& out) {
	out << '(';
	for (size_t f = 0; f < src.size() - 1; f++) {
		out << src[f] << ", ";
	}
	out << src[src.size() - 1] << ")";
}