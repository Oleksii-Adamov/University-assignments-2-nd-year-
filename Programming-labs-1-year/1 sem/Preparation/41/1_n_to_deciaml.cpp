#include<iostream>
using namespace std;
struct division {
	int hole, rem;
};
void decimal (int n, char s[]) {
	s[0] = '.';
	int now = 1, i = 1, i_string = 1;
	division period[50001];
	int period_index;
	bool used[51];
	for (int j = 1; j < 51; j++) {
		used[j] = false;
	}
	period[0].rem = 1;
	used[1] = true;
	while(true) {
		now*=10;
		period[i].hole = now / n;
		period[i].rem = now % n;
		if (period[i].rem == 0) {
			period_index = i+1;
			period[i+1].hole = 0;
			i+=2;
			break;
		}
		if (used[period[i].rem]) {
			for (int j = 0; j < i; j++) {
				if (period[j].rem == period[i].rem) {
					period_index = j + 1;
					break;
				}
			}
			i++;
			break;
		}
		else {
			used[period[i].rem] = true;
		}
		now = period[i].rem;
		i++;
	}
	for (int j = 1; j < i; j++) {
		if (j == period_index) {
			s[i_string] = '*';
			i_string++;
		}
		s[i_string] = char(period[j].hole+'0');
		i_string++;
	}
	s[i_string] = '*';
	s[i_string+1] = '\0';
} 
int main() {
	int n;
	cin >> n;
	char s[50001];
	decimal(n,s);
	cout << s;
}
