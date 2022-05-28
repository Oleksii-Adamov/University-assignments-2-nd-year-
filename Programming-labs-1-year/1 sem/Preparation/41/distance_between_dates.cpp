#include<iostream>
using namespace std;
struct date {
	int day, month, year;
};
bool is_greater_date(date x, date y) {
	if (x.year == y.year && x.month == y.month) return x.day > y.day;
	if (x.year == y.year) return x.month > y.month;
	return x.year > y.year;
}
date distance_between_dates(date first, date second) {
	date ans;
	int days[13] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	// 0 = 12
	if (is_greater_date(first,second)) {
		date t = first;
		first = second;
		second = t;
	}
	ans.year = second.year - first.year;
	ans.month = second.month - first.month;
	if (ans.month < 0) {
		ans.year--;
		ans.month = 12 + ans.month;
	}
	ans.day = second.day - first.day;
	if (ans.day < 0) {
		ans.month--;
		ans.day = days[second.month - 1] + ans.day;
		if (second.month - 1 == 2 && (second.year%400 == 0  || (second.year%100 != 0 && second.year%4 == 0))) {
			ans.day++;	
		}
	}
	return ans;
}
int main() {
	date first, second;
	cin >> first.day >> first.month >> first.year;
	cin >> second.day >> second.month >> second.year;
	date ans = distance_between_dates(first,second);
	cout << ans.day << " " << ans.month << " " << ans.year;
}
