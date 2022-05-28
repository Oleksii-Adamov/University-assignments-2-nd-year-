/*
Дано дві непусті черги. Елементи кожної з черг впорядковані за зростанням. Об'єднати черги в одну зі збереженням упорядкованості елементів.
*/
#include<iostream>
#include<cstring>
using namespace std;
const int MAX_COMMAND_SIZE = 10000;
struct Node {
	int data;
	Node* next;
};
void push(Node** front_ptr, Node** back_ptr, int value) {
	if (front_ptr == nullptr || back_ptr == nullptr) {
		cout << "ERROR\n";
		return;
	}
	Node* new_node = new Node;
	new_node->data = value;
	new_node->next = nullptr;
	if (*front_ptr == nullptr) {
		*front_ptr = new_node;
	}
	else {
		(*back_ptr)->next = new_node;
	}
	*back_ptr = new_node;
}
void push_all_next(Node** front_ptr, Node** back_ptr, Node* cur_node) {
	if (front_ptr == nullptr || back_ptr == nullptr) return;
	while (cur_node != nullptr) {
		push(front_ptr, back_ptr, cur_node->data);
		cur_node = cur_node->next;
	}
}
void merge(Node** q1_front_ptr, Node** q1_back_ptr, Node** q2_front_ptr, Node** q2_back_ptr, Node** res_q_front_ptr, Node** res_q_back_ptr) {
	if (q1_front_ptr == nullptr || q1_back_ptr == nullptr || q2_front_ptr == nullptr || q2_back_ptr == nullptr || res_q_front_ptr == nullptr || res_q_back_ptr == nullptr) {
		cout << "ERROR\n";
		return;
	}
	Node* q1_cur = nullptr, * q2_cur = nullptr;
	if (*q1_front_ptr == nullptr) {
		push_all_next(res_q_front_ptr, res_q_back_ptr, *(q2_front_ptr));
		return;
	}
	if (*q2_front_ptr == nullptr) {
		push_all_next(res_q_front_ptr, res_q_back_ptr, *(q1_front_ptr));
		return;
	}
	if (*q1_front_ptr != nullptr && *q2_front_ptr != nullptr) {
		q1_cur = *q1_front_ptr;
		q2_cur = *q2_front_ptr;
		while (q1_cur != nullptr && q2_cur != nullptr) {
			int new_data;
			if (q1_cur->data < q2_cur->data) {
				new_data = q1_cur->data;
				q1_cur = q1_cur->next;
			}
			else {
				new_data = q2_cur->data;
				q2_cur = q2_cur->next;
			}
			push(res_q_front_ptr, res_q_back_ptr, new_data);
		}
	}
	push_all_next(res_q_front_ptr, res_q_back_ptr, q1_cur);
	push_all_next(res_q_front_ptr, res_q_back_ptr, q2_cur);
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
	cout << "To push element into first queue, enter \"q1\" and value in next row\nTo push element into second queue, enter \"q2\" and value in next row\nTo merge enter \"merge\"\n";
	Node* q1_front = nullptr, * q1_back = nullptr, * q2_front = nullptr, * q2_back = nullptr, * res_q_front = nullptr, * res_q_back = nullptr;
	char command[MAX_COMMAND_SIZE];
	cin.getline(command, MAX_COMMAND_SIZE);
	while (strcmp(command, "merge") != 0) {
		if (strcmp(command, "q1") == 0) {
			int val;
			cin >> val;
			cin.clear();
			cin.ignore(MAX_COMMAND_SIZE, '\n');
			push(&q1_front, &q1_back, val);
		}
		if (strcmp(command, "q2") == 0) {
			int val;
			cin >> val;
			cin.clear();
			cin.ignore(MAX_COMMAND_SIZE, '\n');
			push(&q2_front, &q2_back, val);
		}
		cin.getline(command, MAX_COMMAND_SIZE);
	}
	merge(&q1_front, &q1_back, &q2_front, &q2_back, &res_q_front, &res_q_back);
	print_queue(&res_q_front);
	delete_queue(&q1_front);
	delete_queue(&q2_front);
	delete_queue(&res_q_front);
}
