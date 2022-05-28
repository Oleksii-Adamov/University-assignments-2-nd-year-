#include<iostream>
using namespace std;
void cycle_encryption(char source[], char dest[]) {
	for (int i = 0; source[i] != '\0'; i++) {
		if (source[i] == 'z') dest[i] = 'a';
		else if (source[i] == 'Z') dest[i] = 'A';
		else dest[i] = source[i] + 1;
	}
}
int main() {
	char s[5000];
	cin >> s;
	char ans[5000];
	cycle_encryption(s,ans);
	cout << ans;
}
