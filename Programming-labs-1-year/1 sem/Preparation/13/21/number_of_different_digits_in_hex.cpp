//#include<iostream>
//using namespace std;
int number_of_different_digits_in_hex(int n) {
	int ans = 0;
	bool used[16];
	for (int i = 0; i < 16; i++) used[i] = false;
	while(n != 0) {
		int digit = n % 16;
		if (!used[digit]) {
			ans++;
			used[digit] = true;
		}
		n/=16;
	}
	return ans;
}
int main() {
	/*
	int n;
	cin >> n;
	cout << number_of_different_digits_in_hex(n);
	*/
}
