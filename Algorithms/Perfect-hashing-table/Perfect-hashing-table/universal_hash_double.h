#pragma once
#include <random>
class universal_hash_double
{
private:
	unsigned long long a0, a1, a2, a3, b;
public:
	universal_hash_double();
	universal_hash_double(unsigned long long i_a0, unsigned long long i_a1, unsigned long long i_a2, unsigned long long i_a3, unsigned long long i_b);
	void set(unsigned long long i_a0, unsigned long long i_a1, unsigned long long i_a2, unsigned long long i_a3, unsigned long long i_b);
	void random(std::mt19937& gen, std::uniform_int_distribution<>& dis_a, std::uniform_int_distribution<>& dis_b);
	size_t hash(double value, unsigned long long p, size_t m);
	// copy constructor
	universal_hash_double(const universal_hash_double& other);
	// copy assignment
	universal_hash_double& operator=(const universal_hash_double& other);
};

