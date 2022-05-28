//#include<iostream>
//#include<cstring>
//using namespace std;
// повертає позицію рахуючи з 0, якщо не знайшов -1. Використовує хешування рядків
int find_substr(char substr[], char text[], int number_of_characters_to_analyze) {
	const int p = 31;
	long long p_pow[number_of_characters_to_analyze];
	p_pow[0] = 1;
	for (int i = 1; i < number_of_characters_to_analyze; i++) {
		p_pow[i] = p_pow[i-1] * p;
	}
	int i, length_of_substr = 0;
	long long hash_substr = 0;
	for(i = 0; substr[i] != '\0'; i++) {
		if (i+1 > number_of_characters_to_analyze) return -1;
		hash_substr += (substr[i] - '0' + 1) * p_pow[i];
		length_of_substr++;
	}
	long long prefix_hash_text[number_of_characters_to_analyze];
	for (i = 0; i < number_of_characters_to_analyze; i++) {
		prefix_hash_text[i] = (text[i] - '0' + 1) * p_pow[i];
		if (i != 0) prefix_hash_text[i] += prefix_hash_text[i-1];
	}
	for (i = 0; i < number_of_characters_to_analyze - length_of_substr + 1; i++) {
		long long current_hash = prefix_hash_text[i+length_of_substr-1];
		if (i != 0) current_hash -= prefix_hash_text[i-1];
		if (current_hash == hash_substr * p_pow[i]) {
			return i;
		}
	}
	return -1;
}
int main() {
	/*
	char s1[50002], s2[50002];
	cin.getline(s1,50001);
	cin.getline(s2,50001);
	cout << find_substr(s1,s2,strlen(s2));
	*/
}
