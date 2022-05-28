//скал€рний добуток вектор≥в
#include <iostream>
using namespace std;
const int NSIZE = 10000, MSIZE = 10000 * 0.92, SIZE = 10000;

int main() {
	struct {
		int num;
		int val;  
	} m[MSIZE];
	int cur_pos = 0;
	for (int i = 0; i < SIZE; i++) {
		int input;
		cin >> input;
		if (input != 0) {
			cur_pos++;
			m[cur_pos].val = input;
			m[cur_pos].num = i;
		}
	}
	int m_size = cur_pos + 1, ans = 0;
	cur_pos = 0;
	for (int i = 0; i < NSIZE; i++) {
		int input;
		cin >> input;
		if (i == m[cur_pos].num) {
			ans+=input*m[cur_pos].val;
			cur_pos++;
		}
	}
	cout << ans;
}
