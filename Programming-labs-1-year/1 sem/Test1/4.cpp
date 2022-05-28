#include<iostream>
#include<windows.h>
#include<set>
using namespace std;
int main() { 
    SetConsoleOutputCP(1251);
	int n,m, ans = 0;
	cout << "Введіть N і M\n";
    cin >> n >> m;
	cout << "Введіть матрицю:\n";
	for (int i = 0; i < n; i++) {
		set<int> s;
		bool flag = true;
		for (int j = 0; j < m; j++) {
			int a;
			cin >> a;
			if (flag) {
				if (s.count(a) > 0) {
					flag = false;
				}
				else {
					s.insert(a);
				}
			}
		}
		if (flag)
			ans++;
	}
	cout << "Кількість різних елементів " << ans;
}
