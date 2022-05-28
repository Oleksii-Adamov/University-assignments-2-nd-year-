// O(N^2)
#include<iostream>
#include<math.h>
#include<windows.h>
using namespace std;
const double INF = 1.79769e+308;
struct point {
	double x;
	double y;
};
double dist(point a, point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
void dfs(int v, int n, bool **graph, int points[], bool used[], int &depth) {
	used[v] = true;
	points[depth++] = v;
	for (int i = 0; i < n; i++) {
		if (!used[i] && graph[v][i]) {
			dfs(i,n,graph,points,used,depth);
			//break;
		}
	}
	/*if (!used[graph[v]])
		dfs(graph[v], n, graph, points, used, depth + 1);
		*/
}
int main() {
	SetConsoleOutputCP(1251);
	int n;
	cout << "Aaaa?ou e?eue?nou oi?ie:\n";
	cin >> n;
	cout << "Aaaa?ou oi?ee:\n";
	point* a = new point[n];
	bool **graph = new bool* [n];
	//bool** graph = (bool**) new bool[n][1];
	//int* graph = new int [n];
	bool* used = new bool[n];
	int** group = new int* [n];
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
		graph[i] = new bool[n];
		group[i] = new int [n];
		//graph[i] = -1;
		used[i] = false;
		for (int j = 0; j < n; j++) {
			graph[i][j] = false;
			group[i][j] = -1;
		}
	}
	for (int i = 0; i < n; i++) {
		//if (graph[i] != -1) continue;
		double min_dist = INF;
		int  min_j = n + 1;
		for (int j = 0; j < n; j++) {
			double d = dist(a[i], a[j]);
			if (i != j && d < min_dist) {
				min_dist = d;
				min_j = j;
			}
		}
		graph[i][min_j] = true;
		graph[min_j][i] = true;
		//graph[i] = min_j;
		//graph[min_j] = i;
	}
	cout << "Graph:/n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << graph[i][j] << " ";
		}
		cout << "\n";
		//cout << i << " " << graph[i] << "\n";
	}
	cout << "\n";
	int number_of_groups = 0, start_depth = 0;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i, n, graph, group[number_of_groups], used, start_depth);
			start_depth = 0;
			number_of_groups++;
		}
	}
	cout << "I?ia?aia ciaeoea " << number_of_groups << "a?oie oi?ie\n";
	for (int i = 0; i < number_of_groups; i++) {
		cout << i + 1 << '\n';
		int j = 0;
		while (group[i][j] != -1 && j < n) {
			cout << '(' << a[group[i][j]].x << ',' << a[group[i][j]].y << ") ";
			j++;
		}
		cout << '\n';
	}
	for (int i = 0; i < n; i++) {
		delete[] group[i];
	}
	delete[] group;
	delete[] a;
	delete[] graph;
	delete[] used;
}
