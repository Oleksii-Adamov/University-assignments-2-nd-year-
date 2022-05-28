// асимптотика O(log2(n)^4) если я правильно посчитал
// работает немного медленее чем O(n) на маленьких значениях и значительно быстрее на больших
#include<iostream>
#include<math.h>
#include<windows.h>
#include<limits>
using namespace std;
int main() { 
    SetConsoleOutputCP(1251);
	long long n;
	cout << "Введіть натуральне число, до якого програма буде шукати натуральні числа, в двійковому представленні яких номери ненульових розрядів утворюють арифметичну прогресію \n";
	cin >> n;
	while (!cin.good() || n <= 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Неправильні вхідні данні \n";
		cin >> n;
	}
	// Розряди нумеруються справа наліво починаючи з нуля
	cout << "Ці числа: \n";
	int max_pos = log2(n);
	for (int delta = 1; delta <= max_pos; delta++) {
		for (int start_pos = 0; start_pos <= max_pos - delta; start_pos++) {
			long long number = 1<<start_pos; //2^start_pos побітовий зсув
			for (int end_pos = start_pos + delta; end_pos <= max_pos; end_pos+=delta) {
				number+=1<<end_pos;
				if (number > n) break;
				cout << number << "\n";
			}
		}
	}
	return 0;
}
