#include<iostream>
using namespace std;

int main() {
	int n, m, max_sum_index = -1;
	double max_sum = 0;
	cin >> n >> m;
	/*
	int **a = new int* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new int [m];
	}
	*/	
	for (int i = 0; i < n; i++) {
		double sum = 0;
		for (int j = 0; j < m; j++) {
			double a;
			cin >> a;
			sum += a;
		}	
		if (sum > max_sum) {
			max_sum = sum;
			max_sum_index = i;
		}
	}
	// нумерація рядків з нуля
	cout << max_sum_index << " " << max_sum;
	/*
	for (int i = 0; i < n; i++) {
		delete[] a[i];
	}
	delete[] a;
	*/
}
