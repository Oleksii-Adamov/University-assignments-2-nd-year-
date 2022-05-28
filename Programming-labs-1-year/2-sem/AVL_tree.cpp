#include<iostream>
#include<cstring>
using namespace std;
const int MAX_COMMAND_SIZE = 10000, COUNT = 5;
struct Node
{
    int data;
    Node* left;
    Node* right;
    int height;
};
void print_tree(Node* root, int space)
{
    if (root == NULL)
        return;
    space += COUNT;
    print_tree(root->right, space);
    cout << "\n";
    for (int i = 0; i < space - COUNT; i++) cout << " ";
    cout << root->data << "\n";
    print_tree(root->left, space);
}
void sym_traversal(Node* root) {
    if (root == nullptr) return;
    sym_traversal(root->left);
    cout << root->data << " ";
    sym_traversal(root->right);
}
int get_height(Node* node) {
    if (node == nullptr) return -1;
    return node->height;
}
int calc_height(Node* node) {
    return max(get_height(node->left), get_height(node->right)) + 1;
}
int calc_balance(Node* node) {
    return get_height(node->left) - get_height(node->right);
}
Node* right_rotation(Node* root) {
    Node* left_left_subtree = root->left->left, * left_right_subtree = root->left->right, * right_subtree = root->right;
    Node* new_root = root->left;
    new_root->right = root;
    new_root->left = left_left_subtree;
    new_root->right->left = left_right_subtree;
    new_root->right->right = right_subtree;
    new_root->right->height = calc_height(new_root->right);
    return new_root;
}
Node* left_rotation(Node* root) {
    Node* left_subtree = root->left, * right_left_subtree = root->right->left, * right_right_subtree = root->right->right;
    Node* new_root = root->right;
    new_root->left = root;
    new_root->right = right_right_subtree;
    new_root->left->left = left_subtree;
    new_root->left->right = right_left_subtree;
    new_root->left->height = calc_height(new_root->left);
    return new_root;
}
Node* AVL_fix_balance(Node* root) {
    if (get_height(root) < 1) {
        return root;
    }
    if (calc_balance(root) > 1) { // left-heavy
        if (get_height(root->left->left) < get_height(root->left->right)) {
            root->left = left_rotation(root->left);
        }
        root = right_rotation(root);
    }
    if (calc_balance(root) < -1) { // right-heavy
        if (get_height(root->right->right) < get_height(root->right->left)) {
            root->right = right_rotation(root->right);
        }
        root = left_rotation(root);
    }
    root->height = calc_height(root);
    return root;
}
Node * AVL_insert(Node * root, int data)
{
    if (root == nullptr) {
        Node* new_node = new Node;
        new_node->data = data;
        new_node->left = nullptr;
        new_node->right = nullptr;
        new_node->height = 0;
        return new_node;
    }
    if (data < root->data) {
        root->left = AVL_insert(root->left, data);
    }
    if (data > root->data) {
        root->right = AVL_insert(root->right, data);
    }
    root = AVL_fix_balance(root);
    root->height = calc_height(root);
    return root;
}
Node* AVL_swap_root_with_min_node_and_delete(Node* root, Node* min_node, Node* min_node_parent) {
    if (min_node->left != nullptr) {
        min_node->left = AVL_swap_root_with_min_node_and_delete(root, min_node->left, min_node);
        min_node->height = calc_height(min_node);
        min_node = AVL_fix_balance(min_node);
        return min_node;
    }
    root->data = min_node->data;
    Node* temp = min_node->right;
    delete min_node;
    return temp;
}
Node* AVL_delete(Node* root, int key) {
    if (root == nullptr) return root;
    if (key < root->data) {
        root->left = AVL_delete(root->left, key);
    }
    else if (key > root->data) {
        root->right = AVL_delete(root->right, key);
    }
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr) {
            Node* right_child = root->right;
            delete root;
            right_child->height = calc_height(right_child);
            right_child = AVL_fix_balance(right_child);
            return right_child;
        }
        else if (root->right == nullptr) {
            Node* left_child = root->left;
            delete root;
            left_child->height = calc_height(left_child);
            left_child = AVL_fix_balance(left_child);
            return left_child;
        }
        else {
            Node* next_greater = root->right, * next_greater_parent = root;
            root->right = AVL_swap_root_with_min_node_and_delete(root, next_greater, next_greater_parent);
            root->height = calc_height(root);
            root = AVL_fix_balance(root);
            return root;
        }
    }
    root->height = calc_height(root);
    root = AVL_fix_balance(root);
    return root;
}
bool is_balanced(Node* node) {
    if (node == nullptr) return true;
    bool ans = true;
    ans = is_balanced(node->left) && is_balanced(node->right);
    ans = ans && (abs(calc_balance(node)) < 2);
    return ans;
}
int main() {
    Node* root = nullptr;
    char command[MAX_COMMAND_SIZE];
    cin.getline(command, MAX_COMMAND_SIZE);
    while (strcmp(command, "quit") != 0) {
        if (strcmp(command, "insert") == 0) {
            int val;
            cin >> val;
            cin.clear();
            cin.ignore(MAX_COMMAND_SIZE, '\n');
            root = AVL_insert(root, val);
            if (is_AVL(root)) cout << "AVL!\n";
            cout << "Inorder: ";
            sym_traversal(root);
            cout << "\n";
            cout << "Tree:\n";
            print_tree(root, 0);
            cout << "\n";
            if (!is_balanced(root)) {
                cout << "Error. Tree is unbalanced";
                return 0;
            }
        }
        if (strcmp(command, "delete") == 0) {
            int val;
            cin >> val;
            cin.clear();
            cin.ignore(MAX_COMMAND_SIZE, '\n');
            root = AVL_delete(root, val);
            if (is_AVL(root)) cout << "AVL!\n";
			cout << "Inorder: ";
            sym_traversal(root);
            cout << "\n";
            cout << "Tree:\n";
            print_tree(root, 0);
            cout << "\n";
            if (!is_balanced(root)) {
                cout << "Error. Tree is unbalanced";
                return 0;
            }
        }
        cin.getline(command, MAX_COMMAND_SIZE);
    }
}
/*
insert
10
insert
18
insert
7
insert
15
insert
16
insert
30
insert
25
insert
40
insert
60
insert
2
insert
1
insert
70
*/
