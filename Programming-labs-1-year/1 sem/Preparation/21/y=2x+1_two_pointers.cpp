#include<iostream>
using namespace std;
void solve(int a[]) {
	int read_pos = 0, size = 1, write_pos = 1, count = 0;
	a[0] = 1;
	int p_y = 0, p_z = 0;
	for (int i = 1; i < 100; i++) {
		int y = 2*a[p_y] + 1, z = 3*a[p_z] + 1;
		if (y == z) {
			a[i] = y;
			p_y++;
			p_z++;
		}
		else if (y < z) {
			a[i] = y;
			p_y++;
		}
		else {
			a[i] = z;
			p_z++;
		}
	}
}
int main() {
	int a[100];
	solve(a);
	for (int i = 0; i < 100; i++) {
		cout << a[i] << "\n";
	}
}
