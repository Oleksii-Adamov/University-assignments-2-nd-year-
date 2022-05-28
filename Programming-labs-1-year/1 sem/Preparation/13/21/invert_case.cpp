//#include<iostream>
//using namespace std;
void invert_case(char s[]) {
	int i = 0, difference = 'a' - 'A';
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] += difference;
		}
		else if (s[i] >= 'a' && s[i] <= 'z') {
			s[i] -= difference;
		}
	} 
}
int main() {
	/*
	char s[50001];
	cin.getline(s,50001);
	invert_case(s);
	cout << s;
	*/
}
