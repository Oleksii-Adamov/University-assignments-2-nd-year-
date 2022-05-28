#include<iostream>
#include<cstring>
using namespace std;
struct Node {
	Node* left;
	Node* right;
	int data;
};
struct AVLdata {
	bool is_AVL;
	int height;
	int max_value;
	int min_value;
};
AVLdata get_AVLdata(Node* node) { 
		if (node == nullptr) {
		return {true,-1,0};
	}
	AVLdata left_avl_data = get_AVLdata(node->left);
	AVLdata right_avl_data = get_AVLdata(node->right);
	AVLdata cur_node;
	cur_node.is_AVL = left_avl_data.is_AVL && right_avl_data.is_AVL && (left_avl_data.height - right_avl_data.height < 1) &&
		(left_avl_data.height == -1 || node->data > left_avl_data.max_value) && (right_avl_data.height == -1 || node->data < right_avl_data.min_value);
	cur_node.height = max(left_avl_data.height, right_avl_data.height) + 1;
	if (left_avl_data.height == -1) cur_node.min_value = node->data;
	else cur_node.min_value = left_avl_data.min_value;
	if (right_avl_data.height == -1) cur_node.max_value = node->data;
	else cur_node.max_value = right_avl_data.max_value;
}
bool is_AVL(Node* root) {
	return get_AVLdata(root).is_AVL;
}
int main() {
	
}
