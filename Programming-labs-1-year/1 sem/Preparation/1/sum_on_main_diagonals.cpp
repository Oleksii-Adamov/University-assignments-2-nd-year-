#include<iostream>
using namespace std;
const int SIZE = 30;
int main() {
	double A[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cin >> A[i][j];
		}
	}
	double S[2*SIZE-1];
	int pos_in_s = 0;
	for (int i = SIZE - 1; i >= 0; i--, pos_in_s++) {
		double sum = 0;
		for (int j = 0; j < SIZE - i; j++) {
			sum+=A[i+j][j];
			//cout << A[i+j][j] << " ";
		}
		S[pos_in_s] = sum;
		//cout << "\n";
	}
	for (int j = 1; j < SIZE; j++, pos_in_s++) {
		double sum = 0;
		for (int i = 0; i < SIZE - j; i++) {
			sum+=A[i][j+i];
			//cout << A[i][j+i] << " ";
		} 
		S[pos_in_s] = sum;
		//cout << "\n";
	}
	for (int i = 0; i < 9; i++) cout << S[i] << " ";
}
