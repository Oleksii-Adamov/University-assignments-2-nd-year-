#include<math.h>
const double ERROR_CODE = 1121;
double arctg(double x, double eps = 0.001) {
	if (x>1 || x <-1) return ERROR_CODE;
	double square = x * x, now = x, result = 0, current_pow = x;
	for (int i = 2; !(fabs(now) < eps); i++) {
		result+=now;
		current_pow*=-square;
		now = current_pow/(2*i-1);
	}
	return result;
}
double ch(double x, double eps = 0.001) {
	if (x>1 || x <-1) return ERROR_CODE;
	double square = x*x, result = 1+square/2, now = square*square/(2*3*4);
	for (int i = 3; !(fabs(now) < eps); i++) {
		result+=now;
		now *= square/(2*i*(2*i-1));
	}
	return result;
}
