#include <iostream>
#include<cmath>
using namespace std;
struct Node {
	int data;
	Node* next;
};
long long pow(int x, int n) {
	long long ret = 1;
	for (int i = 1; i <= n; i++) ret *= x;
	return ret;
}
void func(long long n, Node** head_ptr) {
	if (n < 0) {
		cout << "non-negative n required\n";
		return;
	}
	int number_of_digits;
	if (n != 0) {
		number_of_digits = int(log10(n)) + 1;
	}
	if (n == 0 || number_of_digits == 1) {
		(*head_ptr) = new Node;
		(*head_ptr)->data = n;
		(*head_ptr)->next = nullptr;
	}
	else {
		(*head_ptr) = new Node;
		(*head_ptr)->data = n / 10 % 10;
		Node* new_node = new Node;
		new_node->data = n % 10;
		(*head_ptr)->next = new_node;
		Node* prev_node = new_node;
		long long pow10 = pow(10, number_of_digits - 1);
		for (int i = 1; i <= number_of_digits - 2; i++) {
			Node* new_node = new Node;
			new_node->data = n / pow10 % 10;
			prev_node->next = new_node;
			prev_node = new_node;
			pow10 /= 10;
		}
		prev_node->next = nullptr;
	}
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
	Node* head = nullptr;
	int n;
	cin >> n;
	func(n, &head);
	traverse(head);
}
