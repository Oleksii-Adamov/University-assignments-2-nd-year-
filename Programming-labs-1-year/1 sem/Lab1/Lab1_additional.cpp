#include<iostream>
#include<windows.h>
#include<limits>
using namespace std;
int main() { 
    SetConsoleOutputCP(1251);
	long long n;
	cout << "Введіть натуральне число, до якого програма буде шукати натуральні числа, в двійковому представленні яких номери ненульових розрядів утворюють арифметичну прогресію \n";
	if(!cout.good()) return 1;
	cin >> n;
	while (!cin.good() || n <= 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Неправильні вхідні данні \n";
		if(!cout.good()) return 1;
		cin >> n;
	}
	// Розряди нумеруються справа наліво починаючи з нуля
	cout << "Ці числа: \n";
	if(!cout.good()) return 1;
	for (long long i = 1; i <= n; i++) {
		long long temp = i, count = 0, prev = -1, delta = -1;
		bool arifm = true;
		while(temp > 0) {
			int now = temp % 2;
			cout << now;
			temp/=2;
			if (now == 1) {
				if (prev != -1) {
					if (delta == -1) {
						delta = count - prev;
					}
					else if (count - prev != delta) {
						arifm = false;
						//break;
					}
				}
				prev = count;
			}
			count++;
		}
		cout << " ";
		if(!cout.good()) return 1;
		if (arifm && delta != -1) cout << i << "\n";
		else cout << "\n";
		if(!cout.good()) return 1;
	}
	return 0;
}
