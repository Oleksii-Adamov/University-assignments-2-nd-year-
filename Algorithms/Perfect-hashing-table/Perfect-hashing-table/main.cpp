#include<fstream>
#include"hash_table.h"
#include <random>
#include <ctime>
#include <iostream>
int main() {
	int n, m, q;
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	in >> n >> m >> q;
	double* arr = new double[n];
	for (int i = 0; i < n; i++) {
		in >> arr[i];
		/*for (size_t j = 0; j < i; j++) {
			if (abs(1e9 * arr[i] - 1e9 * arr[j]) < 1) {
				std::cout << "Repeat " << arr[i] << " " << arr[j] << "\n";
			}
		}*/
	}
	hash_table table(m, arr, n);
	table.visualize(arr, n, out);
	for (int i = 0; i < q; i++) {
		double value;
		in >> value;
		if (table.contains(value)) {
			out << "Array/Hash table contains " << value << "\n";
		}
		else {
			out << "Array/Hash table DOESN'T contain " << value << "\n";
		}
	}
	/*
	std::random_device rd;
	std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
	std::mt19937 gen(seed);
	std::uniform_int_distribution<> size_dis(1, 1000);
	std::uniform_real_distribution<> real_dis(0, 1000);
	for (int t = 0; t < 1000; t++) {
		n = size_dis(gen);
		std::cout << n << "\n";
		m = size_dis(gen);
		double* arr = new double[n];
		for (size_t i = 0; i < n; i++) {
			bool repeating_element = true;
			while (repeating_element) {
				repeating_element = false;
				arr[i] = real_dis(gen);
				for (size_t j = 0; j < i; j++) {
					if (abs(arr[i] - arr[j]) < eps) {
						repeating_element = true;
						break;
					}
				}
			}
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
		hash_table table(m, arr, n);
		std::cout << "Built\n";
		bool stop = false;
		for (size_t i = 0; i < n; i++) {
			if (!table.contains(arr[i])) {
				std::cout << "Doesn't contain arr[i]\n";
				stop = true;
				break;
			}
		}
		for (size_t i = 0; i < n; i++) {
			double value = real_dis(gen);
			if (!(table.contains(value) == (std::find(arr, arr + n, value) != (arr + n)))) {
				std::cout << "Doesn't match random\n";
				stop = true;
				break;
			}
		}
		delete[] arr;
		if (stop) break;
		std::cout << "Done\n\n";
	}*/
}