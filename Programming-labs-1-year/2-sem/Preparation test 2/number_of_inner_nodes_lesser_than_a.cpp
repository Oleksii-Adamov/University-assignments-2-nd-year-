#include<iostream>
using namespace std;
struct Node {
	Node* left;
	Node* right;
	int data;
};
int number_of_inner_nodes_lesser_that_a(Node* node, int a) {
	if (node == nullptr || (node->left == nullptr && node->right == nullptr)) return 0;
	int ans = 0;
	ans = number_of_inner_nodes_lesser_that_a(node->left,a) + number_of_inner_nodes_lesser_that_a(node->right,a);
	if (node->data < a) ans++;
	return ans;
}
