#include<cmath>
struct rational_number {
	// numerator - ���������, denominator - ���������
	int numerator, denominator;
};
// ���
int gcd(int x, int y) {
	if (y == 0) return x;
	return gcd(y, x % y);
}
// ���
int lcm(int x, int y) {
	return x / gcd(x,y) * y;
}
bool is_rational_number_correct(rational_number x) {
	// ��������� ����������� ���� ������� ���� �����������
	if (x.denominator <= 0) return false;
	return true;
}
rational_number reduction(rational_number x) {
	// -1/0 - ����������� ��� �������
	if (!is_rational_number_correct(x)) return {-1,0};
	int d = gcd(abs(x.numerator), x.denominator);
	x.numerator /= d;
	x.denominator /= d;
	return x;
}
// �������� ������� 0, ���� a = b. -1, ���� a > b. 1, ���� a < b. 2 - ����������� ��� �������
int Crn(rational_number a, rational_number b) {
	if (!(is_rational_number_correct(a) && is_rational_number_correct(b))) return 2;
	a = reduction(a);
	b = reduction(b);
	int common_denominator = lcm(a.denominator, b.denominator);
	a.numerator *= common_denominator/a.denominator;
	b.numerator *= common_denominator/b.denominator;
	if (a.numerator == b.numerator) return 0;
	if (a.numerator < b.numerator) return 1;
	return -1;
}
