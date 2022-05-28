// я робив завданн€ опираючись на приклад, у €кому не було слов "дес€та" "сота".
#include<iostream>
#include<math.h>
#include<windows.h>
using namespace std;
string to_word(string n, bool is_after_dot) {
	if (n.size() == 0) return "";
	if (n == "100") return "сто ";
	if (n == "0" && !is_after_dot) return "нуль ";
	string above_twelve[] = {"","","двадц€ть","тридц€ть","сорок","пТ€тдес€т", "ш≥стдес€т", "с≥мдес€т", "в≥с≥мдес€т", "дев'€носто"};
	string under_ten[] = {"","одинадц€ть", "дванадц€ть", "тринадц€ть", "чотирнадц€ть", "пТ€тнадц€ть", "ш≥стнадц€ть", "с≥мнадц€ть", "в≥с≥мнадц€ть", "дев'€тнадц€ть"};
	string digits[] = {"","один", "два", "три", "чотири", "пТ€ть", "ш≥сть", "с≥м", "в≥с≥м", "дев'€ть"};
	char unit = n[n.size()-1], ten;
	if (n.size() > 1) ten = n[0];
	else ten = char('0'-1);
	string ret = "";
	if (is_after_dot && unit == '0' && ten >= '0') return digits[ten-'0'];
	else if (ten > '1') {
		ret+=above_twelve[ten-'0']+" ";
	}
	else if (ten == '1') {
		if (unit == '0') return "дес€ть ";
		else return under_ten[unit-'0'];
	}
	else if (ten == '0' && is_after_dot && unit != '0') ret+="нуль ";
	ret+=digits[unit-'0'];
	return ret;
}
int main() {
	SetConsoleOutputCP(1251);
	string input;
	cin >> input;
	string b[2] = ("","");
	int k = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '.') {
			k++;
		}
		else b[k]+=input[i];
	}
	cout << to_word(b[0],false) << " " << to_word(b[1],true) << "\n"; 
}
