#include<iostream>
using namespace std;
void merge(double a[], int size_a, double b[], int size_b, double dest[]) {
	int a_p = 0, b_p = 0, i = 0;
	for (; a_p < size_a && b_p < size_b; i++) {
		if (a[a_p] < b[b_p]) {
			dest[i] = a[a_p];
			a_p++;
		}
		else {
			dest[i] = b[b_p];
			b_p++;
		}
	}
	for (; a_p < size_a; i++, a_p++) {
		dest[i] = a[a_p];
	} 
	for (; b_p < size_b; i++, b_p++) {
		dest[i] = b[b_p];
	}
}
void merge_sort(double a[], int size) {
	if (size == 1) return;
	int mid = (size-1)/2, size_a1 = mid+1, size_a2 = size - size_a1;
	double *a1 = new double [size_a1];
	double *a2 = new double [size_a2];
	for (int i = 0; i < size_a1; i++) a1[i] = a[i];
	for (int i = 0; i < size_a2; i++) a2[i] = a[i+size_a1];
	merge_sort(a1,size_a1);
	merge_sort(a2,size_a2);
	merge(a1,size_a1,a2,size_a2,a);
	delete[] a1;
	delete[] a2;
}
int main() {
	int n;
	cin >> n;
	double *a = new double [n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	merge_sort(a,n);
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	delete[] a;
}
