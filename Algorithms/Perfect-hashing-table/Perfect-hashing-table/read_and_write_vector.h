#pragma once
#include <fstream>
#include <vector>
#include <iostream>

void read_vector(std::vector<double>& dest, std::ifstream& in);

void write_vector(const std::vector<double>& src, std::ofstream& out);

void write_vector(const std::vector<double>& src, std::ostream& out);