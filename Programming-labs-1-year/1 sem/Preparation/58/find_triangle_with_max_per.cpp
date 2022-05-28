#include<iostream>
#include<cmath>
using namespace std;
struct point {
	double x, y;
};
struct triangle {
	point fir, sec, thir;
	double per;
};
double dist(point a, point b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
triangle find_triangle_with_max_per(point points[], int size) {
	triangle ans;
	ans.per = 0;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			for (int k = j + 1; k < size; k++) {
				double per = dist(points[i],points[j]) + dist(points[j],points[k]) + dist(points[i],points[k]);
				if (per > ans.per) {
					ans.per = per;
					ans.fir = points[i];
					ans.sec = points[j];
					ans.thir = points[k];
				}
			}
		}
	}
	return ans;
}
int main() {
	int n;
	cin >> n;
	point *a = new point [n];
	for (int i = 0; i < n; i++) 
	{
		cin >> a[i].x >> a[i].y;
	}
	triangle ans = find_triangle_with_max_per(a,n);
	cout << ans.per << " (" << ans.fir.x << ", " << ans.fir.y << ") (" << ans.sec.x << ", " << ans.sec.y << ") (" << ans.thir.x << ", " << ans.thir.y << ')';
}
