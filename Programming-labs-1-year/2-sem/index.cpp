#include<iostream>
using namespace std;
const int MODULE = 107;
struct Node {
	int data;
	int pos;
	Node* next;
};
// circular - index[mod] = last element in list
void build_index(Node* index[MODULE], int input[], int size_of_input) {
	for (int i = 0; i < MODULE; i++) {
		index[i] = nullptr;
	}
	for (int i = 0; i < size_of_input; i++) {
		int mod = input[i] % MODULE;
		if (index[mod] == nullptr) {
			index[mod] = new Node;
			index[mod]->data = input[i];
			index[mod]->pos = i;
			index[mod]->next = index[mod];
		}
		else {
			Node* new_Node = new Node;
			new_Node->data = input[i];
			new_Node->next = index[mod]->next;
			new_Node->pos = i;
			index[mod]->next = new_Node;
			index[mod] = new_Node;
		}
	}
}
void search(Node* index[MODULE], int value) {
	Node* last = index[value%MODULE];
	Node* cur_Node = last->next;
	do {
		if (cur_Node->data == value) {
			cout << cur_Node->pos << " ";
			break;
		}
		cur_Node = cur_Node->next;
	} while (cur_Node != last->next);
}
int main() {
	Node* index[MODULE];
	int input[10];
	for (int i = 0; i < 10; i++) {
		cin >> input[i];
	}
	build_index(index, input, 10);
	int val;
	while (cin >> val) {
		if (val == 0) break;
		search(index, val);
	}
}
