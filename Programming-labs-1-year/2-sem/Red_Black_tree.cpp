#include<iostream>
#include<cstring>
using namespace std;
const int COUNT = 5, MAX_COMMAND_SIZE = 15;
enum Color { RED, BLACK };
struct Node
{
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;
};
void print_tree(Node* root, int space)
{
    if (root == NULL)
        return;
    space += COUNT;
    print_tree(root->right, space);
    cout << "\n";
    for (int i = 0; i < space - COUNT; i++) cout << " ";
    cout << root->data << "\\" << (root->color == BLACK ? "BLACK" : "RED");
    print_tree(root->left, space);
}
Node* BST_insert(Node* root, int data, Node* new_node, Node* parent) {
    if (root == nullptr) {
        new_node->data = data;
        new_node->left = nullptr;
        new_node->right = nullptr;
        new_node->parent = parent;
        return new_node;
    }
    if (data < root->data) {
        root->left = BST_insert(root->left, data, new_node, root);
    }
    if (data > root->data) {
        root->right = BST_insert(root->right, data, new_node, root);
    }
    return root;
}
Node* right_rotation(Node* root) {
    Node* left_left_subtree = root->left->left, * left_right_subtree = root->left->right, * right_subtree = root->right;
    Node* new_root = root->left;
    new_root->right = root;
    new_root->left = left_left_subtree;
    new_root->right->left = left_right_subtree;
    new_root->right->right = right_subtree;
    new_root->parent = root->parent;
    root->parent = new_root;
    if (new_root->parent != nullptr && new_root->parent->right == root) {
        new_root->parent->right = new_root;
    }
    if (new_root->parent != nullptr && new_root->parent->left == root) {
        new_root->parent->left = new_root;
    }
    swap(root->color, new_root->color);
    return new_root;
}
Node* left_rotation(Node* root) {
    Node* left_subtree = root->left, * right_left_subtree = root->right->left, * right_right_subtree = root->right->right;
    Node* new_root = root->right;
    new_root->left = root;
    new_root->right = right_right_subtree;
    new_root->left->left = left_subtree;
    new_root->left->right = right_left_subtree; 
    new_root->parent = root->parent;
    root->parent = new_root;
    if (new_root->parent != nullptr && new_root->parent->right == root) {
        new_root->parent->right = new_root;
    }
    if (new_root->parent != nullptr && new_root->parent->left == root) {
        new_root->parent->left = new_root;
    }
    swap(root->color, new_root->color);
    return new_root;
} // 40 is bad
void fix_violation(Node*& root, Node* cur_node) {
    Node* parent = nullptr;
    Node* grand_parent = nullptr;
    while ((cur_node != root) && (cur_node->color != BLACK) && (cur_node->parent != nullptr && cur_node->parent->parent != nullptr && 
        cur_node->parent->color == RED))
    {
        parent = cur_node->parent;
        grand_parent = cur_node->parent->parent;
        if (parent == grand_parent->left)
        {
            Node* uncle = grand_parent->right;
            if (uncle != nullptr && uncle->color == RED)
            {
                grand_parent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                cur_node = grand_parent;
            }
            else
            {
                if (cur_node == parent->right)
                {
                    parent = left_rotation(parent);
                    cur_node = parent;
                    parent = cur_node->parent;
                }
                grand_parent = right_rotation(grand_parent);
                if (grand_parent->parent == nullptr) root = grand_parent;
                cur_node = parent;
            }
        }
        else
        {
            Node* uncle = grand_parent->left;
            if ((uncle != nullptr) && (uncle->color == RED))
            {
                grand_parent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                cur_node = grand_parent;
            }
            else
            {
                if (cur_node == parent->left)
                {
                    parent = right_rotation(parent);
                    cur_node = parent;
                    parent = cur_node->parent;
                }
                grand_parent = left_rotation(grand_parent);
                if (grand_parent->parent == nullptr) root = grand_parent;
                cur_node = parent;
            }
        }
    }
    root->color = BLACK;
}
void RBTree_insert(Node*& root, int data) {
    Node* cur_node = new Node;
    root = BST_insert(root, data, cur_node, nullptr);
    cur_node->color = RED;
    fix_violation(root, cur_node);
}
int main() {
    Node* root = nullptr;
    char command[MAX_COMMAND_SIZE];
    cin.getline(command, MAX_COMMAND_SIZE);
    while (strcmp(command, "quit") != 0) {
        if (strcmp(command, "insert") == 0) {
            int val;
            cin >> val;
            if (val == 40) {
                cin.clear();
            }
            cin.clear();
            cin.ignore(MAX_COMMAND_SIZE, '\n');
            RBTree_insert(root, val);
            cout << "Tree:\n";
            print_tree(root, 0);
            cout << "\n";
        }
        /*if (strcmp(command, "delete") == 0) {
            int val;
            cin >> val;
            cin.clear();
            cin.ignore(MAX_COMMAND_SIZE, '\n');
            root = AVL_delete(root, val);
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
        }*/
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
