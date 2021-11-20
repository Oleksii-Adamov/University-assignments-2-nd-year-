#include <fstream>
#include <chrono>
#include "damerau-lavenshtein-non-restr-dist.h"
int main() { 
	std::ifstream in("damerau-lavenshtein-non-restr-dist_input.txt");
	std::ofstream out("damerau-lavenshtein-non-restr-dist_output.txt");
	std::string s1, s2;
	in >> s1 >> s2;
	auto start = std::chrono::high_resolution_clock::now();
	long long ans = damerau_levenshtein_non_restr_dist(s1, s2);
	auto end = std::chrono::high_resolution_clock::now();
	out << ans << "\n";
	out << "Has been done for " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 0.001 << " milliseconds\n";
	in.close();
	out.close();
}