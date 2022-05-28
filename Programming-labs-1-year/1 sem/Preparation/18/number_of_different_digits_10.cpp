#include<iostream>
using namespace std;
int number_of_different_digits(long long n) {
	int ans = 0;
	bool used[10];
	for (int i = 0; i < 10; i++) used[i] = false;
	while (n != 0) {
		int digit = n%10;
		if (!used[digit]) {
			ans++;
			used[digit] = true;
		}
		n/=10;
	}
	return ans;
}
int main() {
	long long n;
	cin >> n;
	cout << number_of_different_digits(n);
}
