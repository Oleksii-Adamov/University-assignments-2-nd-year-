#include<bits/stdc++.h>
#include "windows.h"
using namespace std;
int gcd(int a, int b) {
	if (b == 0) {
		return a; 
	} 
	return gcd(b,a%b);
}
int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	int n,m;
	cin >> n >> m;
	cout << n*m/gcd(n,m);
}
