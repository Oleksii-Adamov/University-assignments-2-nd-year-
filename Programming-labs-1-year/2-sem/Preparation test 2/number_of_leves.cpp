#include<iostream>
using namespace std;
struct Node {
	Node* left;
	Node* right;
	int data;
};
int number_of_leaves(Node* node) {
	if (node == nullptr) return 0;
	if (node->left == nullptr && node->right == nullptr) return 1;
	return number_of_leaves(node->left) + number_of_leaves(node->right);
}
