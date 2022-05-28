#include<iostream>
using namespace std;
const int QSIZE = 5;
void enqueue(int circular_queue[], int size, int& front, int& back, int data) {
	if ((front == 0 && back == size - 1) || (front != 0 && back == front - 1)) {
		cout << "Queue is full\n";
		return;
	}
	if (front == -1) { // queue is empty
		front = 0;
		back = 0;
	}
	else if (back == size - 1) {
		back = 0;
	}
	else {
		back++;
	}
	circular_queue[back] = data;
}
int dequeue(int circular_queue[], int size, int& front, int& back) {
	if (front == -1) {
		cout << "Queue is empty\n";
		return -1;
	}
	int data = circular_queue[front];
	if (front == back) {
		front = -1;
		back = -1;
	}
	else if (front == size - 1) {
		front = 0;
	}
	else {
		front++;
	}
	return data;
}
void traverse_queue(int circular_queue[], int size, int front, int back) {
	if (front == -1) {
		cout << "Queue is empty\n";
		return;
	}
	if (front <= back) {
		for (int i = front; i <= back; i++) {
			cout << circular_queue[i] << " ";
		}
	}
	else {
		for (int i = front; i < size; i++) {
			cout << circular_queue[i] << " ";
		}
		for (int i = 0; i <= back; i++) {
			cout << circular_queue[i] << " ";
		}
	}
	cout << "\n";
}
int main() {
	int front = -1, back = -1, a[QSIZE];
	char command[20];
	cin >> command;
	while (strcmp(command, "exit") != 0) {
		if (strcmp(command, "push") == 0) {
			int value;
			cin >> value;
			enqueue(a, QSIZE, front, back, value);
			traverse_queue(a, QSIZE, front, back);
		}
		if (strcmp(command, "pop") == 0) {
			cout << dequeue(a, QSIZE, front, back) << "\n";
			traverse_queue(a, QSIZE, front, back);
		}
		cin >> command;
	}
}
