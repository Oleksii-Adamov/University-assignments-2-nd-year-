#pragma once
#include "AA_tree_node.h"
#include "Complex_num.h"
#include <iostream>
class AA_tree
{
private:
	AA_tree_node* root = nullptr;
public:
	
	bool is_in(Complex_num key);
	void insert(Complex_num key);
	void del(Complex_num key);
	void print();
};

void AA_tree::insert(Complex_num key) {
	root = AA_tree_node::insert(root, key);
}

void AA_tree::del(Complex_num key) {
	root = AA_tree_node::del(root, key);
}

bool AA_tree::is_in(Complex_num key) {
	return AA_tree_node::is_in(root, key);
}

void AA_tree::print() {
	std::vector<std::stringstream> output;
	output.emplace_back();
	root->print(output, 0);
	for (std::size_t i = 0; i < output.size(); i++) {
		std::cout << output[i].str() << std::endl;
	}
	std::cout << std::endl;

}