#include<iostream>
#include<cstring>
using namespace std;
struct Node {
	int data;
	Node* next;
};
bool is_stack_empty(Node* top) {
	return top == nullptr;
}
void push(Node*& top, int value) {
	Node* new_node = new Node;
	new_node->data = value;
	new_node->next = top;
	top = new_node;
}
void pop(Node*& top) {
	if (is_stack_empty(top)) {
		cout << "Stack is empty\n";
		return;
	}
	Node* temp = top;
	top = temp->next;
	delete temp;
}
int main() {
	Node* top = nullptr;
	char command[20];
	cin >> command;
	while (strcmp(command,"exit") != 0) {
		if (strcmp(command,"push") == 0) {
			int value;
			cin >> value;
			push(top,value);
		}
		if (strcmp(command,"pop") == 0) {
			if (is_stack_empty(top)) 
				cout << "Stack is empty" << "\n";
			else {
				int value = top->data;
				pop(top);
				cout << value << "\n";
			}
		}
		cin >> command;
	}
}
