#include<iostream>
#include<algorithm>
using namespace std;
void copy_string(char source[], char dest[]) {
	int i = 0;
	while (true) {
		dest[i] = source[i];
		if (source[i] == '\0') break;
		i++;
	}
}
bool cmp(char x[], char y[]) { 
	int i = 0;
	for (; x[i] != '\0' && y[i] != '\0'; i++) {
		if (x[i] != y[i]) return x[i] < y[i];
	}
	return x[i] == '\0';
}
bool is_strings_equal(char x[], char y[]) {
	int i = 0;
	for (; x[i] != '\0' && y[i] != '\0'; i++) {
		if (x[i] != y[i]) return false;
	}
	return x[i] == y[i];
}
int number_of_different_words(char s[]) {
	bool is_letters = true;
	int len_of_word = 0, max_size = 1, size = 0, max_size_of_word = 1;
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] == ' ') {
			max_size++;
			max_size_of_word = max(max_size_of_word, len_of_word);
			len_of_word = 0;
		}
		else {
			len_of_word++;
		}
	}
	len_of_word = 0;
	char** words = new char* [max_size];
	for (int i = 0; i < max_size; i++) {
		words[i] = new char [max_size_of_word];
	}
	char* word = new char [max_size_of_word];
	for (int i = 0; ; i++) {
		if (s[i] == ' ' || s[i] == '\0' || s[i] == '\n' || s[i] == '\t'|| s[i] == ',' || s[i] == '\"' || s[i] == '\?' || s[i] == '.') {
			if (is_letters && len_of_word > 1) {
				word[len_of_word] = '\0';
				copy_string(word,words[size]);
				size++;
			}
			if (s[i] == '\0') break;
			len_of_word = 0;
			is_letters = true;
		}
		else if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '\'')) {
			is_letters = false;
		}
		else {
			word[len_of_word] = s[i];
			len_of_word++;
		}
	}
	if (size == 0) return 0;
	sort(words,words+size,cmp);
	int ans = 1;
	for (int i = 0; i < size; i++) cout << words[i] << " ";
	for (int i = 1; i < size; i++) {
		if (!is_strings_equal(words[i],words[i-1])) ans++;
	}
	delete[] word;
	delete[] words;
	return ans;
}
int main() {
	char s[50001];
	fgets(s,50000,stdin);
	int ans = number_of_different_words(s);
	cout << "\n" << ans;
}
