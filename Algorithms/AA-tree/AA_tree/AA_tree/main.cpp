#include "AA_tree.h"
#include <fstream>
#include <iostream>
int main() {
	AA_tree tree;
	while (true) {
		std::string command;
		Complex_num value;
		std::cin >> command;
		if (command == "exit") {
			break;
		}
		std::cin >> value;
		if (command == "ins") {
			if (value == Complex_num(5,0)) {
				std::cout << "debug" << std::endl;
			}
			tree.insert(value);
			tree.print();
		}
		if (command == "del") {
			tree.del(value);
			tree.print();
		}
	}
	/*
	input
	ins (30, 2)
	ins (70, 0)
	ins (15, 4)
	ins (85, 7)
	ins (90, 1)
	ins (80, 0)
	ins (50, 50)
	del (50, 50)
	exit
	*/
}