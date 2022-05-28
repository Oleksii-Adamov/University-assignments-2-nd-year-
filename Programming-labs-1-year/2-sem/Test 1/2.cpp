#include <iostream>
using namespace std;
struct Node {
	int data;
	Node* next;
};
bool is_list_in_list(Node* head1, Node* head2) {
	if (head2 == nullptr) { // every list contains empty list
		return true;
	}
	Node* cur_node = head1;
	while (cur_node != nullptr) {
		bool flag = true;
		if (cur_node->data == head2->data) {
			flag = false;
			Node* cur_node2 = head2;
			while (cur_node != nullptr && cur_node2 != nullptr && cur_node->data == cur_node2->data) {
				cur_node = cur_node->next;
				cur_node2 = cur_node2->next;
			}
			if (cur_node2 == nullptr) return true;
		}
		if (flag) cur_node = cur_node->next;
	}
	return false;
}
void traverse(Node* head) {
	Node* cur_node = head;
	while (cur_node != nullptr) {
		cout << cur_node->data << " ";
		cur_node = cur_node->next;
	}
	cout << "\n";
}
void read(int n, Node** head_ptr) {
	int a;
	if (n > 0) {
		cin >> a;
		Node* new_node = new Node;
		new_node->data = a;
		*head_ptr = new_node;
		Node* prev_node = *head_ptr;
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
}
int main() {
	Node* head1 = nullptr, * head2 = nullptr;
	int n, m;
	cin >> n;
	read(n, &head1);
	cin >> m;
	read(m, &head2);
	if (is_list_in_list(head1, head2)) cout << "YES\n";
	else cout << "NO\n";
}

