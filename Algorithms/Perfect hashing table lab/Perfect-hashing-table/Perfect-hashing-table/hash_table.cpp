#include "hash_table.h"
#include <utility>
#include <random>
#include <ctime>
#include <iostream>
#include "read_and_write_vector.h"

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

void hash_table::init(size_t hash_table_size, std::vector<double>* arr, size_t array_size) {
	// initialization
	init_p(hash_table_size, arr, array_size);
	table_size = hash_table_size;
	m_table = new int* [table_size];
	additional_tables = new universal_hash_vector_double[table_size];
	additional_table_sizes = new size_t[table_size];
	unsigned long long best_space = unsigned long long(array_size) * array_size;
	std::random_device rd;
	std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
	std::mt19937 gen(seed);
	std::uniform_int_distribution<> dis_a(1, p - 1/*9*/);
	std::uniform_int_distribution<> dis_b(0, p - 1/*9*/);
	std::uniform_int_distribution<> dis_k(2, p - 1/*9*/);
	// experement_hash_table - simulation of hash table that contains number of collisions + 1 in each slot
	size_t* experement_hash_table = new size_t[table_size];
	// choosing the best hash function - that requires the least space
	for (size_t t = 0; t < 100; t++) {
		universal_hash_vector_double temp;
		temp.random(gen, dis_a, dis_b, dis_k);
		unsigned long long space = 0;
		for (size_t i = 0; i < table_size; i++) {
			experement_hash_table[i] = 0;
		}
		for (size_t i = 0; i < array_size; i++) {
			experement_hash_table[temp.hash(arr[i], p, table_size)]++;
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
		experement_hash_table[main_table.hash(arr[i], p, table_size)]++;
	}
	// creating second layer of hash tables in slots where needed (collisions + 1 = experement_hash_table[i] > 1)
	for (size_t i = 0; i < table_size; i++) {
		additional_table_sizes[i] = experement_hash_table[i] * experement_hash_table[i];
		if (experement_hash_table[i] > 0) {
			m_table[i] = new int[additional_table_sizes[i]];
			for (size_t j = 0; j < additional_table_sizes[i]; j++) {
				m_table[i][j] = -1;
			}
			if (experement_hash_table[i] > 1) {
				// creating random universal hash function
				additional_tables[i].random(gen, dis_a, dis_b, dis_k);
			}
			else {
				// hash function that always return 0, so what needed for one element
				additional_tables[i].set(0, 0, 0);
			}
		}
		else {
			m_table[i] = nullptr;
		}
	}
	for (size_t i = 0; i < array_size; i++) {
		size_t main_index = main_table.hash(arr[i], p, table_size),
			additional_index = additional_tables[main_index].hash(arr[i], p, additional_table_sizes[main_index]);
		unsigned long long count = 0;
		if (m_table[main_index][additional_index] == -1) {
			m_table[main_index][additional_index] = /*&(arr[i])*/i;
		}
		else {
			bool collisions = true;

			int* copy_of_additional_table = new int[additional_table_sizes[main_index]];
			for (size_t j = 0; j < additional_table_sizes[main_index]; j++) {
				copy_of_additional_table[j] = m_table[main_index][j];
			}
			
			// probability of picking hash function without collision on first guess is >= 1/2
			while (collisions) {
				count++;
				collisions = false;
				for (size_t j = 0; j < additional_table_sizes[main_index]; j++) {
					m_table[main_index][j] = -1;
				}
				// changing hash function to random hash function
				additional_tables[main_index].random(gen, dis_a, dis_b, dis_k);

				// rewrite elements in additional table according to new hash function and checking for collisions
				for (size_t j = 0; j < additional_table_sizes[main_index]; j++) {
					if (copy_of_additional_table[j] != -1) {
						size_t index = additional_tables[main_index].hash(arr[copy_of_additional_table[j]], p,
							additional_table_sizes[main_index]);
						if (m_table[main_index][index] == -1) {
							m_table[main_index][index] = copy_of_additional_table[j];
						}
						else {
							collisions = true;
							break;
						}
					}
				}
				// trying to write &arr[i] in additional hash table
				size_t index = additional_tables[main_index].hash(arr[i], p, additional_table_sizes[main_index]);
				if (m_table[main_index][index] == -1) {
					m_table[main_index][index] = i;
				}
				else {
					collisions = true;
				}
			}
			delete[] copy_of_additional_table;
		}
		std::cout << count << " ";
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
	delete[] additional_tables;
	delete[] additional_table_sizes;
	for (size_t i = 0; i < table_size; i++) {
		delete[] m_table[i];
	}
	delete[] m_table;
}
void hash_table::visualize(size_t array_size, std::ofstream& out, std::vector<double>* arr) {
	for (size_t i = 0; i < table_size; i++) {
		if (m_table[i] == nullptr) {
			out << "#";
		}
		else {
			for (size_t j = 0; j < additional_table_sizes[i]; j++) {
				if (m_table[i][j] == -1) {
					out << "# ";
				}
				else {
					write_vector(arr[m_table[i][j]], out);
					out << " ";
				}
			}
		}
		out << '\n';
	}
}
bool hash_table::contains(std::vector<double>& value, std::vector<double>* arr) {
	size_t main_index = main_table.hash(value, p, table_size);
	if (m_table[main_index] == nullptr) {
		return false;
	}
	size_t additional_index = additional_tables[main_index].hash(value, p, additional_table_sizes[main_index]);
	if (m_table[main_index][additional_index] == -1) {
		return false;
	}
	for (size_t i = 0; i < arr[m_table[main_index][additional_index]].size(); i++) {
		if (abs(value[i] - arr[m_table[main_index][additional_index]][i]) > eps)
			return false;
	}
	return true;
}

void hash_table::print_info_about_value(std::vector<double>& value, std::vector<double>* arr, std::ofstream& out) {
	size_t main_index = main_table.hash(value, p, table_size);
	write_vector(value, out);
	if (m_table[main_index] == nullptr) {
		out << " not in hash table\n";
	}
	size_t additional_index = additional_tables[main_index].hash(value, p, additional_table_sizes[main_index]);
	if (m_table[main_index][additional_index] == -1) {
		out << " not in hash table\n";
	}
	for (size_t i = 0; i < arr[m_table[main_index][additional_index]].size(); i++) {
		if (abs(value[i] - arr[m_table[main_index][additional_index]][i]) > eps)
			out << " not in hash table\n";
	}
	out << " in hash table:\n";
	out << "p = " << p << "\n";
	out << "a = " << main_table.a << "\n";
	out << "b = " << main_table.b << "\n";
	out << "k = " << main_table.k << "\n";
	out << "sum = (";
	unsigned long long sum = 0, mult = 1;
	size_t vector_size = value.size();
	for (size_t i = 0; i < vector_size; i++) {
		// interpreting one double as 4 unsigned 16bit integers
		unsigned short* pt = (unsigned short*)(&(value[i]));
		// both 0+ and 0- counts as 0
		if (value[i] == 0.0) {
			pt[0] = 0;
		}
		for (size_t j = 0; j < 4; j++) {
			// add 1 so zero vectors hash correctly
			sum += mult * (unsigned long long(pt[j]) + 1);
			if (i < vector_size - 1 || j < 3)
				out << mult << "*" << (unsigned long long(pt[j]) + 1) << " + ";
			else
				out << mult << "*" << (unsigned long long(pt[j]) + 1) << ") mod " << p;
			sum %= p;
			mult *= main_table.k;
			mult %= p;
		}
	}
	out << " = " << sum << "\n";
	out << "j = ((" << main_table.a << "*" << sum << " + " << main_table.b << ") mod " << p << ") mod " << table_size << " = ";
	out << main_table.hash_int(sum, p, table_size) << "\n";
	if (main_index != main_table.hash_int(sum, p, table_size)) {
		out << "ALERT main_index\n";
		return;
	}
	out << "a_j = " << additional_tables[main_index].a << "\n";
	out << "b_j = " << additional_tables[main_index].b << "\n";
	out << "k_j = " << additional_tables[main_index].k << "\n";
	out << "size = " << additional_table_sizes[main_index] << "\n";
	out << "sum = (";
	sum = 0; mult = 1;
	for (size_t i = 0; i < vector_size; i++) {
		// interpreting one double as 4 unsigned 16bit integers
		unsigned short* pt = (unsigned short*)(&(value[i]));
		// both 0+ and 0- counts as 0
		if (value[i] == 0.0) {
			pt[0] = 0;
		}
		for (size_t j = 0; j < 4; j++) {
			// add 1 so zero vectors hash correctly
			sum += mult * (unsigned long long(pt[j]) + 1);
			if (i < vector_size - 1 || j < 3)
				out << mult << "*" << (unsigned long long(pt[j]) + 1) << " + ";
			else
				out << mult << "*" << (unsigned long long(pt[j]) + 1) << ") mod " << p;
			sum %= p;
			mult *= additional_tables[main_index].k;
			mult %= p;
		}
	}
	out << " = " << sum << "\n";
	out << "f = ((" << additional_tables[main_index].a << "*" << sum << " + " << additional_tables[main_index].b << ") mod "
		<< p << ") mod " << additional_table_sizes[main_index] << " = ";
	out << additional_tables[main_index].hash_int(sum, p, additional_table_sizes[main_index]) << "\n";
	if (additional_index != additional_tables[main_index].hash_int(sum, p, additional_table_sizes[main_index])) {
		out << "ALERT additional_index\n";
		return;
	}
	out << "table[j][f] = " << m_table[main_index][additional_index] << "\n";
}