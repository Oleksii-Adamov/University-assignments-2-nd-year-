#include<bits/stdc++.h>
#include "windows.h"
using namespace std;
const int MAXINT = INT_MAX;
int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	int n, ans = 0;
	cout << "������ ����� ������" << "\n";
	cin >> n;
	vector<int> a(n), b;
	cout << "������ ����� ����� �������� �����" << "\n";
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<bool> checked(INT_MAX,false); 
	for (int i = 0; i < n; i++) {
		if (!checked[a[i]]) {
			checked[a[i]] = true;
			b.push_back(a[i]);
			ans++;
		}
	}
	cout << "ʳ������ ����� ����� " << ans << "\n";
	cout << "ֳ �����:" << "\n";
	for (int i = 0; i < b.size(); i++) {
		cout << b[i] << " ";
	}
}
