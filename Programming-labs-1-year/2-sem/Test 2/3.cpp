#include<iostream>
using namespace std;
struct Node {
	int data;
	Node* left;
	Node* right;
};
Node* reflection(Node* node) {
	if (node == nullptr) return node;
	Node* left_subtree = node->left;
	node->left = reflection(node->right);
	node->right = reflection(left_subtree);
	return node;
}
int main() {
	
}
