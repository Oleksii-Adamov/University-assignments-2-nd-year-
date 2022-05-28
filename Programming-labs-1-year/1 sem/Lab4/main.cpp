/*
Обчислити значення 2 функцій в точці з x точністю eps, при чому n = 1...? або n = 0…?.
Оформити у вигляді бібліотеки (info - https://www.geeksforgeeks.org/write-header-file-c/).
Сігнатура фукції повинна бути у форматі:
double exp(double x, double eps = 0.001), 
double shx(double x, double eps = 0.001) і т.д.
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
	if (int(result) == int(ERROR_CODE)) std::cout << "Арктангенс не можливо підрахувати за даною формолою\n";
	else std::cout << "Арктангенс с заданою точністю: " << std::setprecision(ceil(-log10(eps))) << result << '\n';
	
	
	result = arctg(x);
	if (int(result) == int(ERROR_CODE)) std::cout << "Арктангенс не можливо підрахувати за даною формолою\n";
	else std::cout << "Арктангенс с стандартною точністю 0.001 : " << std::setprecision(ceil(-log10(0.001))) << result << '\n';	
	
	result = ch(x,eps);
	if (int(result) == int(ERROR_CODE)) std::cout << "Гіперболічний косінус не можливо підрахувати за даною формолою\n";
	else std::cout << "Гіперболічний косінус с заданою точністю: " << std::setprecision(ceil(-log10(eps))) << result << '\n';
	
	result = ch(x);
	if (int(result) == int(ERROR_CODE)) std::cout << "Гіперболічний косінус не можливо підрахувати за даною формолою\n";
	else std::cout << "Гіперболічний косінус с стандартною точністю 0.001 : " << std::setprecision(ceil(-log10(0.001))) << result << '\n';
}
