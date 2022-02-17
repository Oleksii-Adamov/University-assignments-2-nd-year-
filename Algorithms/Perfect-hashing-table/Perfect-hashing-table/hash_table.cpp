#include "hash_table.h"
#include <utility>
#include <random>
#include <ctime>
#include <iostream>
#include "read_and_write_vector.h"
//unsigned short* hash_table::from_double_to_vec4(double value) {
	/*unsigned short* pt = (unsigned short*)(&value);
	unsigned short* ret = new unsigned short[4];
	for (size_t i = 0; i < 4; i++) {
		ret[i] = pt[i];
	}*/
	//unsigned long long* pt = (unsigned long long*)(&value);
	/*std::bitset<64> bits(pt[0]);
	// reverse bits
	for (size_t i = 0; i < 32; i++) {
		bool temp = bits[i];
		bits[i] = bits[63 - i];
		bits[63 - i] = temp;
		//std::swap(bits[i], bits[64 - i]);
	}*/
	//return pt[0]/*bits.to_ullong()*/;
//}
bool hash_table::is_prime(unsigned long long num) {
	if (num % 2 == 0 || num < 2) return false;
	for (unsigned long long i = 3; i * i < num; i+=2) {
		if (num % i == 0) return false;
	}
	return true;
}
unsigned long long hash_table::next_prime(unsigned long long num) {
	unsigned long long initial_step = (num % 2) + 1;
	for (unsigned long long i = num + initial_step; ; i += 2) {
		if (is_prime(i)) return i;
	}
}
void hash_table::init_p(size_t hash_table_size, std::vector<double>* arr, size_t array_size) {
	unsigned long long maxi = hash_table_size;
	for (size_t i = 0; i < array_size; i++) {
		size_t vector_size = arr[i].size();
		for (size_t j = 0; j < vector_size; j++) {
			// interpreting one double as 4 unsigned 16bit integers
			unsigned short* pt = (unsigned short*)(&(arr[i][j]));
			for (size_t j = 0; j < 4; j++) {
				if (maxi < pt[0]) {
					maxi = pt[0];
				}
			}
		}
	}
	// +1 because i hash +1 values, so that zero vectors hash correctly
	p = next_prime(maxi + 1);
}
/*size_t hash_table::universal_hash_function(size_t a, size_t b, size_t m, double value) {
	if (m == 0 || p == 0) return 0;
	//std::cout << "Hashing: " << value << " " << multipler_of_a * value << " " << a * multipler_of_a * value << " "
	//	<< a * multipler_of_a * value + b << " " << long long(abs(a * multipler_of_a * value + b)) << " "
	//	<< long long (abs(a * multipler_of_a * value + b)) % p << " " << (long long(abs(a * multipler_of_a * value + b)) % p) % m << "\n";
	/*char c;
	//std::cin >> c;
	size_t psign = 2;
	if (value < 0) {
		psign = 1;
		value *= (-1);
	}
	return (long long((a + multipler_of_a) * value + psign * psign_mult + b) % p) % m;
	//unsigned long long unsigned_integer = from_double_to_ull(value);
	
	std::cout << p << " " << value << " " << unsigned_integer << " " << (unsigned_integer % p) << " " << ((a * (unsigned_integer % p) + b) % p) % m << "\n";
	return ((a * (unsigned_integer % p) + b) % p) % m;
}*/
void hash_table::init(size_t hash_table_size, std::vector<double>* arr, size_t array_size) {
	// initialization
	init_p(hash_table_size, arr, array_size);
	std::cout << p << "\n";
	table_size = hash_table_size;
	m_table = new std::vector<double>** [table_size];
	additional_tables = new universal_hash_vector_double[table_size];
	//a_for_additional_tables = new size_t[m_size];
	//b_for_additional_tables = new size_t[m_size];
	additional_table_sizes = new size_t[table_size];
	unsigned long long best_space = unsigned long long(array_size) * array_size;
	std::random_device rd;
	std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
	std::mt19937 gen(seed);
	std::uniform_int_distribution<> dis_a(1, p - 1);
	std::uniform_int_distribution<> dis_b(0, p - 1);
	k = dis_a(gen);
	// experement_hash_table - simulation of hash table that contains number of collisions + 1 in each slot
	size_t* experement_hash_table = new size_t[table_size];
	// choosing the best hash function - that requires the least space
	for (size_t t = 0; t < 100; t++) {
		//size_t a = dis(gen), b = dis(gen),space = 0;
		universal_hash_vector_double temp;
		temp.random(gen, dis_a, dis_b);
		unsigned long long space = 0;
		for (size_t i = 0; i < table_size; i++) {
			experement_hash_table[i] = 0;
		}
		for (size_t i = 0; i < array_size; i++) {
			//std::cout << universal_hash_function(a, b, m_size, arr[i]) << "\n";
			//experement_hash_table[universal_hash_function(a, b, m_size, arr[i])]++;
			experement_hash_table[temp.hash(arr[i], p, table_size, k)]++;
		}
		for (size_t i = 0; i < table_size; i++) {
			space += unsigned long long(experement_hash_table[i]) * experement_hash_table[i];
		}
		if (space < best_space) {
			best_space = space;
			main_table = temp;
		}
	}
	// finding number of collisions + 1 in each slot
	for (size_t i = 0; i < table_size; i++) {
		experement_hash_table[i] = 0;
	}
	for (size_t i = 0; i < array_size; i++) {
		//experement_hash_table[universal_hash_function(a_main_table, b_main_table, m_size, arr[i])]++;
		experement_hash_table[main_table.hash(arr[i], p, table_size, k)]++;
	}
	// creating second layer of hash tables in slots where needed (collisions + 1 = experement_hash_table[i] > 1)
	for (size_t i = 0; i < table_size; i++) {
		additional_table_sizes[i] = experement_hash_table[i] * experement_hash_table[i];
		if (experement_hash_table[i] > 0) {
			m_table[i] = new std::vector<double>* [additional_table_sizes[i]];
			for (size_t j = 0; j < additional_table_sizes[i]; j++) {
				m_table[i][j] = nullptr;
			}
			if (experement_hash_table[i] > 1) {
				// creating random universal hash function
				additional_tables[i].random(gen, dis_a, dis_b);
				//a_for_additional_tables[i] = dis(gen);
				//b_for_additional_tables[i] = dis(gen);
			}
			else {
				// hash function that always return 0, so what needed for one element
				additional_tables[i].set(0, 0);
				//a_for_additional_tables[i] = 0;
				//b_for_additional_tables[i] = 0;
			}
		}
		else {
			m_table[i] = nullptr;
		}
	}
	for (size_t i = 0; i < array_size; i++) {
		size_t main_index = main_table.hash(arr[i], p, table_size, k)/*universal_hash_function(a_main_table, b_main_table, m_size, arr[i])*/,
			additional_index = additional_tables[main_index].hash(arr[i], p, additional_table_sizes[main_index], k);/*universal_hash_function(a_for_additional_tables[main_index], b_for_additional_tables[main_index],
				additional_table_sizes[main_index], arr[i]);*/
		if (m_table[main_index][additional_index] == nullptr) {
			m_table[main_index][additional_index] = &(arr[i]);
		}
		else {
			bool collisions = true;

			std::vector<double>** copy_of_additional_table = new std::vector<double>* [additional_table_sizes[main_index]];
			for (size_t j = 0; j < additional_table_sizes[main_index]; j++) {
				copy_of_additional_table[j] = m_table[main_index][j];
				//std::cout << copy_of_additional_table[j];
				//if (copy_of_additional_table[j] != nullptr) std::cout << " " << *copy_of_additional_table[j];
				//std::cout << '\n';
			}

			// probability of picking hash function without collision on first guess is >= 1/2
			while (collisions) {
				collisions = false;
				for (size_t j = 0; j < additional_table_sizes[main_index]; j++) {
					m_table[main_index][j] = nullptr;
				}
				// changing hash function to random hash function
				additional_tables[main_index].random(gen, dis_a, dis_b);
				//a_for_additional_tables[main_index] = dis(gen);
				//b_for_additional_tables[main_index] = dis(gen);
				// rewrite elements in additional table according to new hash function and checking for collisions
				for (size_t j = 0; j < additional_table_sizes[main_index]; j++) {
					if (copy_of_additional_table[j] != nullptr) {
						size_t index = additional_tables[main_index].hash(*(copy_of_additional_table[j]), p,
							additional_table_sizes[main_index], k);/*universal_hash_function(a_for_additional_tables[main_index],
							b_for_additional_tables[main_index],
							additional_table_sizes[main_index], *(copy_of_additional_table[j]));*/
						if (m_table[main_index][index] == nullptr) {
							m_table[main_index][index] = copy_of_additional_table[j];
						}
						else {
							collisions = true;
							break;
						}
					}
				}
				// trying to write &arr[i] in additional hash table
				//size_t index = universal_hash_function(a_for_additional_tables[main_index],
				//	b_for_additional_tables[main_index], additional_table_sizes[main_index], arr[i]);
				size_t index = additional_tables[main_index].hash(arr[i], p, additional_table_sizes[main_index], k);
				if (m_table[main_index][index] == nullptr) {
					m_table[main_index][index] = &(arr[i]);
				}
				else {
					/*std::cout << arr[i] << " " << *(m_table[main_index][index]) << "\n"; /*<<
						universal_hash_function(a_for_additional_tables[main_index],
						b_for_additional_tables[main_index], additional_table_sizes[main_index], arr[i]) << " "*/
						/*<< universal_hash_function(a_for_additional_tables[main_index], b_for_additional_tables[main_index],
							additional_table_sizes[main_index], *(m_table[main_index][index])) << " "*/
						//<< a_for_additional_tables[main_index] << " " << b_for_additional_tables[main_index] << "\n";
					collisions = true;
				}
			}
			delete[] copy_of_additional_table;
		}
	}
	delete[] experement_hash_table;
}

hash_table::hash_table(size_t hash_table_size, std::vector<double>* arr, size_t array_size) {
	init(hash_table_size, arr, array_size);
}

double hash_table::get_size() {
	return table_size;
}

hash_table::~hash_table() {
	//delete[] a_for_additional_tables;
	//delete[] b_for_additional_tables;
	delete[] additional_tables;
	delete[] additional_table_sizes;
	for (size_t i = 0; i < table_size; i++) {
		delete[] m_table[i];
	}
	delete[] m_table;
}
void hash_table::visualize(size_t array_size, std::ofstream& out) {
	for (size_t i = 0; i < table_size; i++) {
		if (m_table[i] == nullptr) {
			out << "#";
		}
		else {
			for (size_t j = 0; j < additional_table_sizes[i]; j++) {
				if (m_table[i][j] == nullptr) {
					out << "# ";
				}
				else {
					/*out << '(';
					for (size_t f = 0; f < (*(m_table[i][j])).size() - 1; f++) {
						out << (*(m_table[i][j]))[f] << ", ";
					}
					out << (*(m_table[i][j]))[(*(m_table[i][j])).size() - 1] << ")";*/
					
					//out << *(m_table[i][j]) << " ";
					write_vector(*(m_table[i][j]), out);
					out << " ";
				}
			}
		}
		out << '\n';
	}
}
bool hash_table::contains(std::vector<double>& value) {
	size_t main_index = main_table.hash(value, p, table_size, k);
		/*universal_hash_function(a_main_table, b_main_table, m_size, value);*/
	if (m_table[main_index] == nullptr) {
		return false;
	}
	size_t additional_index = additional_tables[main_index].hash(value, p, additional_table_sizes[main_index], k);
		/*universal_hash_function(a_for_additional_tables[main_index], b_for_additional_tables[main_index],
		additional_table_sizes[main_index], value);*/
	if (m_table[main_index][additional_index] == nullptr) {
		return false;
	}
	for (size_t i = 0; i < (*(m_table[main_index][additional_index])).size(); i++) {
		if (abs(value[i] - (*(m_table[main_index][additional_index]))[i]) > eps)
			return false;
	}
	return true;
}