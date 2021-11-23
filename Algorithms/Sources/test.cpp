#include "pch.h"
#include "../Damerau-Levenshtein-distance/damerau-lavenshtein-non-restr-dist.h"
#include "../Damerau-Levenshtein-distance/damerau-lavenshtein-restr-algo-dist.h"

TEST(Damerau_Levenshtein_Non_Restricted_Distance, Different) {
	// from wiki
	std::string s1 = "ca", s2 = "abc";
	std::vector<std::string> edit_sequence, edited_strings;
	EXPECT_EQ(damerau_levenshtein_dist(s1, s2, edit_sequence, edited_strings), 2);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// from internet
	s1 = "gifts"; s2 = "profit";
	EXPECT_EQ(damerau_levenshtein_dist(s1, s2, edit_sequence, edited_strings), 5);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// mine
	// substitution
	s1 = "aabc"; s2 = "babc";
	EXPECT_EQ(damerau_levenshtein_dist(s1, s2, edit_sequence, edited_strings), 1);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// substitution and deletion
	s1 = "aabc"; s2 = "bab";
	EXPECT_EQ(damerau_levenshtein_dist(s1, s2, edit_sequence, edited_strings), 2);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// substitution and insert
	s1 = "aab"; s2 = "babc";
	EXPECT_EQ(damerau_levenshtein_dist(s1, s2, edit_sequence, edited_strings), 2);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// substitution and transposition
	s1 = "aabc"; s2 = "bacb";
	EXPECT_EQ(damerau_levenshtein_dist(s1, s2, edit_sequence, edited_strings), 2);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// internal insertion
	s1 = "aaaa"; s2 = "aaaba";
	EXPECT_EQ(damerau_levenshtein_dist(s1, s2, edit_sequence, edited_strings), 1);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// right insertion
	s1 = "aaaa"; s2 = "aaaab";
	EXPECT_EQ(damerau_levenshtein_dist(s1, s2, edit_sequence, edited_strings), 1);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// left insertion
	s1 = "baaa"; s2 = "abaaa";
	EXPECT_EQ(damerau_levenshtein_dist(s1, s2, edit_sequence, edited_strings), 1);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// delete between and transpose
	s1 = "ab"; s2 = "bccca";
	EXPECT_EQ(damerau_levenshtein_dist(s1, s2, edit_sequence, edited_strings), 4);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
}

TEST(Damerau_Levenshtein_Non_Restricted_Distance, Same) {
	std::vector<std::string> edit_sequence, edited_strings;
	std::string s1 = "abc", s2 = "abc";
	EXPECT_EQ(damerau_levenshtein_dist(s1, s2, edit_sequence, edited_strings), 0);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
}

TEST(Damerau_Levenshtein_Non_Restricted_Distance, Empty) {
	std::vector<std::string> edit_sequence, edited_strings;
	std::string s1 = "", s2 = "abc";
	EXPECT_EQ(damerau_levenshtein_dist(s1, s2, edit_sequence, edited_strings), 3);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	EXPECT_EQ(damerau_levenshtein_dist(s2, s1, edit_sequence, edited_strings), 3);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s1);
	EXPECT_EQ(damerau_levenshtein_dist(s1, s1, edit_sequence, edited_strings), 0);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s1);
}

TEST(OSA_Distance, Different) {
	// from wiki
	std::string s1 = "ca", s2 = "abc";
	std::vector<std::string> edit_sequence, edited_strings;
	EXPECT_EQ(osa_dist(s1, s2, edit_sequence, edited_strings), 3);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// from internet
	s1 = "gifts"; s2 = "profit";
	EXPECT_EQ(osa_dist(s1, s2, edit_sequence, edited_strings), 5);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// mine
	// substitution
	s1 = "aabc"; s2 = "babc";
	EXPECT_EQ(osa_dist(s1, s2, edit_sequence, edited_strings), 1);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// substitution and deletion
	s1 = "aabc"; s2 = "bab";
	EXPECT_EQ(osa_dist(s1, s2, edit_sequence, edited_strings), 2);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// substitution and insert
	s1 = "aab"; s2 = "babc";
	EXPECT_EQ(osa_dist(s1, s2, edit_sequence, edited_strings), 2);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// substitution and transposition
	s1 = "aabc"; s2 = "bacb";
	EXPECT_EQ(osa_dist(s1, s2, edit_sequence, edited_strings), 2);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// internal insertion
	s1 = "aaaa"; s2 = "aaaba";
	EXPECT_EQ(osa_dist(s1, s2, edit_sequence, edited_strings), 1);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// right insertion
	s1 = "aaaa"; s2 = "aaaab";
	EXPECT_EQ(osa_dist(s1, s2, edit_sequence, edited_strings), 1);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// left insertion
	s1 = "baaa"; s2 = "abaaa";
	EXPECT_EQ(osa_dist(s1, s2, edit_sequence, edited_strings), 1);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	// more than non-restricted
	s1 = "ab"; s2 = "bccca";
	EXPECT_EQ(osa_dist(s1, s2, edit_sequence, edited_strings), 5);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
}

TEST(OSA_Distance, Same) {
	std::vector<std::string> edit_sequence, edited_strings;
	std::string s1 = "abc", s2 = "abc";
	EXPECT_EQ(osa_dist(s1, s2, edit_sequence, edited_strings), 0);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
}

TEST(OSA_Distance, Empty) {
	std::vector<std::string> edit_sequence, edited_strings;
	std::string s1 = "", s2 = "abc";
	EXPECT_EQ(osa_dist(s1, s2, edit_sequence, edited_strings), 3);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s2);
	EXPECT_EQ(osa_dist(s2, s1, edit_sequence, edited_strings), 3);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s1);
	EXPECT_EQ(osa_dist(s1, s1, edit_sequence, edited_strings), 0);
	EXPECT_EQ(edited_strings[edited_strings.size() - 1], s1);
}
