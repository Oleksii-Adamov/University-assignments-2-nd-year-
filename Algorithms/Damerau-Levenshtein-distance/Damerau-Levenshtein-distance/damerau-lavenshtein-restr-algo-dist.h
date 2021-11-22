#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "util.h"
// Optimal string alignment distance, or restricted edit distance 
// Optimal string alignment algorithm computes the number of edit operations needed to make the strings equal
// under the condition that no substring is edited more than once
long long osa_dist(const std::string& s1, const std::string& s2) {
	size_t s1_size = s1.size(), s2_size = s2.size();
	// dist[i][j] - Damerau–Levenshtein distance for s1 constisted of first i characters, and s2 constisted of first j characters
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
		for (size_t j = 1; j <= s2_size; j++) {
			dist[i][j] = min3(
				dist[i][j - 1] + 1, // insertion
				dist[i - 1][j] + 1, //deletion
				dist[i - 1][j - 1] + (s1[i - 1] != s2[j - 1]) // substitution
			);
			// if transposition can be done with previous character
			if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
				// transposition
				dist[i][j] = std::min(dist[i][j], dist[i - 2][j - 2] + 1);
			}
		}
	}
	return dist[s1_size][s2_size];
}