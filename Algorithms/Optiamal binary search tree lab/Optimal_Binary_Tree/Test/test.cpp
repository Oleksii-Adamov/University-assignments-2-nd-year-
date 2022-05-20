#include "pch.h"
#include "../Optimal_Binary_Tree/uppertriangularmatrix.h"
#include "../Optimal_Binary_Tree/optimalBST.h"
TEST(UpperTriangularMatrixTestCase, UpperTriangularMatrixTest) {
    std::size_t n = 5;
    UpperTriangularMatrix m(n);
    std::size_t count = 0;
    // and test of algorithm
    for (std::size_t level = 0; level < n; level++) {
        for (std::size_t i = 0; i < n - level; i++) {
            m.set(i, i + level, count);
            count++;
        }
    }
    EXPECT_EQ(m.get(0, 0), 0);
    EXPECT_EQ(m.get(1, 1), 1);
    EXPECT_EQ(m.get(2, 2), 2);
    EXPECT_EQ(m.get(3, 3), 3);
    EXPECT_EQ(m.get(4, 4), 4);
    EXPECT_EQ(m.get(0, 1), 5);
    EXPECT_EQ(m.get(1, 2), 6);
    EXPECT_EQ(m.get(2, 3), 7);
    EXPECT_EQ(m.get(3, 4), 8);
    EXPECT_EQ(m.get(0, 2), 9);
    EXPECT_EQ(m.get(1, 3), 10);
    EXPECT_EQ(m.get(2, 4), 11);
    EXPECT_EQ(m.get(0, 3), 12);
    EXPECT_EQ(m.get(1, 4), 13);
    EXPECT_EQ(m.get(0, 4), 14);
}
TEST(OptimalBSTTestCase, OptimalBSTTest) {
    std::vector<long long> freq = { 70, 40 };
    std::vector<std::size_t> ans;
    EXPECT_EQ(optimalBST(freq, ans),150);
    EXPECT_EQ(ans[0], 0);
    EXPECT_EQ(ans[1], 1);
    freq = { 50, 70, 20, 30 };
    ans.clear();
    EXPECT_EQ(optimalBST(freq, ans), 290);
    EXPECT_EQ(ans[0], 1);
    EXPECT_EQ(ans[1], 0);
    EXPECT_EQ(ans[2], 3);
    EXPECT_EQ(ans[3], 2);
}