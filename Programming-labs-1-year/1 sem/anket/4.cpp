#include<bits/stdc++.h>
#include "windows.h"
using namespace std;
int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	int n;
	cin >> n;
	vector<int> a(n+1);
	a[1] = 0;
	a[2] = 1;
	for (int i = 3; i <= n; i++) {
		a[i] = a[i-1] + a[i-2];
	}
	cout << a[n];
}
