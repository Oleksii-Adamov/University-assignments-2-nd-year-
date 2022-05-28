#include<iostream>
#include<windows.h>
using namespace std;
int solution(int **arr, int n, int m) {
	int positive = 0, negative = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] > 0) positive++;
			else if (arr[i][j] < 0) negative++;
		}
	}
	if (negative == positive) return 0;
	if (positive > negative) return 1;
	return -1;
}
int main() { 
	SetConsoleOutputCP(1251);
    cout << "¬вед≥ть розм≥ри матриц≥:\n";
	int n,m;
    cin >> n >> m;
	cout << "¬вед≥ть матрицю:\n";
	int **a = new int* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new int [m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	cout << solution(a,n,m);
	for (int i = 0; i < n; i++) {
		delete[] a[i];
	}
	delete[] a;
}
