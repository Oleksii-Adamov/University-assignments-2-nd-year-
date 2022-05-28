#include<iostream>
using namespace std;
void merge(double** a, int rows_a, double** b, int rows_b, double** dest, int columns) {
	int a_p = 0, b_p = 0, i = 0;
	for (;a_p < rows_a && b_p < rows_b; i++) {
		double sum_a = 0, sum_b = 0;
		for (int j = 0; j < columns; j++) {
			sum_a += a[a_p][j];
			sum_b += b[b_p][j]; 
		}
		if (sum_a < sum_b) {
			for (int j = 0; j < columns; j++) {
				dest[i][j] = a[a_p][j];
			}
			a_p++;
		}
		else {
			for (int j = 0; j < columns; j++) {
				dest[i][j] = b[b_p][j];
			}
			b_p++;
		}
	}
	for(; a_p < rows_a; i++, a_p++) {
		for (int j = 0; j < columns; j++) {
				dest[i][j] = a[a_p][j];
		}
	}
	for(; b_p < rows_b; i++, b_p++) {
		for (int j = 0; j < columns; j++) {
				dest[i][j] = b[b_p][j];
		}
	}
}
void sort_of_matrix_by_first_element_of_row(double** a, int rows, int columns) {
	if (rows == 1) return;
	int mid = (rows-1)/2, rows_a1 = mid+1, rows_a2 = rows - rows_a1, i;
	double** a1 = new double* [rows_a1];
	double** a2 = new double* [rows_a2];
	for (i = 0; i < rows_a1; i++) {
		a1[i] = new double [columns];
		for (int j = 0; j < columns; j++) {
			a1[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < rows_a2; i++) {
		a2[i] = new double [columns];
		for (int j = 0; j < columns; j++) {
			a2[i][j] = a[i+rows_a1][j];
		}
	}
	sort_of_matrix_by_first_element_of_row(a1,rows_a1,columns);
	sort_of_matrix_by_first_element_of_row(a2,rows_a2,columns);
	merge(a1,rows_a1,a2,rows_a2,a,columns);
	for (i = 0; i < min(rows_a1,rows_a2); i++) {
		delete[] a1[i];
		delete[] a2[i];
	}
	for (; i < rows_a1; i++) delete[] a1[i];
	for (; i < rows_a2; i++) delete[] a2[i];
	delete[] a1;
	delete[] a2;
}
int main() {
	int n,m;
	cin >> n >> m;
	double** a = new double* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new double [m];
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	sort_of_matrix_by_first_element_of_row(a,n,m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << a[i][j] << " ";
		}
		cout << "\n";
	}
	for (int i = 0; i < n; i++) {
		delete[] a[i];
	}
	delete[] a;
}
