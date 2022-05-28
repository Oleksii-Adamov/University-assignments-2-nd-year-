#include<iostream>
using namespace std;
int main() {
	long double eps, result = 0, now = 1;
	long long k = 1;
	cin >> eps;
	while(true) {
		now *= (k+1)/(long double)(k*k);
		cout << k << " " << now << " ";
		if (now < eps) {
			break;
		}
		if (k % 2 == 1) {
			result-=now;
		}
		else {
			result+=now;
		}
		cout << result << "\n";
		k++;
	}
	cout << result;
}
