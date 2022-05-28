#include <iostream>
using namespace std;
struct Node {
	int data;
	Node* next;
};
void insertInEmpty(Node*& last, int new_data)
{
	if (last != nullptr) return;
	Node* new_Node = new Node;
	new_Node->data = new_data;
	last = new_Node;
	last->next = last;
}
void push_back(Node*& last, int new_data)
{
	if (last == nullptr) {
		insertInEmpty(last, new_data);
		return;
	}
	Node* new_Node = new Node;
	new_Node->data = new_data;
	new_Node->next = last->next;
	last->next = new_Node;
	last = new_Node;
}
struct graph {
	Node* last;
};
bool dfs(int v, graph g[], int key, bool used[]) {
	used[v] = true;
	if (v == key) return true;
	bool ans = false;
	if (g[v].last == nullptr) return false;
	Node* cur_node = g[v].last->next;
	do {
		int v = cur_node->data;
		if (!used[v]) {
			ans = ans || dfs(v, g, key, used);
		}
		cur_node = cur_node->next;
	} while (cur_node != g[v].last->next && !ans);
	return ans;
}
int main() {
	int n, m;
	cin >> n >> m;
	graph* g = new graph[n + 1];
	bool* used = new bool[n + 1];
	for (int i = 1; i <= n; i++) {
		g[i].last = nullptr;
		used[i] = false;
	}
	for (int i = 1; i <= m; i++) {
		int from, to;
		cin >> from >> to;
		push_back(g[from].last, to);
	}
	int v, u;
	cin >> v >> u;
	if (dfs(v, g, u, used)) cout << "Yes";
	else cout << "No";
}
