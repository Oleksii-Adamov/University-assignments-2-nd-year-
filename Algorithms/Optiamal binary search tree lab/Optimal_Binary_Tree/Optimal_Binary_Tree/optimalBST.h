#pragma once
#include <vector>
#include <limits>
#include "uppertriangularmatrix.h"

long long optimalBST(const std::vector<long long>& freq, std::vector<std::size_t>& path) {
	std::size_t n = freq.size();
	UpperTriangularMatrix cost(n);
	UpperTriangularMatrix root(n);
    // prefix sum
    std::vector<long long> pr(n);
    pr[0] = freq[0];
    for (std::size_t i = 1; i < n; i++) {
        pr[i] = pr[i - 1] + freq[i];
    }
    // main diagonal and up
    for (std::size_t level = 0; level < n; level++) {
        for (std::size_t i = 0; i < n - level; i++) {
            std::size_t j = i + level;
            long long min_cost = LLONG_MAX, best_node = 0;
            // finding the best root (minimizing cost)
            for (int r = i; r <= j; r++) {
                long long now = cost.get(i, r - 1) + cost.get(r + 1, j);
                if (now < min_cost) {
                    min_cost = now;
                    best_node = r;
                }
            }
            long long sum = pr[j];
            if (i > 0) sum -= pr[i - 1];
            cost.set(i, j, sum + min_cost);
            root.set(i, j, best_node);
        }
    }
    // iterative dfs tree recovering
    std::vector<int> root_stack;
    std::vector<int> i_stack;
    std::vector<int> j_stack;
    root_stack.push_back(root.get(0, n - 1));
    i_stack.push_back(0);
    j_stack.push_back(n - 1);
    while (!root_stack.empty())
    {
        int now_root = root_stack[root_stack.size() - 1];
        root_stack.pop_back();
        path.push_back(now_root);
        int i = i_stack[i_stack.size() - 1];
        i_stack.pop_back();
        int j = j_stack[j_stack.size() - 1];
        j_stack.pop_back();
        // push right if valid
        if (now_root + 1 <= j) {
            root_stack.push_back(root.get(now_root + 1, j));
            i_stack.push_back(now_root + 1);
            j_stack.push_back(j);
        }
        // push left if valid
        if (i <= now_root - 1) {
            root_stack.push_back(root.get(i, now_root - 1));
            i_stack.push_back(i);
            j_stack.push_back(now_root - 1);
        }
    }
    return cost.get(0, n - 1);
}