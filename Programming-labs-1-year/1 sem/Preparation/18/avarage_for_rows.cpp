#include<bits/stdc++.h>
using namespace std;
int main() {
	int n, m;
	cin >> n >> m;
	double *ans = new double [n];
	for (int i = 0; i < n; i++) {
		ans[i] = 0;
		for (int j = 0; j < m; j++) {
			double a;
			cin >> a;
			ans[i] += a;
		}
		ans[i]/=m;
	}
	for (int i = 0; i < n; i++) {
		cout << ans[i] << " ";
	}
	delete[] ans;
}
