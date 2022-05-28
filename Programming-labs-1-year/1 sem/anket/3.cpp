#include<bits/stdc++.h>
#include "windows.h"
using namespace std;
int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	int n;
	cin >> n;
	if (n/1000 == 0) {
		cout << "Введено не чотирьохзначне число";
	}
	else if (n / 1000 + n / 100 % 10 == n / 10 % 10 + n % 10) {
		cout << "Сумма перших двох цифр дорінює суммі двох його останніх цифр";
	}
	else cout << "Сумма перших двох цифр не дорінює суммі двох його останніх цифр";
}
