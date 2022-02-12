#pragma once
#include <fstream>
const double eps = 1e-9;
class hash_table {
private:
	double*** m_table;
	size_t m_size;
	int a_main_table, b_main_table;
	size_t* a_for_additional_tables, * b_for_additional_tables, * additional_table_sizes;
	size_t universal_hash_function(size_t a, size_t b, size_t m, double value);
	size_t p;
	long long next_prime_after_num_by_multiplier(size_t num);
	bool is_prime(long long num);
public:
	void init(size_t hash_table_size, double* arr, size_t array_size);
	hash_table(size_t hash_table_size, double* arr, size_t array_size);
	double get_size();
	~hash_table();
	void visualize(double* arr, size_t array_size, std::ofstream& out);
	bool contains(double value);
};