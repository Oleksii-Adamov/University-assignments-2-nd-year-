#include<iostream>
#include<algorithm>
#include<windows.h>
using namespace std;
bool bin_search(int a[], int n, int key) {
	int l = 0, r = n - 1;
	while (l < r) {
		int mid = (l+r)/2;
		if (a[mid] == key) return true;
		if (a[mid] > key) r = mid - 1;
		else l = mid + 1;
	}
	if (a[l] == key) return true;
	return false;
}
int main() {
	SetConsoleOutputCP(1251);
	cout << "Введіть розмір масиву:\n";
	int n, number;
	cin >> n;
	int* a = new int [n];
	cout << "Введіть масив:\n";
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << "Введіть число, яке хотіли б перевірити:\n";
	cin >> number;
	sort(a,a+n);
	for (int i = 0; i < n; i++) {
		if (bin_search(a,n,number-a[i])) {
			cout << "Так, напирклад це числа " << a[i] << " " << number-a[i] << '\n';
			return 0;
		}
	}
	cout << "Ні\n";
}
