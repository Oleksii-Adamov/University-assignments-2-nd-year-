#include<iostream>
#include<windows.h>
using namespace std;
int main() { 
    SetConsoleOutputCP(1251);
    cout << "������ N:\n";
	int n;
    cin >> n;
	cout << "������ �������:\n";
	int **a = new int* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new int [n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	cout << "����� ��������:\n";
	for (int j = n - 1; j >= 0; j--) {
		int maxi = a[0][j];
		for (int i = 1; i < n - j; i++) {
			if (a[i][j+i] > maxi) maxi = a[i][j+i];
		}
		cout << maxi << " ";
	}
	for (int i = 1; i < n; i++) {
		int maxi = a[i][0];
		for (int j = 0; j < n - i; j++) {
			if (a[i+j][j] > maxi) maxi = a[i+j][j];
		}
		cout << maxi << " ";
	}
	for (int i = 0; i < n; i++) {
		delete[] a[i];
	}
	delete[] a;
}
