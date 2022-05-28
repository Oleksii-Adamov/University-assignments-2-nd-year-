#include<iostream>
using namespace std;
void solve(int a[]) {
	int read_pos = 0, size = 1, write_pos = 1, count = 0;
	a[0] = 1;
	bool used[100][2];
	for (int i = 0; i < 100; i++) {
		used[i][0] = false;
		used[i][1] = false;
	}
	int multiplier[2] = {2, 3};
	while (write_pos < 100) {
		int min_ind = read_pos - 1, min_mult = -1, min_res = -1;
		for (int j = read_pos; j < write_pos; j++) {
			for (int mult = 0; mult < 2; mult++) {
				count++;
				if (!used[j][mult]) {
					int now = multiplier[mult] * a[j] + 1;
					if (min_mult == -1 || now < min_res) {
						min_ind = j;
						min_mult = mult;
						min_res = now;
					}
				}
			}
		}
		if (a[write_pos-1] != min_res) {
			a[write_pos] = min_res;
			write_pos++;
		}	
		used[min_ind][min_mult] = true;
	}
}
int main() {
	int a[100];
	solve(a);
	for (int i = 0; i < 100; i++) {
		cout << a[i] << "\n";
	}
}
