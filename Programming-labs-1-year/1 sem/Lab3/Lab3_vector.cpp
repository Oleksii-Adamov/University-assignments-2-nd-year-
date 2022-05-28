// O(N^2)
#include<iostream>
#include<math.h>
#include<windows.h>
#include <vector>
using namespace std;
const double INF = 1.79769e+308;
struct point {
	double x;
	double y;
};
double dist(point a, point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
void dfs(int v, int n, const vector< vector<int> > &graph, vector<int> &points, bool used[]) {
	used[v] = true;
	points.push_back(v);
	for (int i = 0; i < graph[v].size(); i++) {
		if (!used[graph[v][i]]) {
			dfs(graph[v][i], n, graph, points, used);
		}
	}
}
int main() {
	SetConsoleOutputCP(1251);
	int n;
	cout << "Введіть кількість точок:\n";
	cin >> n;
	cout << "Введіть точки:\n";
	point* a = new point[n];
	vector< vector<int> > graph(n);
	bool* used = new bool[n];
	vector< vector<int> > group;
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
		used[i] = false;
	}
	for (int i = 0; i < n; i++) {
		double min_dist = INF;
		int  min_j = i;
		for (int j = 0; j < n; j++) {
			double d = dist(a[i], a[j]);
			if (i != j && d < min_dist) {
				min_dist = d;
				min_j = j;
			}
		}
		graph[i].push_back(min_j);
		graph[min_j].push_back(i);
	}
	int number_of_groups = 0;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			vector<int> temp;
			group.push_back(temp);
			dfs(i, n, graph, group[number_of_groups], used);
			number_of_groups++;
		}
	}
	cout << "Програма знайшла " << number_of_groups << " групи точок\n";
	for (int i = 0; i < number_of_groups; i++) {
		cout << i + 1 << '\n';
		for (int j = 0; j < group[i].size(); j++) {
			cout << '(' << a[group[i][j]].x << ',' << a[group[i][j]].y << ") ";
		}
		cout << '\n';
	}
	delete[] a;
	delete[] used;
}


/*
5
-5 -5
14 -6
13 11
105 122
163 135


6
8 5
8 2
6 2
6 4
10 3
10 4



11
-4 5
-4 7
-2 -3
-5 -5
2 9
3 7
4 8
4 -3
7 -2
5 -6
8 5




10
1 1
1 2
2 3
4 -2
7 1
4 -3
3 1
9 2
0 8
7 3
*/
