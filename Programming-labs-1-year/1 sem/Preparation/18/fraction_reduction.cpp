#include<iostream>
#include<math.h>
using namespace std;
struct fraction {
	int numerator, denominator;
};
int gcd(int x, int y) {
	if (y == 0) return x;
	return gcd(y, x % y);
}
fraction fraction_reduction(fraction x) {
	// знаменник раціональної дробі повинен бути натуральним , -1/0 - повідомлення про помилку
	if (x.denominator <= 0) return {-1,0};
	int d = gcd(abs(x.numerator), x.denominator);
	x.numerator /= d;
	x.denominator /= d;
	return x;
}
int main() {
	fraction input;
	cin >> input.numerator >> input.denominator;
	fraction ans = fraction_reduction(input);
	cout << ans.numerator << "/" << ans.denominator;
}
