#include "pch.h"
#include "../AA_tree/AA_tree.h"
TEST(AA_tree, insert) {
	AA_tree test_tree;
	test_tree.insert(Complex_num(30, 0));
	EXPECT_TRUE(test_tree.is_in(Complex_num(30, 0)));
	test_tree.insert(Complex_num(70, 0));
	EXPECT_TRUE(test_tree.is_in(Complex_num(70, 0)));
	test_tree.insert(Complex_num(15, 0));
	EXPECT_TRUE(test_tree.is_in(Complex_num(15, 0)));
	test_tree.insert(Complex_num(85, 0));
	EXPECT_TRUE(test_tree.is_in(Complex_num(85, 0)));
	test_tree.insert(Complex_num(90, 0));
	EXPECT_TRUE(test_tree.is_in(Complex_num(90, 0)));
	EXPECT_FALSE(test_tree.is_in(Complex_num(10, 0)));
}

TEST(AA_tree, del) {
	AA_tree test_tree;
	test_tree.insert(Complex_num(30, 0));
	EXPECT_TRUE(test_tree.is_in(Complex_num(30, 0)));
	test_tree.insert(Complex_num(70, 0));
	EXPECT_TRUE(test_tree.is_in(Complex_num(70, 0)));
	test_tree.insert(Complex_num(15, 0));
	EXPECT_TRUE(test_tree.is_in(Complex_num(15, 0)));
	test_tree.insert(Complex_num(85, 0));
	EXPECT_TRUE(test_tree.is_in(Complex_num(85, 0)));
	test_tree.insert(Complex_num(90, 0));
	EXPECT_TRUE(test_tree.is_in(Complex_num(90, 0)));
	test_tree.del(Complex_num(15, 0));
	EXPECT_FALSE(test_tree.is_in(Complex_num(15, 0)));
	test_tree.del(Complex_num(30, 0));
	EXPECT_FALSE(test_tree.is_in(Complex_num(30, 0)));
	test_tree.del(Complex_num(85, 0));
	EXPECT_FALSE(test_tree.is_in(Complex_num(85, 0)));
}