//#include<iostream>
//using namespace std;
struct date {
	int day, month, year;
};
bool is_date_correct(date d) {
	if (d.year < 0 || d.month < 1 || d.month > 12) return false;
	int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (d.year % 400 == 0  || (d.year % 100 != 0 && d.year % 4 == 0)) {
		days[2]++;
	}
	if (d.day < 1 || d.day > days[d.month]) return false;
	return true;
}
int main() {
	/*
	date input;
	cin >> input.day >> input.month >> input.year;
	cout << is_date_correct(input);
	*/
}
