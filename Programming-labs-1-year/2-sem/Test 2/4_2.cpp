#include<iostream>
#include<queue>
using namespace std;
struct Tree_node {
	int data;
	Tree_node* left;
	Tree_node* right;
};
struct list_node {
	list_node* next;
	Tree_node* data;
};
struct list {
	list* next;
	list_node* last;
};
// circular list
void insertInEmpty(list_node*& last, Tree_node* new_data)
{
	if (last != nullptr) return;
	list_node* new_Node = new list_node;
	new_Node->data = new_data;
	last = new_Node;
	last->next = last;
}
void push_back(list_node*& last, Tree_node* new_data)
{
	if (last == nullptr) {
		insertInEmpty(last, new_data);
		return;
	}
	list_node* new_Node = new list_node;
	new_Node->data = new_data;
	new_Node->next = last->next;
	last->next = new_Node;
	last = new_Node;
}
struct queue_data {
	list* cur_list;
	Tree_node* node;
};
list level_order(Tree_node* root, list* cur_list) {
	queue<queue_data> q;
	q.push(root); 
	list* cur_list;
 	while (!q.empty()) {
		queue_data now = q.front();
		q.pop();
		if (now.cur_list == nullptr) {

		}
		push_back(now.cur_list->last, now.node);
		if (now.node->left != nullptr) {
			q.push({ now.cur_list->next, now.node->left });
		}
		if (now.node->right != nullptr) {
			q.push({ now.cur_list->next, now.node->right });
		}
	}
}
