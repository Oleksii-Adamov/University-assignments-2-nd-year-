#include<iostream>
#include<cstring>
using namespace std;
struct Node {
	int data;
	Node* next;
};
void insertInEmpty(Node** last_ptr, int new_data)
{
	if (*last_ptr != nullptr) return;
	Node* new_Node = new Node;
	new_Node->data = new_data;
	*last_ptr = new_Node;
	(*last_ptr)->next = *last_ptr;
}
void insertAtBegin(Node** last_ptr, int new_data)
{
	if (*last_ptr == nullptr) {
		insertInEmpty(last_ptr, new_data);
		return;
	}
	Node* new_Node = new Node;
	new_Node->data = new_data;
	new_Node->next = (*last_ptr)->next;
	(*last_ptr)->next = new_Node;
}
void insertAtEnd(Node** last_ptr, int new_data)
{
	if (*last_ptr == nullptr) {
		insertInEmpty(last_ptr, new_data);
		return;
	}
	Node* new_Node = new Node;
	new_Node->data = new_data;
	new_Node->next = (*last_ptr)->next;
	(*last_ptr)->next = new_Node;
	(*last_ptr) = new_Node;
}
void insertAfter(Node** last_ptr, int new_data, int after_item)
{
	if (*last_ptr == nullptr) return;
	Node* new_Node = new Node;
	new_Node->data = new_data;
	Node* cur_Node;
	cur_Node = (*last_ptr)->next;
	do
	{
		if (cur_Node->data == after_item)
		{
			new_Node->next = cur_Node->next;
			cur_Node->next = new_Node;
			if (cur_Node == *last_ptr)
				*last_ptr = new_Node;
			return;
		}
		cur_Node = cur_Node->next;
	} while (cur_Node != (*last_ptr)->next);
	cout << "The node with data " << after_item << " is not present in the list.\n";

}
void traverseList(Node* last) {
	if (last == nullptr) {
		cout << "Circular linked List is empty.\n";
		return;
	}
	Node* cur_Node;
	cur_Node = last->next;
	do {
		cout << cur_Node->data << "==>";
		cur_Node = cur_Node->next;
	} while (cur_Node != last->next);
	if (cur_Node == last->next) // возмиожно не нужно
		cout << cur_Node->data;
	cout << "\n\n";
}

//delete the node from the list
void deleteNode(Node** last_ptr, int key)
{
	if (*last_ptr == nullptr) return;
	Node* cur_Node = (*last_ptr)->next;
	Node* prev_Node = (*last_ptr);
	do {
		if (cur_Node->data == key) break;
		prev_Node = cur_Node;
		cur_Node = cur_Node->next;
	} while (cur_Node != (*last_ptr)->next);
	if (cur_Node->next == cur_Node) {
		*last_ptr = nullptr;
	}
	else if (cur_Node == (*last_ptr)) {
		prev_Node->next = cur_Node->next;
		(*last_ptr) = prev_Node;
	}
	else prev_Node->next = cur_Node->next;
	delete cur_Node;
}
int main() {
	Node* last = nullptr;
	char command[30];
	cin.getline(command, 30);
	while (strcmp(command, "exit") != 0) {
		if (strcmp(command, "show") == 0) {
			traverseList(last);
		}
		if (strcmp(command, "insertAfter") == 0) {
			int ins, key;
			cin >> ins >> key;
			insertAfter(&last, ins, key);
		}
		if (strcmp(command, "insertAtEnd") == 0) {
			int ins;
			cin >> ins;
			insertAtEnd(&last, ins);
		}
		if (strcmp(command, "insertAtBegin") == 0) {
			int ins;
			cin >> ins;
			insertAtBegin(&last, ins);
		}
		if (strcmp(command, "deleteNode") == 0) {
			int key;
			cin >> key;
			deleteNode(&last, key);
		}
		cin.getline(command, 30);
	}
}
