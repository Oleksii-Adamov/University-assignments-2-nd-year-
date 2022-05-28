#include<iostream>
using namespace std;
struct Node {
	int data;
	Node* left;
	Node* right;
};
int calc_depth(Node* node) {
	if (node == nullptr) return -1;
	return max(calc_depth(node->left), calc_depth(node->right)) + 1;
}
int main() {

}
