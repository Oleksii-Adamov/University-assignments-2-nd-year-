#include<iostream>
#include<windows.h>
using namespace std;
const int MAX_STREAM_SIZE = 10000;
struct Worker {
 	int age;
 	char* name;
};
struct Node {
	Worker data;
	Node* next;
};
void insert_node(Node** head_ptr, Worker node_data) {
	Node* new_node = new Node;
	new_node->data = node_data;
	if (*head_ptr == nullptr) {
		new_node->next = nullptr;
		*head_ptr = new_node;
	}
	Node* cur_node = *head_ptr;
	while(cur_node->next != nullptr && cur_node->next->data.age < node_data.age) 
		cur_node = cur_node->next;
	new_node->next = cur_node->next;
	cur_node->next = new_node;
}
void delete_node(Node** head_ptr, Worker node_data) {
	Node* prev_node = *head_ptr;
	if (prev_node->data.name == node_data.name && prev_node->data.age == node_data.age) {
		*head_ptr = prev_node->next;
		return;
	}
	Node* cur_node = prev_node->next;
	while(cur_node->next != nullptr) {
		if (cur_node->data.name == node_data.name && cur_node->data.age == node_data.age) {
			prev_node->next = cur_node->next;
			delete cur_node;
			return;
		}
		cur_node = cur_node->next;
	}
}
void read_list_from_file(Node** head_ptr) {
	cout << "”каж≥ть формат файлу:\nb - б≥нарний\nt-текстовий\n";
	char format;
	cout << "¬вед≥ть назву файла\n";
	char* file_name;
	cin.getline(file_name,MAX_STREAM_SIZE,'\n');
	int size;
	cin >> size;
	for (int i = 0; i < size;i++) {
		Worker node_data;
		cin.getline(node_data.name,MAX_STREAM_SIZE,'\n');
		cin >> node_data.age;
		insert_node(head_ptr,node_data);
	}
}
void show_list(Node** head_ptr) {
	Node* cur_node = *head_ptr;
	while(cur_node != nullptr) {
		cout << cur_node->data.name << "\n" << cur_node->data.age << "\n=========================\n";
		cur_node = cur_node->next;
	}
}
void hint() {
	cout << "¬вед≥ть команду(ins - добавити, del - видалити), повне ≥м'€ роб≥тника, та його в≥к в окремих р€дках. Ќаприклад:\n";
	cout << "ins\nOleksii Adamov\n18\n";
	cout << "ўоб зчитати список роб≥ник≥в з файлу, введ≥ть read, та отримайте ≥нструкц≥ю, що робити дал≥\n";
	cout << "ўоб записати список роб≥ник≥в у файл, введ≥ть write, та отримайте ≥нструкц≥ю, що робити дал≥\n";
	cout << "ўоб побачити список роб≥ник≥в, введ≥ть state\n";
	cout << "ўоб завершити роботу програми, введ≥ть exit\n";
	cout << "ўоб отримати цю п≥дказку знову, введ≥ть help\n";
}
int main() {
	SetConsoleOutputCP(1251);
	Node* head = nullptr;
	hint();
	char* command;
	cin.getline(command,MAX_STREAM_SIZE,'\n');
	while (command != "exit") {
		if (command == "help") hint();
		if (command == "read") read_list_from_file(&head);
		if (command == "ins" || command == "del") {
			Worker node_data; 
			cin.getline(node_data.name,MAX_STREAM_SIZE,'\n');
			cin >> node_data.age;
			if (command == "ins")
				insert_node(&head,node_data);
			else delete_node(&head,node_data);
		}
		if (command == "state") show_list(&head);
		cin.getline(command,MAX_STREAM_SIZE,'\n');
	}
}
