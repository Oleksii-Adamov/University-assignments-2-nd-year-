#include<iostream>
#include<cstring>
#include<math.h>
using namespace std;
int main() {
	char d[50002];
	//cin.getline(d,50000);
	//scanf("%s",d);
	fgets(d,50000,stdin);
	int i;
	for (i = 0; d[i] != '\n'; i++) {
		if (!(d[i] >= '0' && d[i] <= '9')) {
			cout << "ERROR";
			return 1;
		}
	}
	int n = 0, size = i, mult = 1;
	for (i = size - 1; i >= 0; i--, mult*=10) {
		n += (d[i] - '0') * mult;
	}
	int size_of_bin = log2(n) + 2, pos = size_of_bin - 2;
	char bin[size_of_bin];
	while(n != 0) {
		bin[pos] = (n%2+'0');
		n/=2;
		pos--;
	}
	bin[size_of_bin-1] = '\0';
	cout << bin;
}
