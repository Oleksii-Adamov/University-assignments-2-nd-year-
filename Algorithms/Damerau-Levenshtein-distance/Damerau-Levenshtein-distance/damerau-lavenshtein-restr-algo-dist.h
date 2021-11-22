#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "util.h"
// Optimal string alignment distance, or restricted edit distance 
// Optimal string alignment algorithm computes the number of edit operations needed to make the strings equal
// under the condition that no substring is edited more than once
long long osa_dist(const std::string& s1, const std::string& s2, std::vector<std::string>& edit_sequence, std::vector<std::string>& edited_strings) {
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
	std::string cur_string = s1;
	edited_strings.push_back(cur_string);
	int i = s1_size, j = s2_size;
	while (i > 0 || j > 0) {
		bool insertion = false, deletion = false, substitution = false, transposition = false;
		long long minimum = -1; 
		if (j > 0 && dist[i][j - 1] + 1) {
			minimum = dist[i][j - 1] + 1;
			insertion = true;
		}
		if (i > 0 && (dist[i - 1][j] + 1 < minimum || minimum == -1)) {
			minimum = dist[i - 1][j] + 1;
			deletion = true;
		}
		if (i > 0 && j > 0 && dist[i - 1][j - 1] + (s1[i - 1] != s2[j - 1]) <= minimum) {
			minimum = dist[i - 1][j - 1] + (s1[i - 1] != s2[j - 1]);
			substitution = true;
		}
		if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1] && dist[i - 2][j - 2] + 1 <= minimum) {
			minimum = dist[i - 2][j - 2];
			transposition = true;
		}
		if (transposition) {
			edit_sequence.push_back("Transpose " + std::to_string(i) + " and " + std::to_string(i - 1));
			std::swap(cur_string[i - 1], cur_string[i - 2]);
			edited_strings.push_back(cur_string);
			i -= 2;
			j -= 2;
		}
		else if (substitution) {
			if (s1[i - 1] != s2[j - 1]) {
				edit_sequence.push_back("Substitute at position " + std::to_string(i) + " to " + s2[j - 1]);
				cur_string[i - 1] = s2[j - 1];
				edited_strings.push_back(cur_string);
			}
			i--;
			j--;
		}
		else if (deletion) {
			edit_sequence.push_back("Delete " + std::to_string(i));
			cur_string.erase(i - 1, 1);
			edited_strings.push_back(cur_string);
			i--;
		}
		else {
			edit_sequence.push_back("Insert after " + std::to_string(i) + " " + s2[j - 1]);
			cur_string.insert(i, 1, s2[j - 1]);
			edited_strings.push_back(cur_string);
			j--;
		}
	}
	return dist[s1_size][s2_size];
}