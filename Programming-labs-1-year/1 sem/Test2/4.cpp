// я робив завданн€ опираючись на приклад, у €кому не було слов "дес€та" "сота".
#include<iostream>
#include<math.h>
#include<windows.h>
using namespace std;
string to_word(int n, bool is_after_dot) {
	if (n == 100) return "сто";
	if (n == 0 && !is_after_dot) return "нуль";
	/*const char***/ string above_twelve[] = {"","","двадц€ть","тридц€ть","сорок","пТ€тдес€т", "ш≥стдес€т", "с≥мдес€т", "в≥с≥мдес€т", "дев'€носто"};
	string under_ten[] = {"","одинадц€ть", "дванадц€ть", "тринадц€ть", "чотирнадц€ть", "пТ€тнадц€ть", "ш≥стнадц€ть", "с≥мнадц€ть", "в≥с≥мнадц€ть", "дев'€тнадц€ть"};
	string digits[] = {"","один", "два", "три", "чотири", "пТ€ть", "ш≥сть", "с≥м", "в≥с≥м", "дев'€ть"};
	int ten = n/10, unit = n%10;
	string ret = "";
	if (ten > 1) {
		ret+=above_twelve[ten]+" ";
	}
	else if (ten == 1) {
		if (unit == 0) return "дес€ть";
		else return under_ten[unit];
	}
	else if (ten == 0 && is_after_dot && unit != 0) ret+="нуль ";
	ret+=digits[unit];
	return ret;
}
int main() {
	SetConsoleOutputCP(1251);
	double input;
	cin >> input;
	int x = floor(input*100);
	//cout << x/1000*10+x/100%10 << " " << x/10%10*10+x%10 << "\n"; 
	cout << to_word(x/1000*10+x/100%10,false) << " " << to_word(x/10%10*10+x%10,true) << "\n"; 
}
