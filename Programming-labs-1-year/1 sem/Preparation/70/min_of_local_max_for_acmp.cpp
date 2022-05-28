#include<iostream>
using namespace std;
struct element {
	double value;
	int index;
};
// ���� ����� ��������� �� ������� �������� ����� ����� ������
int find_min_of_local_max(double arr[], int size) {
	element min = {0.0,-1};
	int ans = 0;
	// ���� ����� ��������� �������� �� ���� ��������, ���� ���������� �������� � �������� -1, �� ����������� ��� ��, �� ������� �������� �� ��������
	for (int i = 1; i < size - 1; i++) {
		if (arr[i] > arr[i-1] && arr[i] > arr[i+1]) {
			if (min.index == -1 || arr[i] < min.value) {
				min.index = i;
				min.value = arr[i];
			}
			ans++;
		}
	}
	return ans;
}
int main() {
	int n = 100, m = 0;
	double *a = new double [n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i] == 0) break;
		m++;
	}
	cout << find_min_of_local_max(a,m);
	delete[] a;
}
