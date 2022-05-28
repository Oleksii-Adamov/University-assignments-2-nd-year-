#include<iostream>
#include<windows.h>
using namespace std;
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
	int *min_in_row = new int [n];
	int *max_in_column = new int [m];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	for (int j = 0; j < m; j++) max_in_column[j] = a[0][j];
	for (int i = 0; i < n; i++) {
		min_in_row[i] = a[i][0];
		for (int j = 0; j < m; j++) {
			if (a[i][j] < min_in_row[i]) min_in_row[i] = a[i][j];  
			if (a[i][j] > max_in_column[j]) max_in_column[j] = a[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (min_in_row[i] == a[i][j] && max_in_column[j] == a[i][j]) {
				cout << a[i][j] << " за ≥ндексами " << i << " " << j << "\n";
			}
		}
	}
	for (int i = 0; i < n; i++) {
		delete[] a[i];
	}
	delete[] a;
	delete[] min_in_row;
	delete[] max_in_column;
}
