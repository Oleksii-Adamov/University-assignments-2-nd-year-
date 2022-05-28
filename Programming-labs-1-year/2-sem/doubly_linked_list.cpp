#include <iostream>
using namespace std;
struct Node {
	int data;
	Node* next, prev;
};
void insert_front(Node** head_ptr, int new_data)
{
	Node* newNode = new Node;
	newNode->data = new_data;
	newNode->next = *head_ptr;
	newNode->prev = nullptr;
	if ((*head_ptr) != nullptr)
		(*head_ptr)->prev = newNode;
	*head_ptr = newNode;
}
void insert_After(Node* prev_node, int new_data)
{
	if (prev_node == nullptr) {
		cout << "Previous node is required , it cannot be NULL";
		return;
	}
	Node* newNode = new Node;
	newNode->data = new_data;
	newNode->next = prev_node->next;
	prev_node->next = newNode;
	newNode->prev = prev_node;
	if (newNode->next != nullptr)
	newNode->next->prev = newNode;
}
void insert_end(Node** head_ptr, int new_data)
{
	Node* newNode = new Node;
	Node* last = *head_ptr;
	newNode->data = new_data;
	newNode->next = nullptr;
	if (*head_ptr == nullptr) {
		newNode->prev = nullptr;
		*head_ptr = newNode;
		return;
	}
	while (last->next != nullptr)
		last = last->next;
	last->next = newNode;
	newNode->prev = last;
}
void deleteNode(Node** head_ptr, Node* del) {
	if (*head_ptr == nullptr || del == nullptr) 
        return;
    if (*head_ptr == del) 
        *head_ptr = del->next; 
    if (del->next != nullptr) 
        del->next->prev = del->prev; 
    if (del->prev != nullptr) 
        del->prev->next = del->next; 
    delete del;
}
void reverseList(Node** head_ptr)
{
	Node* left = *head_ptr;
	Node* right = *head_ptr;
	while (right->next != nullptr)
	right = right->next;
	while (left != right && left->prev != right) {
	  swap(left->data, right->data);
	  left = left->next;
	  right = right->prev;
	}
}
int main() {
	
}
