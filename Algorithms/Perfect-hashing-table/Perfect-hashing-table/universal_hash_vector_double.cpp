#include "universal_hash_vector_double.h"
universal_hash_vector_double::universal_hash_vector_double() {
	// do noting
}
universal_hash_vector_double::universal_hash_vector_double(unsigned long long i_a, unsigned long long i_b) {
	set(i_a, i_b);
}
void universal_hash_vector_double::set(unsigned long long i_a, unsigned long long i_b) {
	a = i_a;
	b = i_b;
}
void universal_hash_vector_double::random(std::mt19937& gen, std::uniform_int_distribution<>& dis_a,
	std::uniform_int_distribution<>& dis_b) {
	a = dis_a(gen);
	b = dis_b(gen);
}
size_t universal_hash_vector_double::hash_int(unsigned long long num, unsigned long long p, size_t m) {
	return size_t(((a * num + b) % p) % m);
}
size_t universal_hash_vector_double::hash(const std::vector<double>& vec, unsigned long long p, size_t m, unsigned long long k) {
	unsigned long long sum = 0, mult = 1;
	size_t vector_size = vec.size();
	for (size_t i = 0; i < vector_size; i++) {
		// interpreting one double as 4 unsigned 16bit integers
		unsigned short* pt = (unsigned short*)(&(vec[i]));
		// both 0+ and 0- counts as 0
		if (!(vec[i] == 0.0)) {
			pt[0] = 0;
		}
		for (size_t j = 0; j < 4; j++) {
			// add 1 so zero vectors hash correctly
			sum += mult * (pt[j] + 1);
			sum %= p;
			mult *= k;
			mult %= p;
		}
	}
	return hash_int(sum, p, m);
}
// copy constructor
universal_hash_vector_double::universal_hash_vector_double(const universal_hash_vector_double& other) {
	a = other.a;
	b = other.b;
}
// copy assignment
universal_hash_vector_double& universal_hash_vector_double::operator=(const universal_hash_vector_double& other) {
	if (this != &other) {
		a = other.a;
		b = other.b;
	}
	return *this;
}