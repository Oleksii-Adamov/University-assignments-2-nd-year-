#include<iostream>
using namespace std;
int number_of_greater_then_column (double** a, int rows, int columns) {
	double *sum_in_column = new double [columns];
	int ans = 0;
	for (int j = 0; j < columns; j++) {
		sum_in_column[j] = 0;
		for (int i = 0; i < rows; i++) {
			sum_in_column[j] += a[i][j];	
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (a[i][j] > sum_in_column[j] - a[i][j]) {
				cout << i << " " << j << "\n";
				ans++;
			}
		}
	}
	return ans;
}
int main() {
	int n, m;
	cin >> n >> m;
	double **a = new double* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new double [m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	cout << number_of_greater_then_column(a,n,m);
	for (int i = 0; i < n; i++) {
		delete[] a[i];
	}
	delete[] a;
}
