#include<iostream>
#include<cstring>
using namespace std;
struct TreeNode {
	TreeNode* left;
	TreeNode* right;
	int data;
};
struct StNode {
	TreeNode* data;
	StNode* next;
};
bool is_stack_empty(StNode* top) {
	return top == nullptr;
}
void st_push(StNode*& top, TreeNode* value) {
	StNode* new_node = new StNode;
	new_node->data = value;
	new_node->next = top;
	top = new_node;
}
void st_pop(StNode*& top) {
	if (is_stack_empty(top)) {
		cout << "Stack is empty";
		exit(1);
	}
	StNode* temp = top;
	top = temp->next;
	delete temp;
}
void symord(TreeNode* root) {
	StNode* top = nullptr;
	TreeNode* cur_node = root;
	while (!is_stack_empty(top) || cur_node != nullptr) {
		while(cur_node != nullptr) {
			st_push(top, cur_node);
			cur_node = cur_node->left;
		}
		cur_node = top->data;
		st_pop(top);
		cout << cur_node->data;
		cur_node = cur_node->right;
	}
}
int main() {
	
}
