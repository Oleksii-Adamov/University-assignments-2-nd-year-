#include <iostream>
using namespace std;
struct Node {
	int data;
	Node* next;
};
void invert(Node** head_ptr, Node** new_head_ptr) {
	if (head_ptr == nullptr || new_head_ptr == nullptr) {
		cout << "ERROR";
		exit(1);
	}
	if (*(head_ptr) == nullptr) {
		*new_head_ptr = nullptr;
		return;
	}
	Node* prev_node = *head_ptr;
	Node* cur_node = prev_node->next;
	Node* new_node = new Node;
	new_node->data = prev_node->data;
	new_node->next = nullptr;
	prev_node = new_node;
	while (cur_node != nullptr) {
		Node* new_node = new Node;
		new_node->data = cur_node->data;
		new_node->next = prev_node;
		prev_node = new_node;
		cur_node = cur_node->next;
	}
	*new_head_ptr = prev_node;
}
void traverse(Node* head) {
	Node* cur_node = head;
	while (cur_node != nullptr) {
		cout << cur_node->data << " ";
		cur_node = cur_node->next;
	}
	cout << "\n";
}
int main() {
	Node* head = nullptr, * new_head = nullptr;
	int n, a;
	cin >> n;
	if (n > 0) {
		cin >> a;
		Node* new_node = new Node;
		new_node->data = a;
		head = new_node;
		Node* prev_node = head;
		for (int i = 1; i < n; i++) {
			int a;
			cin >> a;
			Node* new_node = new Node;
			new_node->data = a;
			prev_node->next = new_node;
			prev_node = new_node;
		}
		prev_node->next = nullptr;
	}
	traverse(head);
	invert(&head, &new_head);
	traverse(new_head);
}
