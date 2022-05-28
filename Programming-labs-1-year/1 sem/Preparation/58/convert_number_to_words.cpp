#include<iostream>
#include<cstring>
#include<windows.h>
using namespace std;
void convert_number_to_words (int value, char dest[]) {
	if (value > 999 || value < 100) return;
	const char* units[] = {"","один", "два", "три", "чотири", "пТ€ть", "ш≥сть", "с≥м", "в≥с≥м", "дев'€ть"};
	const char* under_twelve[] = {"дес€ть","одинадц€ть", "дванадц€ть", "тринадц€ть", "чотирнадц€ть", "пТ€тнадц€ть", "ш≥стнадц€ть", "с≥мнадц€ть", "в≥с≥мнадц€ть", "дев'€тнадц€ть"};
	const char* tens[] = {"","","двадц€ть","тридц€ть","сорок","пТ€тдес€т", "ш≥стдес€т", "с≥мдес€т", "в≥с≥мдес€т", "дев'€носто"};
	const char* hundreds[] = {"","сто","дв≥ст≥","триста","чотириста","пТ€тсот","ш≥стсот", "с≥мсот", "в≥с≥мсот", "дев'€тсот"};
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
