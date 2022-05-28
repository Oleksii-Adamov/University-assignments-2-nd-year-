#include<iostream>
using namespace std;
int number_of_words(char s[]) {
	int cur_len = 0,  ans = 0;
	bool is_letters = true;
	for (int i = 0; ; i++) {
		/*if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
			cur_len++;
		}
		else {
			if (cur_len > 1) {
				ans++;
			} 
			cur_len = 0;
		}*/
		if (s[i] == ' ' || s[i] == '\0' || s[i] == '\n' || s[i] == '\t'|| s[i] == ',' || s[i] == '\"' || s[i] == '\?' || s[i] == '.') {
			if (is_letters && cur_len > 1) {
				cout << s[i-1];
				ans++;
			}
			if (s[i] == '\0') break;
			cur_len = 0;
			is_letters = true;
		}
		else if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '\'')) {
			is_letters = false;
		}
		else cur_len++;
	}
	/*if (cur_len > 1) {
		ans++;
	} */
	return ans;
}
int main() {
	char s[50002];
	cin.getline(s,50001);
	cout << number_of_words(s);
}
