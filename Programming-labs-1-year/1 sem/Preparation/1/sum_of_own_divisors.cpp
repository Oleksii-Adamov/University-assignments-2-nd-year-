//#include<iostream>
#include<math.h>
//using namespace std;
sum_of_own_divisors(int n) {
	int sum = 1;
	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			sum+=i;
			if (i != sqrt(n)) {
				sum+=n/i;	
			}
		}
	}
	return sum;
}
max_sum_of_own_divisors(int n) {
	int ans = 1, dp = 0;
	for (int i = 2; i <= n; i++) {
		int now = sum_of_own_divisors(i);
		if (now > dp) {
			dp = now;
			ans = i;
		}
	}
	return ans;
}
int main() {
	/*
	int n;
	cin >> n; 
	cout << max_sum_of_own_divisors(n) << " ";
	*/
}
