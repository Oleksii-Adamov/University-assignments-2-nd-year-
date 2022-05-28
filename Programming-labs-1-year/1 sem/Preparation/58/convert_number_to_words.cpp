#include<iostream>
#include<cstring>
#include<windows.h>
using namespace std;
void convert_number_to_words (int value, char dest[]) {
	if (value > 999 || value < 100) return;
	const char* units[] = {"","����", "���", "���", "������", "����", "�����", "��", "���", "���'���"};
	const char* under_twelve[] = {"������","����������", "����������", "����������", "������������", "����������", "�����������", "���������", "����������", "���'���������"};
	const char* tens[] = {"","","��������","��������","�����","��������", "���������", "�������", "��������", "���'������"};
	const char* hundreds[] = {"","���","����","������","���������","������","�������", "�����", "������", "���'�����"};
	int hundred = value / 100, ten = value / 10 % 10, unit = value % 10;
	strcat(dest,hundreds[hundred]);
	strcat(dest," ");
	if (ten == 1) {
		strcat(dest,under_twelve[unit]);
	}
	else {
		strcat(dest,tens[ten]);
		if (ten != 0) strcat(dest," ");
		strcat(dest,units[unit]);
	}
}
int main() {
	SetConsoleOutputCP(1251);
	int n;
	cin >> n;
	char ans[500];
	ans[0] = '\0';
	convert_number_to_words(n,ans);
	cout << ans;
}
