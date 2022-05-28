///#include<iostream>
//using namespace std;
struct time{
	int hour, min, sec;
};
time back_25_sec(time input) {
	input.sec -= 25;
	if (input.sec < 0) {
		input.sec = 60 + input.sec;
		input.min--;
	}
	if (input.min < 0) {
		input.min = 60 + input.min;
		input.hour--;
	}
	if (input.hour < 0) {
		input.hour = 24 + input.hour;
	}
	return input;
}
int main() {
	/*
	time tim;
	cin >> tim.hour >> tim.min >> tim.sec;
	time res = back_25_sec(tim);
	cout << res.hour << " " << res.min << " " << res.sec << "\n";
	*/
}

