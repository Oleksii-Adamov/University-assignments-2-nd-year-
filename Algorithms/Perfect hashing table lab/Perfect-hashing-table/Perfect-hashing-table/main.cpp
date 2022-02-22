#include<fstream>
#include"hash_table.h"
#include <random>
#include <ctime>
#include <iostream>
#include "read_and_write_vector.h"
int main() {
	/*{
		size_t n, m, q;
		std::ifstream in("input.txt");
		std::ofstream out("output.txt");
		in >> n >> m >> q;
		std::vector<double>* arr = new std::vector<double>[n];
		for (size_t i = 0; i < n; i++) {
			read_vector(arr[i], in);
		}
		hash_table table(m, arr, n);
		table.visualize(n, out, arr);
		for (size_t i = 0; i < q; i++) {
			std::vector<double> value;
			read_vector(value, in);
			if (table.contains(value, arr)) {
				out << "Array/Hash table contains ";
			}
			else {
				out << "Array/Hash table DOESN'T contain ";
			}
			write_vector(value, out);
			out << "\n";
		}
		table.print_info_about_value(arr[0], arr, out);
		delete[] arr;
	}*/
	{
		std::random_device rd;
		std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
		std::mt19937 gen(seed);
		std::uniform_int_distribution<> size_dis(1, 100);
		std::uniform_real_distribution<> real_dis(0, 1000);
		for (int t = 0; t < 100; t++) {
			size_t n = size_dis(gen);
			size_t m = size_dis(gen);
			std::cout << "\n" << n << " " << m << " " << "\n";
			std::vector<double>* arr = new std::vector<double>[n];
			for (size_t i = 0; i < n; i++) {
				bool repeating_element = true;
				int count = 0;
				while (repeating_element) {
					count++;
					if (count > 1000) {
						std::cout << "Cycle repeating element\n";
						break;
					}
					size_t size = size_dis(gen);
					for (size_t j = 0; j < size; j++) {
						arr[i].push_back(real_dis(gen));
					}
					if (i == 0) repeating_element = false;
					for (size_t j = 0; j < i; j++) {
						if (arr[j].size() != arr[i].size()) {
							repeating_element = false;
							continue;
						}
						for (size_t k = 0; k < arr[j].size(); k++) {
							if (abs(arr[i][k] - arr[j][k]) > eps) {
								repeating_element = false;
								break;
							}
						}
					}
				}
				//std::cout << arr[i] << " ";
			//	write_vector(arr[i], std::cout);
				//std::cout << " ";
			}
			//std::cout << "\n";
			hash_table table(m, arr, n);
			//std::cout << "Built\n";
			bool stop = false;
			for (size_t i = 0; i < n; i++) {
				if (!table.contains(arr[i], arr)) {
					std::cout << "Doesn't contain arr[i]\n";
					stop = true;
					break;
				}
			}
			for (size_t i = 0; i < n; i++) {
				std::vector<double> vec;
				size_t size = size_dis(gen);
				for (size_t j = 0; j < size; j++) {
					vec.push_back(real_dis(gen));
				}
				bool contains = false;
				for (size_t j = 0; j < i; j++) {
					if (arr[j].size() == vec.size()) {
						bool all_equal = true;
						for (size_t k = 0; k < vec.size(); k++) {
							if (abs(arr[i][k] - arr[j][k]) > eps) {
								all_equal = false;
								break;
							}
						}
						if (all_equal) contains = true;
					}
				}
				if (!(table.contains(vec, arr) == contains)) {
					std::cout << "Doesn't match random\n";
					stop = true;
					break;
				}
			}
			delete[] arr;
			if (stop) break;
			//std::cout << "Done\n\n";
		}
	}
}