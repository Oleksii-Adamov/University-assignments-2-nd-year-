#include<bits/stdc++.h>
#include "windows.h"
using namespace std;
int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	int a,b,c;
	cin >> a >> b >> c;
	if (c >= a + b || a >= b + c || b >= a + c) {
		cout << "Трикутник не існує";
	}
	else if (c*c == a*a + b*b || a*a == b*b + c*c || b*b == a*a + c*c) {
		cout << "Трикутник прямокутний";
	}
	else if (c*c > a*a + b*b || a*a > b*b + c*c || b*b > a*a + c*c) {
		cout << "Трикутник тупокутний";
	}
	else cout << "Трикутник гострокутний";
}
