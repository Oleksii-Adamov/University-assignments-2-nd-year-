//#include<iostream>
#include<algorithm>
using namespace std;
struct two {
	int fir, sec;
};
struct element {
	double val;
	int ind;
};
bool cmp(element x, element y) {
	if (x.val == y.val) return x.ind < y.ind;
	return x.val < y.val;
	
}
two closest(double arr[], int size) {
	element *a = new element [size];
	for (int i = 0; i < size; i++) {
		a[i].val = arr[i];
		a[i].ind = i;
	}
	sort(a,a+size,cmp);
	two ans = {a[0].ind, a[1].ind};
	int mini = a[1].val - a[0].val;
	for (int i = 1; i < size - 1; i++) {
		int now = a[i+1].val - a[i].val;
		if (now < mini) {
			mini = now;
			ans = {a[i].ind, a[i+1].ind};
		}
	}
	return ans;
}
int main() {
	/*
	int n;
	cin >> n;
	double *a = new double [n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	two ans = closest(a,n);
	cout << ans.fir << " " << ans.sec; 
	*/
}
