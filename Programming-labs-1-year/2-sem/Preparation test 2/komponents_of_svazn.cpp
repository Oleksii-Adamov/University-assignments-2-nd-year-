#include <iostream>
using namespace std;
const int MAXN = 100005;
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
	int power;
	Node* last;
};
graph g[MAXN], k[MAXN];
long long n, m, i, j, d, f, o, p[100005], r[100005];

void dfs(long long v) {
	long long j;
	p[v] = 1;
	r[o]++;
	push_back(k[o].last, v);
	if (g[v].last == nullptr) return; 
	Node* cur_node = g[v].last->next;
	do {
		int v = cur_node->data;
		if (!p[v]) {
			dfs(v);
		}
		cur_node = cur_node->next;
	} while (cur_node != g[v].last->next);
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		g[i].power = 0;
	}
	for (i = 1; i <= m; i++) {
		cin >> d >> f;
		push_back(g[d].last, f);
		g[d].power++;
		push_back(g[f].last, d);
		g[f].power++;
	}
	for (int i = 1; i <= n; i++) {
		cout << g[i].power << " ";
	}
	cout << "\n";
	for (i = 1; i <= n; i++) {
		if (p[i] == 0) {
			o++;
			dfs(i);
		}
	}
	cout << o << endl;
	for (i = 1; i <= o; i++) {
		cout << r[i] << endl;
		Node* cur_node = k[i].last->next;
		do {
			cout << cur_node->data << " ";
			cur_node = cur_node->next;
		} while (cur_node != k[i].last->next);
		cout << "\n";
	}
}
