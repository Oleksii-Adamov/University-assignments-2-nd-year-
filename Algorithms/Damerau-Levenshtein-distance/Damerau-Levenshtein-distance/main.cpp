#include <fstream>
#include <chrono>
#include "damerau-lavenshtein-non-restr-dist.h"
#include "damerau-lavenshtein-restr-algo-dist.h"
int main() { 
	std::ifstream in("damerau-lavenshtein-dist_input.txt");
	std::ofstream out("damerau-lavenshtein-dist_output.txt");
	std::string s1, s2;
	in >> s1 >> s2;
	long long ans;
	std::vector<std::string> edit_sequence, edited_strings;
	auto start = std::chrono::high_resolution_clock::now();
	ans = damerau_levenshtein_dist(s1, s2, edit_sequence, edited_strings);
	auto end = std::chrono::high_resolution_clock::now();
	out << "Damerau–Levenshtein distance (without restrictions):\n";
	out << ans << "\n";
	out << "Damerau–Levenshtein edit sequence(without restrictions):\n";
	for (size_t i = 0; i < edit_sequence.size(); i++) {
		out << edit_sequence[i] << "\n";
	}
	for (size_t i = 0; i < edited_strings.size() - 1; i++) {
		out << edited_strings[i] << "->";
	}
	out << edited_strings[edited_strings.size() - 1] << "\n";
	out << "Has been done for " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 0.001 << " milliseconds\n";
	edit_sequence.clear();
	edited_strings.clear();
	start = std::chrono::high_resolution_clock::now();
	ans = osa_dist(s1, s2, edit_sequence, edited_strings);
	end = std::chrono::high_resolution_clock::now();
	out << "Optimal string alignment distance, or restricted edit distance:\n";
	out << ans << "\n";
	out << "Optimal string alignment distance, or restricted edit sequence:\n";
	for (size_t i = 0; i < edit_sequence.size(); i++) {
		out << edit_sequence[i] << "\n";
	}
	for (size_t i = 0; i < edited_strings.size() - 1; i++) {
		out << edited_strings[i] << "->";
	}
	out << edited_strings[edited_strings.size() - 1] << "\n";
	out << "Has been done for " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 0.001 << " milliseconds\n";
	in.close();
	out.close();
}