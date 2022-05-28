// � ����� �������� ���������� �� �������, � ����� �� ���� ���� "������" "����".
#include<iostream>
#include<math.h>
#include<windows.h>
using namespace std;
string to_word(string n, bool is_after_dot) {
	if (n.size() == 0) return "";
	if (n == "100") return "��� ";
	if (n == "0" && !is_after_dot) return "���� ";
	string above_twelve[] = {"","","��������","��������","�����","��������", "���������", "�������", "��������", "���'������"};
	string under_ten[] = {"","����������", "����������", "����������", "������������", "����������", "�����������", "���������", "����������", "���'���������"};
	string digits[] = {"","����", "���", "���", "������", "����", "�����", "��", "���", "���'���"};
	char unit = n[n.size()-1], ten;
	if (n.size() > 1) ten = n[0];
	else ten = char('0'-1);
	string ret = "";
	if (is_after_dot && unit == '0' && ten >= '0') return digits[ten-'0'];
	else if (ten > '1') {
		ret+=above_twelve[ten-'0']+" ";
	}
	else if (ten == '1') {
		if (unit == '0') return "������ ";
		else return under_ten[unit-'0'];
	}
	else if (ten == '0' && is_after_dot && unit != '0') ret+="���� ";
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
