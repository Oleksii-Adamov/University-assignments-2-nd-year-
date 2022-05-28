#include<iostream>
bool is_stack_empty(int top) {
	return top < 0;
}
void push(int stack[], int size, int top, int data) {
	if (top >= size - 1) {
		cout << "Stack is full\n";	
		return;
	}
	top++;
	stack[top] = data;
}
int pop (int stack[], int size, int top) {
	if (is_stack_empty(top)) {
		cout << "Stack is empty\n";
		return -1;
	}
	int data = stack[top];
	top--;
	return data;
}
