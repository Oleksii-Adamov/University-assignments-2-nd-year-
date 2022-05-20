#pragma once
#include "Complex_num.h"
#include <vector>
#include <string>

struct AA_tree_node
{
	Complex_num key;
	unsigned int level;
	AA_tree_node* left;
	AA_tree_node* right;
	// leaf with key
	AA_tree_node(Complex_num key);
	bool is_leaf();
	static AA_tree_node* del(AA_tree_node* root, Complex_num key);
	static AA_tree_node* insert(AA_tree_node* root, Complex_num key);
	static bool is_in(AA_tree_node* root, Complex_num key);
	void print(std::vector<std::stringstream>& output, std::size_t row);
private:
	static AA_tree_node* skew(AA_tree_node* node);
	static AA_tree_node* split(AA_tree_node* node);
	static AA_tree_node* decrease_level(AA_tree_node* node);
	static AA_tree_node* predecessor(AA_tree_node* node);
	static AA_tree_node* successor(AA_tree_node* node);
	
};

#include<algorithm>

AA_tree_node::AA_tree_node(Complex_num key)
	: key(key), left(nullptr), right(nullptr), level(1)
{

}

bool AA_tree_node::is_leaf() {
	if (left == nullptr && right == nullptr) {
		return true;
	}
	else
		return false;
}

AA_tree_node* AA_tree_node::skew(AA_tree_node* node) {
	if (node == nullptr)
		return nullptr;
	if (node->left == nullptr)
		return node;
	if (node->left->level == node->level) {
		// Swap the pointers of horizontal left links.
		AA_tree_node* orig_left_node = node->left;
		node->left = orig_left_node->right;
		orig_left_node->right = node;
		return orig_left_node;
	}
	// if left child not on same level than no need to skew
	return node;
}

AA_tree_node* AA_tree_node::split(AA_tree_node* node) {
	if (node == nullptr)
		return nullptr;
	if (node->right == nullptr || node->right->right == nullptr)
		return node;
	if (node->level == node->right->right->level) {
		// Take the middle horizontal node, elevate it, and return it.
		AA_tree_node* middle_node = node->right;
		node->right = middle_node->left;
		middle_node->left = node;
		middle_node->level++;
		return middle_node;
	}
	// if no two horizontal links than no split needed
	return node;
}

AA_tree_node* AA_tree_node::insert(AA_tree_node* root, Complex_num key) {
	if (root == nullptr) {
		AA_tree_node* leaf = new AA_tree_node(key);
		return leaf;
	}
	if (key < root->key) {
		root->left = insert(root->left, key);
	}
	else if (key > root->key) {
		root->right = insert(root->right, key);
	}
	root = skew(root);
	root = split(root);
}

AA_tree_node* AA_tree_node::decrease_level(AA_tree_node* node) {
	if (node->left != nullptr && node->right != nullptr) {
		unsigned int should_be = std::min(node->left->level, node->right->level) + 1;
		if (should_be < node->level) {
			node->level = should_be;
			if (should_be < node->right->level) {
				node->right->level = should_be;
			}
		}
	}
	return node;
}

AA_tree_node* AA_tree_node::predecessor(AA_tree_node* node) {
	node = node->left;
	while (node->right != nullptr)
	{
		node = node->right;
	}
	return node;
}

AA_tree_node* AA_tree_node::successor(AA_tree_node* node) {
	node = node->right;
	while (node->left != nullptr)
	{
		node = node->left;
	}
	return node;
}

AA_tree_node* AA_tree_node::del(AA_tree_node* root, Complex_num key) {
	if (root == nullptr)
		return nullptr;
	if (key < root->key) {
		root->left = del(root->left, key);
	}
	else if (key > root->key) {
		root->right = del(root->right, key);
	}
	else {
		// if leaf
		if (root->is_leaf()) {
			delete root;
			return nullptr;
		}
		if (root->left == nullptr) {
			// find successor, swap values with it and delete it
			// as I think following AA-tree properties successor is always right node (because if there is left node to right node than 
			// root has to be not level 1, and so have left child which not the case
			// my implementation but I am not sure so it is commented and I will use default
			//root->key = root->right->key;
			//delete root->right;
			AA_tree_node* successor_node = successor(root);
			root->key = successor_node->key;
			root->right = del(root->right, successor_node->key);
		}
		else {
			// find predecessor, swap values with it and delete it
			AA_tree_node* predecessor_node = predecessor(root);
			root->key = predecessor_node->key;
			root->left = del(root->left, predecessor_node->key);
		}
	}
	root = decrease_level(root);
	root = skew(root);
	root->right = skew(root->right);
	if (root->right != nullptr)
		root->right->right = skew(root->right->right);
	root = split(root);
	root->right = split(root->right);
	return root;
}

bool AA_tree_node::is_in(AA_tree_node* root, Complex_num key) {
	if (root == nullptr) {
		return false;
	}
	if (root->key == key) {
		return true;
	}
	if (key < root->key) {
		return is_in(root->left, key);
	}
	if (key > root->key) {
		return is_in(root->right, key);
	}
}

void AA_tree_node::print(std::vector<std::stringstream>& output, std::size_t row) {
	if (left != nullptr) {
		if (output.size() == row + 1) {
			output.emplace_back();
			output[row + 1] << "|";
			output.emplace_back();
			left->print(output, row + 2);
		}
		else {
			while (output[row + 1].str().size() < output[row].str().size() - 1)
			{
				output[row + 1] << ' ';
			}
			output[row + 1] << '|';
			while (output[row + 2].str().size() < output[row + 1].str().size() - 1)
			{
				output[row + 2] << ' ';
			}
			left->print(output, row + 2);
		}
		std::stringstream ss;
		ss << '(' << left->key.real() << "," << left->key.imag() << ')';
		std::size_t left_child_string_size = ss.str().size() + 2;
	}
	output[row] << '(' << key.real() << "," << key.imag() << ')';
	if (right != nullptr && right->level == level) {
		while (output[row].str().size() < output[output.size() - 1].str().size())
		{
			output[row] << '-';
		}
		output[row] << "---";
		right->print(output, row);
	}
	if (right != nullptr && right->level != level) {
		if (left == nullptr) {
			output.emplace_back();
			output.emplace_back();
		}
		while (output[row].str().size() < output[output.size()-1].str().size())
		{
			output[row] << '-';
		}
		output[row] << '-' << '-';
		while (output[row+1].str().size() < output[row].str().size() - 1)
		{
			output[row+1] << ' ';
		}
		output[row + 1] << '|';
		while (output[row + 2].str().size() < output[row + 1].str().size() - 1)
		{
			output[row + 2] << ' ';
		}
		right->print(output, row + 2);
	}
}