#include<iostream>
using namespace std;
struct Node {
	Node* left;
	Node* right;
	int data;
};
int number_of_leaves_in_segment_in_binary_tree(Node* node, int left_border, int right_border) {
	if (node == nullptr) return 0;
	if (node->left == nullptr && node->right == nullptr) return node->data >= left_border && node->data <= right_border;
	return number_of_leaves_in_segment_in_binary_tree(node->left,left_border,right_border) + number_of_leaves_in_segment_in_binary_tree(node->right,left_border,right_border);
}
