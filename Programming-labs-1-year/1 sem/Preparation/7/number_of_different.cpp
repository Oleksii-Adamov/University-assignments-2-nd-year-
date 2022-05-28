#include<iostream>
#include<algorithm>
using namespace std;
void copy_arr(int source[], int size, int dest[]) {
	for (int i = 0; i < size; i++) {
		dest[i] = source[i];
	}
}
int number_of_different(int arr[], int size) {
	if (size <= 0) return 0;
	int *sorted_arr = new int [size];
	int ans = 1;
	copy_arr(arr, size, sorted_arr);
	sort(sorted_arr, sorted_arr + size);
	for (int i = 1; i < size; i++) {
		if (sorted_arr[i] != sorted_arr[i-1]) ans++;
	}		
	delete[] sorted_arr;
	return ans;
}
int main() {
	int n;
	cin >> n;
	int *input = new int [n];
	for (int i = 0; i < n; i++) cin >> input[i];
	cout << number_of_different(input,n);
}
