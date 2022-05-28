#include<bits/stdc++.h>
using namespace std;
const long long INF = 1000000000;
long long a[101][101];
int main () {
	int n,s,t;
	cin >> n >> s >> t;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			if (a[i][j] == -1) {
				a[i][j] = INF;
			}
		}
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j<= n; j++) {
				a[i][j] = min(a[i][k] + a[k][j],a[i][j]);
			}
		}
	}
	if (a[s][t] == INF) {
		cout << -1;
	}
	else {
		cout << a[s][t];
	}
	return 0;
}
