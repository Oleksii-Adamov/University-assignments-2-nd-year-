#include<iostream>
#include<cstring>
using namespace std;
const int MAX_COMMAND_SIZE = 10000, COUNT = 5;
struct Node {
	Node* left;
	Node* right;
	int data;
};
Node* merge_BST (Node* left_tree, Node* right_tree) {
	Node* cur_node = right_tree;
	while(cur_node->left != nullptr) {
		cur_node = cur_node->left;
	}
	cur_node->left = left_tree;
	return right_tree;
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
int main() {
	Node* roots[2];
	roots[0] = nullptr;
	roots[1] = nullptr;
	int i = 0;
    char command[MAX_COMMAND_SIZE];
    cin.getline(command, MAX_COMMAND_SIZE);
    while (strcmp(command, "quit") != 0 && i < 2) {
        if (strcmp(command, "ins") == 0) {
            int val;
            cin >> val;
            cin.clear();
            cin.ignore(MAX_COMMAND_SIZE, '\n');
            roots[i] = BST_insert(roots[i], val);
            cout << "\n";
            cout << "Tree:\n";
            print_tree(roots[i], 0);
            cout << "\n";
        }
        if (strcmp(command, "next") == 0) {
            i++;
        }
        cin.getline(command, MAX_COMMAND_SIZE);
    }
   print_tree(merge_BST(roots[0],roots[1]), 0); ;
}
