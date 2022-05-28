#include<bits/stdc++.h>
#include "windows.h"
using namespace std;
int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	int n,key,ans=0;
	cout << "Введіть розмір масиву" << "\n";
	cin >> n;
	vector<int> a(n+1);
	cout << "Введіть відсортований масив" << "\n";
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	cout << "Введіть значення шукаємого елементу" << "\n";
	cin >> key;
	int r = n, l=1;
	while(r - l > 0) {
		int mid = (r+l)/2;
		cout << l << " " << r << "\n";
		if (a[mid] < key) {
			l = mid+1;
		}
		else {
			r = mid;
		}
	}
	if (a[l] == key) {
		ans = l;
	}
	else if (a[r] == key) {
		ans = r;
	}
	if (ans == 0) {
		cout << "Шукаємого елементу немає в масиві";
	}
	else cout << "Шукаємий елемент знаходиться у позиціїї (нумерація з 1) " << ans;
}
