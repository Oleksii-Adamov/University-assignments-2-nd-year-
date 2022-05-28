#include<iostream>
#include<math.h>
#include<windows.h>
#include<limits>
#include<vector>
#include<algorithm>
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
	long long max_pos = log2(n);
	vector<long long> a;
	for (int delta = 1; delta <= max_pos; delta++) {
		for (int start_pos = 0; start_pos <= max_pos - delta; start_pos++) {
			long long number = 1<<start_pos; //2^start_pos побітовий зсув
			for (int end_pos = start_pos + delta; end_pos <= max_pos; end_pos+=delta) {
				number+=1<<end_pos;
				if (number > n) break;
				a.push_back(number);
			}
		}
	}
	sort(a.begin(),a.end());
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << "\n";
		if(!cout.good()) return 1;
	}
	return 0;
}
