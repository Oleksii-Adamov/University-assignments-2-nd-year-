// � ����� �������� ���������� �� �������, � ����� �� ���� ���� "������" "����".
#include<iostream>
#include<math.h>
#include<windows.h>
using namespace std;
string to_word(int n, bool is_after_dot) {
	if (n == 100) return "���";
	if (n == 0 && !is_after_dot) return "����";
	/*const char***/ string above_twelve[] = {"","","��������","��������","�����","��������", "���������", "�������", "��������", "���'������"};
	string under_ten[] = {"","����������", "����������", "����������", "������������", "����������", "�����������", "���������", "����������", "���'���������"};
	string digits[] = {"","����", "���", "���", "������", "����", "�����", "��", "���", "���'���"};
	int ten = n/10, unit = n%10;
	string ret = "";
	if (ten > 1) {
		ret+=above_twelve[ten]+" ";
	}
	else if (ten == 1) {
		if (unit == 0) return "������";
		else return under_ten[unit];
	}
	else if (ten == 0 && is_after_dot && unit != 0) ret+="���� ";
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
