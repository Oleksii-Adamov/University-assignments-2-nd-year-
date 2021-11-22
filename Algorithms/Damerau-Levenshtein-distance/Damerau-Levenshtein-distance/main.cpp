#include <fstream>
#include <chrono>
#include "damerau-lavenshtein-non-restr-dist.h"
#include "damerau-lavenshtein-restr-algo-dist.h"
int main() { 
	std::ifstream in("damerau-lavenshtein-dist_input.txt");
	std::ofstream out("damerau-lavenshtein-dist_output.txt");
	std::string s1, s2;
	in >> s1 >> s2;
	auto start = std::chrono::high_resolution_clock::now();
	long long ans = damerau_levenshtein_dist(s1, s2);
	auto end = std::chrono::high_resolution_clock::now();
	out << "Damerau–Levenshtein distance (without restrictions):\n";
	out << ans << "\n";
	out << "Has been done for " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 0.001 << " milliseconds\n";
	start = std::chrono::high_resolution_clock::now();
	ans = osa_dist(s1, s2);
	end = std::chrono::high_resolution_clock::now();
	out << "Optimal string alignment distance, or restricted edit distance:\n";
	out << ans << "\n";
	out << "Has been done for " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 0.001 << " milliseconds\n";
	in.close();
	out.close();
}