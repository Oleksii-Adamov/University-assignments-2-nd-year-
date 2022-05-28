#include<iostream>
#include<cstring>
using namespace std;
bool used_char[128];
int main() {
	char s[256], t[256];
	cin >> s >> t;
	// контатенація
	char* result = new char [strlen(s)+strlen(t)+1];
	strcpy(result,s);
	strcat(result,t);
	cout << result << "\n";
	delete[] result;
	for (int i = 0; i < strlen(t); i++) {
		used_char[t[i]] = true; 
	}
	int i = 0;
	while (i < strlen(s)) {
		//cout << s << "\n";
		if(used_char[s[i]]) {
			memmove(&s[i], &s[i + 1], strlen(s) - i);
			i--;
		}
		i++;
	}
	cout << s << " " << strlen(s) << "\n";
	cout << t << " " << strlen(t) << "\n"; 
}
