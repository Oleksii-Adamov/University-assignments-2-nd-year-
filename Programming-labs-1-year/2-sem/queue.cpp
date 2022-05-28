#include<iostream>
#include<cstring>
using namespace std;
struct Node {
	int data;
	Node* next;
};
bool is_queue_empty(Node** front_ptr) {
	return (*front_ptr) == nullptr;
}
void push(Node** front_ptr, Node** back_ptr, int value) {
	if (front_ptr == nullptr || back_ptr == nullptr) {
		cout << "ERROR\n";
		return;
	}
	Node* new_node = new Node;
	new_node->data = value;
	new_node->next = nullptr;
	if (is_queue_empty(front_ptr)) {
		*front_ptr = new_node;
	}
	else {
		(*back_ptr)->next = new_node;
	}
	*back_ptr = new_node;
}
void pop(Node** front_ptr, Node** back_ptr) {
	if (front_ptr == nullptr || back_ptr == nullptr) {
		cout << "ERROR\n";
		return;
	}
	if (is_queue_empty(front_ptr)) {
		cout << "ERROR - queue is empty";
		return;
	}
	Node* temp = *front_ptr;
	if (temp->next != nullptr) {
		*front_ptr = temp->next;	
	}
	else {
		*front_ptr = nullptr;
		*back_ptr = nullptr;
	}
	delete temp;
}
void print_queue(Node** front_ptr) {
	if (front_ptr == nullptr) {
		cout << "ERROR\n";
		return;
	}
	if (*front_ptr == nullptr) {
		cout << "Queue is empty\n";
		return;
	}
	Node* cur_node = *(front_ptr);
	while (cur_node != nullptr) {
		cout << cur_node->data << " ";
		cur_node = cur_node->next;
	}
}
void delete_queue(Node** front_ptr) {
	if (front_ptr == nullptr) {
		cout << "ERROR\n";
		return;
	}
	if (*front_ptr == nullptr) return;
	Node* cur_node = *(front_ptr);
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
			push(&front,&back,value);
		}
		if (strcmp(command,"pop") == 0) {
			if (is_queue_empty(&front)) 
				cout << "Queue is empty" << "\n";
			else {
				int value = front->data;
				pop(&front,&back);
				cout << value << "\n";
			}
		}
		cin >> command;
	}
}

