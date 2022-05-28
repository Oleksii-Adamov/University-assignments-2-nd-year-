#include <bits/stdc++.h>
using namespace std;
const long long INF = 2009000999;
int main() {
	long long n,m,s;
	cin >> n >> m >> s; 
	vector < vector < pair<long long,long long> > > g (n);
	for (long long k = 1; k <= m; k++) {
		long long i,j,a;
		cin >> i >> j >> a;
		g[i].push_back(make_pair(j,a));
		g[j].push_back(make_pair(i,a));
	}
	vector<long long> d (n, INF),  p (n);
	d[s] = 0;
	set < pair<long long,long long> > q;
	q.insert (make_pair (d[s], s));
	while (!q.empty()) {
		long long v = q.begin()->second;
		q.erase (q.begin());
		for (size_t j=0; j<g[v].size(); ++j) {
			long long to = g[v][j].first,
				len = g[v][j].second;
			if (d[v] + len < d[to]) {
				q.erase (make_pair (d[to], to));
				d[to] = d[v] + len;
				q.insert (make_pair (d[to], to));
			}
		}
	}
	for (int i = 0; i < n; i++) {
		cout << d[i] << " ";
	}
	return 0;
}

