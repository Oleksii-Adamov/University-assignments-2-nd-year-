#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "util.h"
// Damerau–Levenshtein distance (without restrictions)
// working with english non-capital letters a-z
long long damerau_levenshtein_dist(const std::string& s1, const std::string& s2) {
	// for each character in alphabet we store the position of last entry in s1 starting counting from 1; 0 - if no entry
	std::vector<size_t> last_pos_of_letter_in_s1('z' - 'a' + 1, 0);
	size_t s1_size = s1.size(), s2_size = s2.size();
	// dist[i][j] - Damerau–Levenshtein distance for s1 constisted of first i characters, and s2  constisted of first j characters
	std::vector<std::vector<long long>> dist(s1_size + 1, std::vector<long long>(s2_size + 1));
	// if s2 is empty we need to perform i deletions
	for (size_t i = 0; i <= s1_size; i++) {
		dist[i][0] = i;
	}
	// if s1 is empty we need to perform j insertions
	for (size_t j = 0; j <= s2_size; j++) {
		dist[0][j] = j;
	}
	for (size_t i = 1; i <= s1_size; i++) {
		// the position of last entry of s1[i-1] in s2 starting counting from 1; 0 - if no entry
		size_t last_pos_of_letter_in_s2 = 0;
		for (size_t j = 1; j <= s2_size; j++) {
			// declaring k and f for convenience
			size_t k = last_pos_of_letter_in_s1[s2[j - 1] - 'a'], f = last_pos_of_letter_in_s2;
			dist[i][j] = min3(
				dist[i][j - 1] + 1, // insertion
				dist[i - 1][j] + 1, //deletion
				dist[i - 1][j - 1] + (s1[i - 1] != s2[j - 1]) // substitution
			);
			// if there are enries
			if (k > 0 && f > 0) {
				// delete i-k-1 characters, transpose, insert j-f-1 characters
				dist[i][j] = std::min(dist[i][j], dist[k - 1][f - 1] + (i - k - 1) + (j - f - 1) + 1);
			}
			if (s1[i - 1] == s2[j - 1]) {
				last_pos_of_letter_in_s2 = j;
			}
		}
		last_pos_of_letter_in_s1[s1[i - 1] - 'a'] = i;
	}
	return dist[s1_size][s2_size];
}