#include<iostream>
#include<algorithm>
using namespace std;
double max_that_repeated_in_matrix(double** a, int rows, int columns) {
	int size = rows*columns, pos = 0;
	double *arr = new double [size];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			arr[pos] = a[i][j];
			pos++;
		}
	}
	sort(arr,arr+size);
	for (int i = size - 1; i >= 1; i--) {
		if (arr[i] == arr[i-1]) return arr[i];
	}
	delete[] arr;
	return 0.33333333;
}
int main() {
	int n, m;
	cin >> n >> m;
	double** a = new double* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new double [m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	cout << max_that_repeated_in_matrix(a,n,m);
}
