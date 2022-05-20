#include <fstream>
#include <chrono>
#include <complex>
#include <vector>
#include "optimalBST.h"
int main() {
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	std::size_t n;
	in >> n;
	std::vector<std::complex<double>> keys(n);
	for (std::size_t i = 0; i < n; i++) {
		in >> keys[i];
	}
	std::vector<long long> freq(n);
	for (std::size_t i = 0; i < n; i++) {
		in >> freq[i];
	}
	std::vector<std::size_t> path;
	auto start = std::chrono::high_resolution_clock::now();
	long long cost = optimalBST(freq, path);
	auto end = std::chrono::high_resolution_clock::now();
	out << "cost = " << cost << "\n";
	out << "Pre-order tree traversal: ";
	for (std::size_t i = 0; i < n; i++) {
		out << keys[path[i]] << " ";
	}
	out << "\n";
	out << "Has been done for " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 0.001 << " milliseconds\n";
}