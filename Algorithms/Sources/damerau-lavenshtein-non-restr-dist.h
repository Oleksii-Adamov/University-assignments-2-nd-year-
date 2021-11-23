#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "util.h"
// Damerau–Levenshtein distance (without restrictions)
// working with english non-capital letters a-z
long long damerau_levenshtein_dist(const std::string& s1, const std::string& s2, std::vector<std::string>& edit_sequence, std::vector<std::string>& edited_strings) {
	// for each character in alphabet we store the position of last entry in s1 starting counting from 1; 0 - if no entry
	std::vector<size_t> last_pos_of_letter_in_s1('z' - 'a' + 1, 0);
	size_t s1_size = s1.size(), s2_size = s2.size();
	// dist[i][j] - Damerau–Levenshtein distance for s1 constisted of first i characters, and s2  constisted of first j characters
	std::vector<std::vector<long long>> dist(s1_size + 1, std::vector<long long>(s2_size + 1));
	// last_poses_of_letters_k_f[i][j] - stores values of k and f for (i,j) iteration. k and f explained later
	std::vector<std::vector<std::pair<size_t, size_t>>> last_poses_of_letters_k_f(s1_size + 1, std::vector<std::pair<size_t, size_t>> (s2_size + 1));
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
			last_poses_of_letters_k_f[i][j] = { k, f };
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
	std::string cur_string = s1;
	edited_strings.reserve(dist[s1_size][s2_size] + 1);
	edit_sequence.reserve(dist[s1_size][s2_size]);
	edited_strings.push_back(cur_string);
	size_t i = s1_size, j = s2_size;
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
		size_t k = last_poses_of_letters_k_f[i][j].first, f = last_poses_of_letters_k_f[i][j].second;
		if (k > 0 && f > 0 && dist[k - 1][f - 1] + (i - k - 1) + (j - f - 1) + 1 <= minimum) {
			minimum = dist[k - 1][f - 1] + (i - k - 1) + (j - f - 1) + 1;
			transposition = true;
		}
		if (transposition) {
			if (i - k - 1 > 0) {
				for (size_t pos = i - 1; pos != k; pos--) {
					edit_sequence.push_back("Delete " + std::to_string(pos));
					cur_string.erase(pos - 1, 1);
					edited_strings.push_back(cur_string);
				}
			}
			edit_sequence.push_back("Transpose " + std::to_string(k) + " and " + std::to_string(k + 1));
			std::swap(cur_string[k - 1], cur_string[k]);
			edited_strings.push_back(cur_string);
			if (j - f - 1 > 0) {
				size_t pos_in_s1 = k;
				for (size_t pos_in_s2 = f + 1; pos_in_s2 < j; pos_in_s2++, pos_in_s1++) {
					edit_sequence.push_back("Insert after " + std::to_string(pos_in_s1) + " " + s2[pos_in_s2 - 1]);
					cur_string.insert(pos_in_s1, 1, s2[pos_in_s2 - 1]);
					edited_strings.push_back(cur_string);
				}
			}
			i = k - 1;
			j = f - 1;
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