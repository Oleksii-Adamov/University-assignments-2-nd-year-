#include "pch.h"
#include "../Damerau-Levenshtein-distance/damerau-lavenshtein-non-restr-dist.h"
#include <iostream>

TEST(Damerau_Levenshtein_Non_Restricted_Distance, Different) {
	// from wiki
	std::string s1 = "ca", s2 = "abc";
	EXPECT_EQ(damerau_levenshtein_non_restr_dist(s1, s2), 2);
	// from internet
	s1 = "gifts"; s2 = "profit";
	EXPECT_EQ(damerau_levenshtein_non_restr_dist(s1, s2), 5);
	// mine
	// substitution
	s1 = "aabc"; s2 = "babc";
	EXPECT_EQ(damerau_levenshtein_non_restr_dist(s1, s2), 1);
	// substitution and deletion
	s1 = "aabc"; s2 = "bab";
	EXPECT_EQ(damerau_levenshtein_non_restr_dist(s1, s2), 2);
	// substitution and insert
	s1 = "aab"; s2 = "babc";
	EXPECT_EQ(damerau_levenshtein_non_restr_dist(s1, s2), 2);
	// substitution and transposition
	s1 = "aabc"; s2 = "bacb";
	EXPECT_EQ(damerau_levenshtein_non_restr_dist(s1, s2), 2);
}

TEST(Damerau_Levenshtein_Non_Restricted_Distance, Same) {
	std::string s1 = "abc", s2 = "abc";
	//std::cerr <<  damerau_levenshtein_non_restr_dist(s1, s2) << std::endl;
	EXPECT_EQ(damerau_levenshtein_non_restr_dist(s1, s2), 0);
}

TEST(Damerau_Levenshtein_Non_Restricted_Distance, Empty) {
	std::string s1 = "", s2 = "abc";
	//std::cerr <<  damerau_levenshtein_non_restr_dist(s1, s2) << std::endl;
	EXPECT_EQ(damerau_levenshtein_non_restr_dist(s1, s2), 3);
	EXPECT_EQ(damerau_levenshtein_non_restr_dist(s2, s1), 3);
	EXPECT_EQ(damerau_levenshtein_non_restr_dist(s1, s1), 0);
}