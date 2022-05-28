#include<iostream>
#include<cstring>
using namespace std;
struct Node {
	int data;
	Node* next;
};
bool is_queue_empty(Node* front) {
	return front == nullptr;
}
void push(Node*& front, Node*& back, int value) {
	Node* new_node = new Node;
	new_node->data = value;
	new_node->next = nullptr;
	if (is_queue_empty(front)) {
		front = new_node;
	}
	else {
		back->next = new_node;
	}
	back = new_node;
}
int pop(Node*& front, Node*& back) {
	if (is_queue_empty(front)) {
		cout << "ERROR - queue is empty";
		return -1;
	}
	Node* temp = front;
	int data = temp->data;
	front = temp->next;
	if (front == nullptr) {
		back = nullptr;
	}
	delete temp;
	return data;
}
void print_queue(Node*& front) {
	if (is_queue_empty(front)) {
		cout << "Queue is empty\n";
		return;
	}
	Node* cur_node = front;
	while (cur_node != nullptr) {
		cout << cur_node->data << " ";
		cur_node = cur_node->next;
	}
}
void delete_queue(Node*& front) {
	if (is_queue_empty(front)) return;
	Node* cur_node = front;
	while (cur_node != nullptr) {
		Node* temp = cur_node;
		cur_node = cur_node->next;
		delete temp;
	}
}
int main() {
	Node* front = nullptr;
	Node* back = nullptr;
	char command[20];
	cin >> command;
	while (strcmp(command,"exit") != 0) {
		if (strcmp(command,"push") == 0) {
			int value;
			cin >> value;
			push(front,back,value);
		}
		if (strcmp(command,"pop") == 0) {
			if (is_queue_empty(front)) 
				cout << "Queue is empty" << "\n";
			else {
				cout << pop(front,back) << "\n";
			}
		}
		cin >> command;
	}
}

