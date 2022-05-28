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
	cout << "������ ����� ������:\n";
	int n, number;
	cin >> n;
	int* a = new int [n];
	cout << "������ �����:\n";
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << "������ �����, ��� ����� � ���������:\n";
	cin >> number;
	sort(a,a+n);
	for (int i = 0; i < n; i++) {
		if (bin_search(a,n,number-a[i])) {
			cout << "���, ��������� �� ����� " << a[i] << " " << number-a[i] << '\n';
			return 0;
		}
	}
	cout << "ͳ\n";
}
