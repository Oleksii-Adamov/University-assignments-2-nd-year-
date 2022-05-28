#include<iostream>
#include<queue>
#include<vector>
using namespace std;
struct Node {
	int data;
	Node* left;
	Node* right;
};
vector< vector<int> > level_order(Node* root) {
	vector< vector<int> > ans;
	queue<pair<int, Node* >> q;
	q.push({ 0, root });
	while (!q.empty()) {
		pair<int, Node* > now = q.front();
		int index = now.first;
		Node* node = now.second;
		q.pop();
		if (index >= ans.size()) {
			vector<int> t;
			ans.push_back(t);
		}
		ans[index].push_back(node->data);
		if (node->left != nullptr) {
			q.push({ index + 1, node->left });
		}
		if (node->right != nullptr) {
			q.push({ index + 1, node->right });
		}
	}
	return ans;
}
void print_level_order(vector< vector<int> > ans) {
	cout << '[';
	for (int i = 0; i < ans.size(); i++) {
		cout << '[';
		for (int j = 0; j < ans[i].size(); j++) {
			cout << ans[i][j];
			if (j != ans[i].size() - 1) cout << ", ";
		}
		cout << ']';
		if (i != ans.size() - 1) cout << ", ";
	}
	cout << "]\n";
}
int main() {
	
}
