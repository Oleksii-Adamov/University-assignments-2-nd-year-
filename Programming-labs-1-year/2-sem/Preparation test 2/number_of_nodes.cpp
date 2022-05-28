#include<iostream>
using namespace std;
struct Node {
	Node* left;
	Node* right;
	int data;
};
int number_of_nodes(Node* node) {
	if (node == nullptr) return 0;
	return number_of_nodes(node->left) + number_of_nodes(node->right) + 1;
}
int main() {
	
}
