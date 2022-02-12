#include "pch.h"
#include <random>
#include <fstream>

#include "../Perfect-hashing-table/hash_table.cpp"

TEST(hash_table_test, random_test) {
	std::random_device rd;
	std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
	std::mt19937 gen(seed);
	std::uniform_int_distribution<> size_dis(1, 10);
	std::uniform_real_distribution<> real_dis(-1000, 1000);
	for (int t = 0; t < 10; t++) {
		size_t n = size_dis(gen), m = size_dis(gen);
		double* arr = new double[n];
		for (size_t i = 0; i < n; i++) {
			arr[i] = real_dis(gen);
		}
		hash_table table(m, arr, n);
		for (size_t i = 0; i < n; i++) {
			EXPECT_TRUE(table.contains(arr[i]));
		}
		for (size_t i = 0; i < n; i++) {
			double value = real_dis(gen);
			EXPECT_EQ(table.contains(value), std::find(arr, arr + n, value) != (arr + n));
		}
		delete[] arr;
	}
	//EXPECT_EQ(1, 1);
}

TEST(hash_table_test, example_test) {
	//EXPECT_EQ(1, 1);
	int n, m, q;
	std::ifstream in("../Perfect-hashing-table/input.txt");
	in >> n >> m >> q;
	double* arr = new double[n];
	for (int i = 0; i < n; i++) {
		in >> arr[i];
	}
	hash_table table(m, arr, n);
	for (int i = 0; i < q; i++) {
		double value;
		in >> value;
		if (i < 10)
			EXPECT_TRUE(table.contains(value));
		else
			EXPECT_FALSE(table.contains(value));
	}
	delete[] arr;
}