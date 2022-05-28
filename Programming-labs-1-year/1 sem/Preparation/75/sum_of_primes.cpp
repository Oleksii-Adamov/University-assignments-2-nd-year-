//#include<iostream>
//using namespace std;
bool is_prime(int n) {
	if (n == 2) return true;
	if (n < 2 || n % 2 == 0) return false;
	for (long long i = 3; i * i <= n; i+=2) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}
long long sum_of_primes(int a[], int size) {
	long long ans = 0;
	for (int i = 0; i < size; i++) {
		if (is_prime(a[i])) {
			ans+=a[i];
		}
	}
	return ans;
}
int main() {
	/*int n;
	cin >> n;
	int *a = new int [n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << sum_of_primes(a,n);
	delete[] a;
	*/
}
