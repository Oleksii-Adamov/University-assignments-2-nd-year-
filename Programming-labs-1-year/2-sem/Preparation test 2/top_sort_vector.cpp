#include <bits/stdc++.h>
using namespace std;
vector<int> g[100001];
int used[100001];
vector<int> ans;
void dfs(int v) {
    used[v] = 2;
    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];
        if (used[u] == 0) {
            dfs(u);
        } else if (used[u] == 2) {
            cout << -1;
            exit(0);
        }
    }
    used[v] = 1;
    ans.push_back(v);
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int from,to;
        cin >> from >> to;
        g[from].push_back(to);
    }
    for (int i = 1; i <= n; i++) {
        if (used[i] == 0) {
            dfs(i);
        }
    }
    for (int i = ans.size()- 1; i>=0;i--)
        cout << ans[i] << " ";
}
