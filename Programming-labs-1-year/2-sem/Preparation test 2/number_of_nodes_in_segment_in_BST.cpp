#include<iostream>
using namespace std;
struct Node {
	Node* left;
	Node* right;
	int data;
};
int number_of_nodes_in_segment_in_BST(Node* node, int left_border, int right_border) {
	if (node == nullptr) return 0;
	int ans = 0;
	if (node->left != nullptr && node->data > left_border) ans += number_of_nodes_in_segment_in_BST(node->left, left_border, min(node->data - 1, right_border));
	if (node->right != nullptr && node->data < right_border) ans += number_of_nodes_in_segment_in_BST(node->right, max(node->data + 1, left_border), right_border);
	if (node->data >= left_border && node->data <= right_border) ans++;
	return ans;
}
