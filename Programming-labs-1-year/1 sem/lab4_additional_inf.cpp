/*double ch(double x, double eps = 0.001) {
	if (x>1 || x <-1) return ERROR_CODE;
	double result = 0, now = 1, square = x*x;
	for (int i = 1; !(fabs(now) < eps); i++) {
		result+=now;
		now *= square/(2*i*(2*i-1));
	}
	return result;
}*/
