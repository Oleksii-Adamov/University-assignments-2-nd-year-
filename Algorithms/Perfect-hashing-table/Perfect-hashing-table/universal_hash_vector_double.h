#pragma once
#include <random>
class universal_hash_vector_double
{
private:
	unsigned long long a, b;
	size_t hash_int(unsigned long long num, unsigned long long p, size_t m);
public:
	universal_hash_vector_double();
	universal_hash_vector_double(unsigned long long i_a, unsigned long long i_b);
	void set(unsigned long long i_a, unsigned long long i_b);
	void random(std::mt19937& gen, std::uniform_int_distribution<>& dis_a, std::uniform_int_distribution<>& dis_b);
	size_t hash(const std::vector<double>& vec, unsigned long long p, size_t m, unsigned long long k);
	// copy constructor
	universal_hash_vector_double(const universal_hash_vector_double& other);
	// copy assignment
	universal_hash_vector_double& operator=(const universal_hash_vector_double& other);
};

