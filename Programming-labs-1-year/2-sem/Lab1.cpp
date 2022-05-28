/*
Створіть однобічно зв'язаний список робітників. Програма має меню, можливо додавати, видаляти робітників. 
При додаванні робітника у список він додається таким чином, що список робітників залишається впорядкованим відносно року народження робітника.
*/
#include<iostream>
#include<windows.h>
#include<cstring>
using namespace std;
const int MAX_NAME_SIZE = 256;
struct Date {
	int day, month, year;
};
struct Worker {
	Date date_of_birth;
	char name[MAX_NAME_SIZE];
};
struct Node {
	Worker data;
	Node* next;
};
bool is_date_correct(Date d) {
	if (d.year < 0 || d.month < 1 || d.month > 12) return false;
	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (d.year % 400 == 0 || (d.year % 100 != 0 && d.year % 4 == 0)) {
		days[2]++;
	}
	if (d.day < 1 || d.day > days[d.month]) return false;
	return true;
}
bool read_date(Date& d)
{
	char c;
	cin >> d.day >> c >> d.month >> c >> d.year;
	cin.clear();
	cin.ignore(10000,'\n');
	return is_date_correct(d);
}
void write_date(Date d) {
	if (d.day < 10) cout << '0';
	cout << d.day << '.';
	if (d.month < 10) cout << '0';
	cout << d.month << '.' << d.year;
}
int compare_date(Date x, Date y) { // <0 - <, =0 - ==, >0 - >
	if (x.year == y.year && x.month == y.month) return x.day - y.day;
	if (x.year == y.year) return x.month - y.month;
	return x.year - y.year;
}
bool is_equal_data(Worker x, Worker y) {
	return strcmp(x.name, y.name) == 0 && compare_date(x.date_of_birth, y.date_of_birth) == 0;
}
void insert_node(Node** head_ptr, Worker node_data) {
	Node* new_node = new Node;
	new_node->data = node_data;
	if (*head_ptr == nullptr || compare_date((*head_ptr)->data.date_of_birth, node_data.date_of_birth) > 0) {
		new_node->next = (*head_ptr);
		*head_ptr = new_node;
		return;
	}
	Node* cur_node = *head_ptr;
	while (cur_node->next != nullptr && compare_date(cur_node->next->data.date_of_birth, node_data.date_of_birth) < 0)
		cur_node = cur_node->next;
	new_node->next = cur_node->next;
	cur_node->next = new_node;
}
void delete_node(Node** head_ptr, Worker node_data) {
	if (*head_ptr == nullptr) return;
	Node* prev_node = *head_ptr;
	if (is_equal_data(prev_node->data, node_data)) {
		Node* tmp = prev_node->next;
		delete prev_node;
		*head_ptr = tmp;
		return;
	}
	Node* cur_node = prev_node->next;
	while (cur_node != nullptr) {
		if (is_equal_data(cur_node->data, node_data)) {
			prev_node->next = cur_node->next;
			delete cur_node;
			return;
		}
		prev_node = cur_node;
		cur_node = cur_node->next;
	}
}
void delete_all_nodes(Node** head_ptr) {
	Node* cur_node = *head_ptr;
	while (cur_node != nullptr) {
		Node* temp = cur_node->next;
		delete cur_node;
		cur_node = temp;
	}
	*head_ptr = nullptr;
}
void show_list(Node** head_ptr) {
	Node* cur_node = *head_ptr;
	if (cur_node == nullptr) {
		cout << "Порожній\n";
		return;
	}
	cout << "=========================\n";
	while (cur_node != nullptr) {
		cout << cur_node->data.name << "\n";
		write_date(cur_node->data.date_of_birth);
		cout << "\n=========================\n";
		cur_node = cur_node->next;
	}
}
void hint() {
	cout << "Введіть команду(ins - добавити, del - видалити), повне ім'я робітника (англійською), та його дату народження в окремих рядках. Наприклад:\n";
	cout << "ins\nOleksii Adamov\n18.01.2003\n";
	cout << "Щоб побачити список робіників, введіть state\n";
	cout << "Щоб видалити всіх робітників зі списку, введіть delete all\n";
	cout << "Щоб завершити роботу програми, введіть exit\n";
	cout << "Щоб отримати цю підказку знову, введіть help\n";
}
int main() {
	SetConsoleOutputCP(1251);
	Node* head = nullptr;
	hint();
	char command[MAX_NAME_SIZE];
	cin.getline(command, MAX_NAME_SIZE);
	while (strcmp(command, "exit") != 0) {
		if (strcmp(command,"help") == 0) hint();
		else if (strcmp(command, "ins") == 0 || strcmp(command, "del") == 0) {
			Worker node_data;
			cin.getline(node_data.name, MAX_NAME_SIZE);
			if (!read_date(node_data.date_of_birth)) {
				cout << "Неправильна дата\n";
			}
			else if (strcmp(command, "ins") == 0)
				insert_node(&head, node_data);
			else delete_node(&head, node_data);
		}
		else if (strcmp(command, "delete all") == 0) delete_all_nodes(&head);
		else if (strcmp(command, "state") == 0) show_list(&head);
		else cout << "Неправильна команда\n";
		cin.getline(command, MAX_NAME_SIZE);
	}
}
