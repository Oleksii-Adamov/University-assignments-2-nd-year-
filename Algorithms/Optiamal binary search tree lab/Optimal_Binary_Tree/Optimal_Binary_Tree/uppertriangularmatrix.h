#pragma once
#include <vector>

class UpperTriangularMatrix
{
public:
    UpperTriangularMatrix() {};
    UpperTriangularMatrix(std::size_t n) {
        set_dimension(n);
    };
private:
    std::vector<long long> arr;
public:
    long long get(int i, int j) {
        if (i > j) return 0;
        return arr[i + j * (j + 1) / 2];
    }
    void set(int i, int j, long long val) {
        if (i <= j) {
            arr[i + j * (j + 1) / 2] = val;
        }
    }
    void set_dimension(std::size_t n) {
        arr.clear();
        arr.resize(n * (n + 1) / 2);
    }
};