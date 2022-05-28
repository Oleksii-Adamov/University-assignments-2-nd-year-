#include<iostream>
#include<windows.h>
#include<set>
using namespace std;
int main() { 
    SetConsoleOutputCP(1251);
    cout << "Введіть N:\n";
	int n;
    cin >> n;
	cout << "Введіть масив:\n";
	int* a = new int [n];
	multiset<int> s;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		s.insert(a[i]);
	}
	int size = 0;
	for (int i = 0; i < n; i++) {
		if (s.count(a[i]) > 2) {
			size++;
			a[size-1] = a[i];	
		}
	}
	cout << "Розмір масиву " << size << "\n" << "Масив:\n";
	for (int i = 0; i < size; i++) {
		cout << a[i] << " ";
	}
	delete[] a;
}
