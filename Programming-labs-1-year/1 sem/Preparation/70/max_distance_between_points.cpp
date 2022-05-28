//#include<iostream>
#include<math.h>
//using namespace std;
struct point {
	double x, y;
};
struct answer {
	point a, b;
	double dist;
};
double distance_between_points(point a, point b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
answer max_distance_between_points(point a[], int size_a, point b[], int size_b) {
	answer ans;
	ans.dist = 0.0;
	for (int i = 0; i < size_a; i++) {
		for (int j = 0; j < size_b; j++) {
			double cur_dist = distance_between_points(a[i],b[j]);
			if (cur_dist > ans.dist) {
				ans.dist = cur_dist;
				ans.a = a[i];
				ans.b = b[j];
			}
		}
	}
	return ans;
}
int main() {
	/*
	int n, m;
	cin >> n;
	point *a = new point [n];
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
	} 
	cin >> m;
	point *b = new point [m];
	for (int i = 0; i < m; i++) {
		cin >> b[i].x >> b[i].y;
	}
	answer ans = max_distance_between_points(a,n,b,m);
	cout << ans.dist << " (" << ans.a.x << ", " << ans.a.y << ") (" << ans.b.x << ", " << ans.b.y << ')';
	*/
}
