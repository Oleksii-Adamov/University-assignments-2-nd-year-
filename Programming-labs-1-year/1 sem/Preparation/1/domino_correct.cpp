//#include<iostream>
//using namespace std;
struct domino_tile {
	int first, second;
};
bool correct(domino_tile r[], int size) {
	for (int i = 0; i < size; i++) {
		if (i != 0 && r[i].first != r[i-1].second) return false;
	}
	return true;
}
int main() {
	/*
	int n;
	cin >> n;
	domino_tile* r = new domino_tile [n];
	for (int i = 0; i < n; i++) {
		cin >> r[i].first >> r[i].second;
	}
	cout << correct(r,n);
	delete[] r;
	*/
}
