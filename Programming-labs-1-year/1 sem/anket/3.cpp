#include<bits/stdc++.h>
#include "windows.h"
using namespace std;
int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	int n;
	cin >> n;
	if (n/1000 == 0) {
		cout << "������� �� �������������� �����";
	}
	else if (n / 1000 + n / 100 % 10 == n / 10 % 10 + n % 10) {
		cout << "����� ������ ���� ���� ������ ���� ���� ���� ������� ����";
	}
	else cout << "����� ������ ���� ���� �� ������ ���� ���� ���� ������� ����";
}
