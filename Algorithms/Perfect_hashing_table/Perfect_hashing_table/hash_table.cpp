#include "hash_table.h"
#include <utility>
#include <random>
#include <ctime>
#include <iostream>
size_t hash_table::universal_hash_function(size_t a, size_t b, size_t m, double value) {
	if (m == 0 || p == 0) return 0;
	return (size_t(a * value + b) % p) % m;
}
void hash_table::init(size_t hash_table_size, double* arr, size_t array_size) {
	// initialization
	m_size = hash_table_size;
	m_table = new double** [m_size];
	a_for_additional_tables = new size_t[m_size];
	b_for_additional_tables = new size_t[m_size];
	additional_table_sizes = new size_t[m_size];
	size_t best_space = array_size * array_size;
	std::random_device rd;
	std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
	std::mt19937 gen(seed);
	std::uniform_int_distribution<> dis(1, 100);
	// experement_hash_table - simulation of hash table that contains number of collisions + 1 in each slot
	size_t* experement_hash_table = new size_t[m_size];
	// choosing the best hash function - that requires the least space
	for (size_t k = 0; k < 100; k++) {
		size_t a = dis(gen), b = dis(gen), space = 0;
		for (size_t i = 0; i < m_size; i++) {
			experement_hash_table[i] = 0;
		}
		for (size_t i = 0; i < array_size; i++) {
			//std::cout << universal_hash_function(a, b, m_size, arr[i]) << "\n";
			experement_hash_table[universal_hash_function(a, b, m_size, arr[i])]++;
		}
		for (size_t i = 0; i < m_size; i++) {
			space += experement_hash_table[i] * experement_hash_table[i];
		}
		if (space < best_space) {
			best_space = space;
			a_main_table = a;
			b_main_table = b;
		}
	}
	// finding number of collisions + 1 in each slot
	for (size_t i = 0; i < m_size; i++) {
		experement_hash_table[i] = 0;
	}
	for (size_t i = 0; i < array_size; i++) {
		experement_hash_table[universal_hash_function(a_main_table, b_main_table, m_size, arr[i])]++;
	}
	// creating second layer of hash tables in slots where needed (collisions + 1 = experement_hash_table[i] > 1)
	for (size_t i = 0; i < m_size; i++) {
		additional_table_sizes[i] = experement_hash_table[i] * experement_hash_table[i];
		if (experement_hash_table[i] > 0) {
			m_table[i] = new double* [additional_table_sizes[i]];
			for (size_t j = 0; j < additional_table_sizes[i]; j++) {
				m_table[i][j] = nullptr;
			}
			if (experement_hash_table[i] > 1) {
				// creating random universal hash function
				a_for_additional_tables[i] = dis(gen);
				b_for_additional_tables[i] = dis(gen);
			}
			else {
				// hash function that always return 0, so what needed for one element
				a_for_additional_tables[i] = 0;
				b_for_additional_tables[i] = 0;
			}
		}
		else {
			m_table[i] = nullptr;
		}
	}
	for (size_t i = 0; i < array_size; i++) {
		size_t main_index = universal_hash_function(a_main_table, b_main_table, m_size, arr[i]),
			additional_index = universal_hash_function(a_for_additional_tables[main_index], b_for_additional_tables[main_index],
				additional_table_sizes[main_index], arr[i]);
		if (m_table[main_index][additional_index] == nullptr) {
			m_table[main_index][additional_index] = &(arr[i]);
		}
		else {
			bool collisions = true;

			double** copy_of_additional_table = new double* [additional_table_sizes[main_index]];
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
				a_for_additional_tables[main_index] = dis(gen);
				b_for_additional_tables[main_index] = dis(gen);

				// rewrite elements in additional table according to new hash function and checking for collisions
				for (size_t j = 0; j < additional_table_sizes[main_index]; j++) {
					if (copy_of_additional_table[j] != nullptr) {
						size_t index = universal_hash_function(a_for_additional_tables[main_index], b_for_additional_tables[main_index],
							additional_table_sizes[main_index], *(copy_of_additional_table[j]));
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
				size_t index = universal_hash_function(a_for_additional_tables[main_index], b_for_additional_tables[main_index],
					additional_table_sizes[main_index], arr[i]);
				if (m_table[main_index][index] == nullptr) {
					m_table[main_index][index] = &(arr[i]);
				}
				else {
					collisions = true;
				}
			}
			delete[] copy_of_additional_table;
		}
	}
	delete[] experement_hash_table;
}

hash_table::hash_table(size_t hash_table_size, double* arr, size_t array_size) {
	init(hash_table_size, arr, array_size);
}

double hash_table::get_size() {
	return m_size;
}

hash_table::~hash_table() {
	delete[] a_for_additional_tables;
	delete[] b_for_additional_tables;
	delete[] additional_table_sizes;
	for (size_t i = 0; i < m_size; i++) {
		delete[] m_table[i];
	}
	delete[] m_table;
}
void hash_table::visualize(double* arr, size_t array_size, std::ofstream& out) {
	for (size_t i = 0; i < m_size; i++) {
		if (m_table[i] == nullptr) {
			out << "#";
		}
		else {
			for (size_t j = 0; j < additional_table_sizes[i]; j++) {
				if (m_table[i][j] == nullptr) {
					out << "# ";
				}
				else {
					out << *(m_table[i][j]) << " ";
				}
			}
		}
		out << '\n';
	}
}
bool hash_table::contains(double value) {
	size_t main_index = universal_hash_function(a_main_table, b_main_table, m_size, value);
	if (m_table[main_index] == nullptr) {
		return false;
	}
	size_t additional_index = universal_hash_function(a_for_additional_tables[main_index], b_for_additional_tables[main_index],
		additional_table_sizes[main_index], value);
	if (m_table[main_index][additional_index] == nullptr) {
		return false;
	}

	if (abs(value - *(m_table[main_index][additional_index])) < eps)
		return true;
	else
		return false;
}
