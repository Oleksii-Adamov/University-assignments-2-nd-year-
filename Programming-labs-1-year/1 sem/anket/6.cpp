#include<bits/stdc++.h>
#include "windows.h"
using namespace std;
int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	vector<bool> prime(101,true);
	prime[1] = false;
	for (int i = 2; i <= 100; i++) {
		if (prime[i]) {
			cout << i << " ";
			for (int j = i*i; j <= 100; j+=i) {
				prime[j] = false;
			}
		}
	}
}
