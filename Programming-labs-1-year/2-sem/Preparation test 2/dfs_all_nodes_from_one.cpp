#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000;
struct Node {
	int v;
	Node *next;
};
void push_back(struct Node*& head, int node_data)
{
	Node* newNode = new Node;
	Node* last = head;
	newNode->data = node_data;
	newNode->next = nullptr;
	if (head == nullptr) {
		head = newNode;
		return;
	}
	while (last->next != nullptr)
		last = last->next;
	last->next = newNode;
	return;
}
Node* graph[MAXN];
bool used[MAXN];
int dfs(int v) {
	int ans = 0;
	used[v] = true;
	Node* cur_node = graph[v];
	while(cur_node != nullptr) {
		if (!used[cur_node->v]) {
			ans += dfs(cur_node->v);
		}
		cur_node = cur_node->next;
	}
	ans++;
	return ans;
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int from, to;
		cin >> from >> to;
		push_back(graph[from],to);
	}
	for (int i = 1; i <= n; i++) {
		if (!used[i]) {
			int p = dfs(i);
		}
	}
}
