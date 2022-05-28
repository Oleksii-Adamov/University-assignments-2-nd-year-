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
int main() {
	int n, m;
	cin >> n;
	double *a = new double [n];
	for (int i = 0; i < n; i++) cin >> a[i];
	cin >> m;
	double *b = new double [m];
	for (int i = 0; i < m; i++) cin >> b[i];
	double *c = new double [n+m];
	merge(a,n,b,m,c);
	for (int i = 0; i < n + m; i++) {
		cout << c[i] << " ";
	}
}
