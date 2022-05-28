#include<iostream>
#include<cstring>
using namespace std;
struct Node {
	int data;
	Node* next;
	Node* prev;
};
bool is_queue_empty(Node** front_ptr) {
	return (*front_ptr) == nullptr;
}
void push_back(Node** front_ptr, Node** back_ptr, int value) {
	Node* new_node = new Node;
	new_node->data = value;
	new_node->next = nullptr;
	if (is_queue_empty(front_ptr)) {
		new_node->prev = nullptr;
		*front_ptr = new_node;
	}
	else {
		new_node->prev = *back_ptr;
		(*back_ptr)->next = new_node;
	}
	*back_ptr = new_node;
}
void push_front(Node** front_ptr, Node** back_ptr, int value) {
	Node* new_node = new Node;
	new_node->data = value;
	new_node->prev = nullptr;
	if (is_queue_empty(front_ptr)) {
		new_node->next = nullptr;
		*back_ptr = new_node;
	} 
	else {
		new_node->next = *front_ptr;
		(*front_ptr)->prev = new_node;
	}
	*front_ptr = new_node;
}
void pop_front(Node** front_ptr, Node** back_ptr) {
	if (is_queue_empty(front_ptr)) {
		cout << "Queue is empty";
		exit(EXIT_FAILURE);
	}
	//int value;
	Node* temp = *front_ptr;
	//value = temp->data;
	*front_ptr = temp->next;		
	if (*front_ptr == nullptr)
		*back_ptr = nullptr;
	else 
		(*front_ptr)->prev = nullptr;
	delete temp;
	//return value;	
}
void pop_back(Node** front_ptr, Node** back_ptr) {
	if (is_queue_empty(front_ptr)) {
		cout << "Queue is empty";
		exit(1);
	}
	//int value;
	Node* temp = *back_ptr;
	//value = temp->data;
	*back_ptr = temp->prev;
	if (*back_ptr == nullptr)
		*front_ptr = nullptr;
	else 
		(*back_ptr)->next = nullptr;
	delete temp;
	//return value;
}
int main() {
	Node* front = nullptr;
	Node* back = nullptr;
	char command[20];
	cin >> command;
	while (strcmp(command,"exit") != 0) {
		if (strcmp(command,"push_back") == 0) {
			int value;
			cin >> value;
			push_back(&front,&back,value);
		}
		if (strcmp(command,"push_front") == 0) {
			int value;
			cin >> value;
			push_front(&front,&back,value);
		}
		if (strcmp(command,"pop_back") == 0) {
			if (is_queue_empty(&front)) 
				cout << "Queue is empty" << "\n";
			else {
				int value = back->data;
				pop_back(&front,&back);
				cout << value << "\n";
			}
		}
		if (strcmp(command,"pop_front") == 0) {
			if (is_queue_empty(&front)) 
				cout << "Queue is empty" << "\n";
			else {
				int value = front->data;
				pop_front(&front,&back);
				cout << value << "\n";
			}
		}
		cin >> command;
	}
}
