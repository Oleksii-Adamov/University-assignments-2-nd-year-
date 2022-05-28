//#include<cstdio>
//#include<stdlib.h>
#include<iostream>
using namespace std;
/*int most_frequent_digit_in_text(const char* name) {
	// -1 у тексті немає цифр
	FILE *fp = fopen(name, "r");
	if (fp == NULL) exit(1);
	char c;
	int count[10], max_count = 0, ans = -1;
	for (int i = 0; i < 9; i++) count[i] = 0;
	while((c = fgetc(fp)) != EOF) {
		if (c >= '0' && c <= '9') {
			int digit = c-'0';
			count[digit]++;
			if (count[digit] > max_count) {
				max_count = count[digit];
				ans = digit;
			}
		}
	}
	fclose(fp);
	return ans;
}*/
/*int most_frequent_digit_in_text(char s[]) { 
	// -1 у тексті немає цифр
	int count[10], max_count = 0, ans = -1;
	for (int i = 0; i < 9; i++) count[i] = 0;
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			int digit = s[i]-'0';
			count[digit]++;
			if (count[digit] > max_count) {
				max_count = count[digit];
				ans = digit;
			}
		}
	}
	return ans;
}*/
int main() {
	//cout << most_frequent_digit_in_text("input.txt");
	//char s[50000];
	//cin.getline(s,50000,'\0');
	//cout << most_frequent_digit_in_text(s);
	char c;
	int count[10], max_count = 0, ans = -1;
	for (int i = 0; i < 9; i++) count[i] = 0;
	while((c = getchar()) != EOF) {
		if (c >= '0' && c <= '9') {
			int digit = c - '0';
			count[digit]++;
			if (count[digit] > max_count) {
				max_count = count[digit];
				ans = digit;
			}
		}
	}
	cout << ans;
}
