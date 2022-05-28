#include<iostream>
using namespace std;
struct Node {
	Node* left;
	Node* right;
	int data;
};
int max_val(Node* root) {
	Node* cur_node = root;
	while(cur_node->right != nullptr) cur_node = cur_node->right;
	return cur_node->data;
}
