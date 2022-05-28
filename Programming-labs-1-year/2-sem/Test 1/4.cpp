#include <map>
#include <iostream>
using namespace std;
struct Node {
	Node* next;
};
int find_cycle(Node* head) {
	Node* cur_node = head;
	map<Node*, int> mp;
	map<Node*, int>::iterator it;
	int i = 1;
	while (cur_node != nullptr) {
		it = mp.find(cur_node);
		if (it != mp.end()) {
			return it->second;
		}
		else {
			mp[cur_node] = i;
		}
		cur_node = cur_node->next;
		i++;
	}
	mp.clear();
	return 0; // not found
}
void init(int n, Node** head_ptr, int cycle_begin) {
	if (n > 0) {
		*head_ptr = new Node;
		Node* prev_node = *head_ptr, * cycle = nullptr;
		if (cycle_begin == 1) cycle = *head_ptr;
		for (int i = 2; i <= n; i++) {
			Node* new_node = new Node;
			if (i == cycle_begin) {
				cycle = new_node;
			}
			prev_node->next = new_node;
			prev_node = new_node;
		}
		prev_node->next = cycle;
	}
}
int main() {
	Node* head = nullptr;
	int size, cycle_begin;
	cin >> size;
	if (size > 0) {
		cin >> cycle_begin;
		init(size, &head, cycle_begin);
	}
	cout << find_cycle(head);
}
