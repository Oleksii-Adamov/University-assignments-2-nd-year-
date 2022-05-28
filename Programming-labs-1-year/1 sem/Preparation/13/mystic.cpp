#include<iostream>
using namespace std;
int main() {
	char s[50001];
	//cin.getline(s,50000);
	fgets(s,50000,stdin);
	/*for (int i = 0; s[i] != '\0'; i++) {
		cout << s[i];
	}*/
	cout << s;
}	
