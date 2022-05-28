#include <bits/stdc++.h>
using namespace std;
const int INF = 1000;
int main() {
	int n,s,f;
	cin >> n >> s >> f; 
	s--;
	vector < vector < pair<int,int> > > g (n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int a;
			cin >> a;
			if (a!=-1) {
				 pair <int,int> temp = make_pair(j,a);
				 g[i].push_back(temp);
			}
		}
	}
	vector<int> d (n, INF),  p (n);
	d[s] = 0;
	vector<bool> u (n);
	for (int i=0; i<n; i++) {
		int v = -1;
		for (int j=0; j<n; j++)
			if (!u[j] && (v == -1 || d[j] < d[v]))
				v = j;
		if (d[v] == INF)
			break;
		u[v] = true;
		for (size_t j=0; j<g[v].size(); j++) {
			int to = g[v][j].first, len = g[v][j].second;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
			}
		}
	}
	if (d[f-1] == INF) {
		cout << -1;
		return 0;
	}
	vector<int> path;	
	for (int v = f - 1; v!=s; v=p[v])
	path.push_back (v);
	path.push_back (s);
	reverse (path.begin(), path.end());
	for (int i = 0; i < path.size(); i++) {
		cout << path[i] + 1 << " ";
	}
	return 0;
}
