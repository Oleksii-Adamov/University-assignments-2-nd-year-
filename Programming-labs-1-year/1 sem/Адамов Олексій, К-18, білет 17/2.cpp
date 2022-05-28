#include<cmath>
struct rational_number {
	// numerator - чисельник, denominator - знаменник
	int numerator, denominator;
};
// НОД
int gcd(int x, int y) {
	if (y == 0) return x;
	return gcd(y, x % y);
}
// НОК
int lcm(int x, int y) {
	return x / gcd(x,y) * y;
}
bool is_rational_number_correct(rational_number x) {
	// знаменник раціональної дробі повинен бути натуральним
	if (x.denominator <= 0) return false;
	return true;
}
rational_number reduction(rational_number x) {
	// -1/0 - повідомлення про помилку
	if (!is_rational_number_correct(x)) return {-1,0};
	int d = gcd(abs(x.numerator), x.denominator);
	x.numerator /= d;
	x.denominator /= d;
	return x;
}
// фунукція повертає 0, якщо a = b. -1, якщо a > b. 1, якщо a < b. 2 - повідомлення про помилку
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
