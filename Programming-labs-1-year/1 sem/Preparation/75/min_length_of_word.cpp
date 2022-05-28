#include<iostream>
using namespace std;
int min_length_of_word(char s[]) {
	// -1 ÿךשמ סכמג םו לא÷
	int cur_len = 0, min_len = -1;
	for (int i = 0; s[i] != '\0'; i++) {
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
			cur_len++;
		}
		else {
			if (cur_len != 0 && (cur_len < min_len || min_len == -1)) {
				min_len = cur_len;
			} 
			cur_len = 0;
		}
	}
	if (cur_len != 0 && (cur_len < min_len || min_len == -1)) {
		min_len = cur_len;
	} 
	return min_len;
}
int main() {
	char s[50002];
	cin.getline(s,50001);
	cout << min_length_of_word(s);
}
