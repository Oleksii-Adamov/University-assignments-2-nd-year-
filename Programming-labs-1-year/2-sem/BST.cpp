#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int MAX_COMMAND_SIZE = 10000, COUNT = 5;
struct Node {
	Node * left, * right;
	int data;
};
void print_tree(Node* root, int space)
{
    if (root == NULL)
        return;
    space += COUNT;
    print_tree(root->right, space);
    cout << "\n";
    for (int i = 0; i < space - COUNT; i++) cout << " ";
    cout << root->data << "\n";
    print_tree(root->left, space);
}
Node* BST_find(Node* root, int key) {
	if (root == nullptr || root->data == key) return root;
	else if (root->data < key) BST_find(root->left, key);
	else  BST_find(root->right, key);
}
Node* BST_insert(Node* root, int ins_val) {
	if (root == nullptr) {
		Node* new_node = new Node;
		new_node->data = ins_val;
		new_node->left = nullptr;
		new_node->right = nullptr;
		return new_node;
	}
	if (ins_val < root->data) {
		root->left = BST_insert(root->left, ins_val);
	}
	if (ins_val > root->data) {
		root->right = BST_insert(root->right, ins_val);
	}
	return root;
}
void BST_traversal(Node* root) {
	if (root == nullptr) return;
	BST_traversal(root->left);
	cout << root->data << " ";
	BST_traversal(root->right);
}
Node* BST_delete(Node* root, int key) {
	if (root == nullptr) return root;
	if (key < root->data) {
		root->left = BST_delete(root->left, key);
	}
	else if (key > root->data) {
		root->right = BST_delete(root->right, key);
	}
	else {
		if (root->left == nullptr && root->right == nullptr) {
			delete root;
			return nullptr;
		}
		else if (root->left == nullptr) {
			Node* right_child = root->right;
			delete root;
			return right_child;
		}
		else if (root->right == nullptr) {
			Node* left_child = root->left;
			delete root;
			return left_child;
		}
		else {
			Node* next_greater = root->right, * next_greater_parent = root;
			while (next_greater->left != nullptr) {
				next_greater_parent = next_greater;
				next_greater = next_greater->left;
			}
			root->data = next_greater->data;
			if (next_greater_parent == root) {
				root->right = next_greater->right;
			}
			else {
				next_greater_parent->left = next_greater->right;
			}
			delete next_greater;
		}
	}
	return root;
}
int calc_depth(Node* node) {
	if (node == nullptr) return -1;
	return max(calc_depth(node->left), calc_depth(node->right)) + 1;
}
Node* reflection(Node* node) {
	if (node == nullptr) return node;
	Node* left_subtree = node->left;
	node->left = reflection(node->right);
	node->right = reflection(left_subtree);
	return node;
}
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
}
int main() {
	Node* root = nullptr;
    char command[MAX_COMMAND_SIZE];
    cin.getline(command, MAX_COMMAND_SIZE);
    while (strcmp(command, "quit") != 0) {
        if (strcmp(command, "ins") == 0) {
            int val;
            cin >> val;
            cin.clear();
            cin.ignore(MAX_COMMAND_SIZE, '\n');
            root = BST_insert(root, val);
            cout << "\n";
            cout << "Tree:\n";
            print_tree(root, 0);
            cout << "\n";
        }
        if (strcmp(command, "delete") == 0) {
            int val;
            cin >> val;
            cin.clear();
            cin.ignore(MAX_COMMAND_SIZE, '\n');
            root = BST_delete(root, val);
			cout << "\n";
            cout << "Tree:\n";
            print_tree(root, 0);
            cout << "\n";
        }
        if (strcmp(command, "refl") == 0) {
        	root = reflection(root);
        	cout << "Tree:\n";
            print_tree(root, 0);
            cout << "\n";
		}
        if (strcmp(command, "dep") == 0) {
            cout << calc_depth(root) << "\n";
		}
		if (strcmp(command, "lev") == 0) {
            vector< vector<int> > ans = level_order(root);
            for (int i = 0; i < ans.size(); i++) {
            	cout << '[';
            	for (int j = 0; j < ans[i].size(); j++) {
            		cout << ans[i][j] << " ";
				}
				cout << "]\n";
			}
		}
        cin.getline(command, MAX_COMMAND_SIZE);
    }
}
