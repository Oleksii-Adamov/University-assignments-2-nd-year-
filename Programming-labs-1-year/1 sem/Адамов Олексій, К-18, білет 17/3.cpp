// цифра у римській системі -1 - повідомлення про помилку
int roman_digit(char c) {
	switch(c) {
		case 'I': return 1;
		case 'V': return 5;
		case 'X': return 10;
		case 'L': return 50;
		case 'C': return 100;
		case 'D': return 500;
		case 'M': return 1000;
	}
	return -1;
}
// -1 - повідомлення про помилку
int from_roman_to_decimal(char r[]) {
	if (r[0] == '\0') return 0;
	int prev = roman_digit(r[0]), ans = 0;
	if (prev == -1) return -1;
	for (int i = 1; r[i] != '\0'; i++) {
		int now = roman_digit(r[i]);
		if (now == -1) return -1;
		if (prev < now) ans -= prev;
		else ans += prev;
		prev = now;
	}
	ans += prev;
	return ans;
}
