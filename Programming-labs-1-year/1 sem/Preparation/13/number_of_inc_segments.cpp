#include<iostream>
using namespace std;
int main() {
	int n, ans = 0;
	bool is_inc = false;
	cin >> n;
	double *a = new double [n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (i != 0 && a[i] > a[i-1]) {
			is_inc = true;
		}
		else {
			if (is_inc) ans++;
			is_inc = false;
		}
	}
	if (is_inc) ans++;
	cout << ans;
}
