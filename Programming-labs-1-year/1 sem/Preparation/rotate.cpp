#include<iostream>
int main() {
	int t;
	std::cin >> t;
	for (int q = 0; q < t; q++) {
		int n;
		std::cin >> n;
		int** a = new int* [n];
		for (int i = 0; i < n; i++) {
			a[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				std::cin >> a[i][j];
			}
		}
		for (int i = 0; i < n / 2; i++) {
			for (int j = i; j < n - 1 - i; j++) {
				int now_i = i, now_j = j, now = a[i][j];
				for (int f = 0; f < 4; f++) {
					// anti clockwise
					std::swap(now, a[n - 1 - now_j][now_i]); 
					int new_i = n - 1 - now_j, new_j = now_i;
					/*
					clocwise
					std::swap(now, matrix[now_j][n - 1- now_i]);
					int new_i = now_j, new_j = n - 1- now_i;
					*/
					now_i = new_i;
					now_j = new_j;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << a[i][j] << " ";
			}
			std::cout << "\n";
		}
		for (int i = 0; i < n; i++) {
			delete[] a[i];
		}
		delete[] a;
	}
}
