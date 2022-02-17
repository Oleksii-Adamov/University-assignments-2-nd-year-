#pragma once
#include <fstream>
#include "universal_hash_double.h"
const double eps = 1e-9;
class hash_table {
private:
	double*** m_table;
	size_t table_size;
	//int a_main_table, b_main_table;
	//size_t* a_for_additional_tables, * b_for_additional_tables, * additional_table_sizes, * psign_mult_for_additional_tables;
	universal_hash_double main_table;
	universal_hash_double* additional_tables;
	size_t* additional_table_sizes;
	//size_t universal_hash_function(size_t a, size_t b, size_t m, double value);
	unsigned long long p;
	//unsigned long long from_double_to_ull(double value);
	unsigned long long next_prime(unsigned long long num);
	// return the lesser prime number that is > num
	bool is_prime(unsigned long long num);
	void init_p(size_t hash_table_size, double* arr, size_t array_size);
public:
	void init(size_t hash_table_size, double* arr, size_t array_size);
	hash_table(size_t hash_table_size, double* arr, size_t array_size);
	double get_size();
	~hash_table();
	void visualize(double* arr, size_t array_size, std::ofstream& out);
	bool contains(double value);
};