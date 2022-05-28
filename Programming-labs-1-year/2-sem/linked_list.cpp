#include <iostream>
using namespace std;
struct Node {
	int data;
	Node *next;
};
void insert_front(Node** head_ptr, int node_data)
{
	Node* newNode = new Node;
	newNode->data = node_data;
	newNode->next = *head_ptr;
	*head_ptr = newNode;
}
void insertAfter(Node* prev_node, int node_data)
{
	if (prev_node == nullptr) {
		cout << "the given previous node is required,cannot be NULL";
		return; 
	} 
	Node* newNode = new Node; 
	newNode->data = node_data;
	newNode->next = prev_node->next;
	prev_node->next = newNode;
}
void insert_end(struct Node** head_ptr, int node_data)
{
	Node* newNode = new Node;
	Node* last = *head_ptr;
	newNode->data = node_data;
	newNode->next = nullptr;
	if (*head_ptr == nullptr) {
		*head_ptr = newNode;
		return;
	}
	while (last->next != nullptr)
		last = last->next;
	last->next = newNode;
	return;
}
void deleteFirstNode(Node** head_ptr)
{
	if (*head_ptr == nullptr) return;
	Node* temp = *head_ptr;
	*head_ptr = temp->next;
	delete temp;
}
void deleteLastNode(Node** head_ptr)
{
	if (*head_ptr == nullptr) return;
	if ((*head_ptr)->next == nullptr) {
		Node* temp = *head_ptr;
		*head_ptr = nullptr;
		delete temp;
	}
	Node* second_last = *head_ptr;
	while (second_last->next->next != nullptr)
		second_last = second_last->next;
	delete (second_last->next);
	second_last->next = nullptr;
}
int main() {
	/*Node* top = nullptr;
	char command[20];
	cin >> command;
	while (strcmp(command,"exit") != 0) {
		if (strcmp(command,"insert_") == 0)
	}*/
}
