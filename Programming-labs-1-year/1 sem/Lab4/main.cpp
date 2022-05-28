/*
��������� �������� 2 ������� � ����� � x ������� eps, ��� ���� n = 1...? ��� n = 0�?.
�������� � ������ �������� (info - https://www.geeksforgeeks.org/write-header-file-c/).
ѳ������� ������ ������� ���� � ������:
double exp(double x, double eps = 0.001), 
double shx(double x, double eps = 0.001) � �.�.
3) ch(x)
9) arctg(x)
*/
#include<iostream>
#include<windows.h>
#include <iomanip>
#include"function.h"
int main() {
	SetConsoleOutputCP(1251);
	double x, eps;
	std::cin >> x >> eps;
	
	std::cout << std::fixed;
	double result = arctg(x,eps);
	if (int(result) == int(ERROR_CODE)) std::cout << "���������� �� ������� ���������� �� ����� ��������\n";
	else std::cout << "���������� � ������� �������: " << std::setprecision(ceil(-log10(eps))) << result << '\n';
	
	
	result = arctg(x);
	if (int(result) == int(ERROR_CODE)) std::cout << "���������� �� ������� ���������� �� ����� ��������\n";
	else std::cout << "���������� � ����������� ������� 0.001 : " << std::setprecision(ceil(-log10(0.001))) << result << '\n';	
	
	result = ch(x,eps);
	if (int(result) == int(ERROR_CODE)) std::cout << "ó���������� ������ �� ������� ���������� �� ����� ��������\n";
	else std::cout << "ó���������� ������ � ������� �������: " << std::setprecision(ceil(-log10(eps))) << result << '\n';
	
	result = ch(x);
	if (int(result) == int(ERROR_CODE)) std::cout << "ó���������� ������ �� ������� ���������� �� ����� ��������\n";
	else std::cout << "ó���������� ������ � ����������� ������� 0.001 : " << std::setprecision(ceil(-log10(0.001))) << result << '\n';
}
