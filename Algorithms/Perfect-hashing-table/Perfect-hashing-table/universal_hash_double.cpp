#include "universal_hash_double.h"
universal_hash_double::universal_hash_double() {
	// do noting
}
universal_hash_double::universal_hash_double(unsigned long long i_a0, unsigned long long i_a1, unsigned long long i_a2,
	unsigned long long i_a3, unsigned long long i_b) {
	set(i_a0, i_a1, i_a2, i_a3, i_b);
}
void universal_hash_double::set(unsigned long long i_a0, unsigned long long i_a1, unsigned long long i_a2,
	unsigned long long i_a3, unsigned long long i_b) {
	a0 = i_a0;
	a1 = i_a1;
	a2 = i_a2;
	a3 = i_a3;
	b = i_b;
}
void universal_hash_double::random(std::mt19937& gen, std::uniform_int_distribution<>& dis_a, std::uniform_int_distribution<>& dis_b) {
	a0 = dis_a(gen);
	a1 = dis_a(gen);
	a2 = dis_a(gen);
	a3 = dis_a(gen);
	b = dis_b(gen);
}
size_t universal_hash_double::hash(double value, unsigned long long p, size_t m) {
	// both 0+ and 0- hash to b % p % m
	if (value == 0.0)
		return size_t((b % p) % m);
	unsigned short* pt = (unsigned short*)(&value);
	return size_t(((a0 * pt[0] + a1 * pt[1] + a2 * pt[2] + a3 * pt[3] + b) % p) % m);
}
// copy constructor
universal_hash_double::universal_hash_double(const universal_hash_double& other) {
	a0 = other.a0;
	a1 = other.a1;
	a2 = other.a2;
	a3 = other.a3;
	b = other.b;
}
// copy assignment
universal_hash_double& universal_hash_double::operator=(const universal_hash_double& other) {
	if (this != &other) {
		a0 = other.a0;
		a1 = other.a1;
		a2 = other.a2;
		a3 = other.a3;
		b = other.b;
	}
	return *this;
}