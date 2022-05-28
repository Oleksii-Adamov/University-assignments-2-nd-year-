#include<iostream>
using namespace std;
const int MAX_SIZE = 10000, M = 10;
struct Node {
	Node* sons[M];
	int data;
};
int find_close(string s, int pos, int len) {
	
}
int string_to_int(string s, int& pos, int len) {
	
}
Node* bracket_input(string s, int& pos, int len) {
	if (pos >= len) return;
	if (s[pos] != '(' && s[pos] != ')') {
		Node* new_node = new Node;
		new_node->data = string_to_int(s,pos,len);
		pos++;
		if (pos < len) {
			if (s[pos] == '(') {
				pos_close = find_close(s,pos,len);
			}
			if (pos_close != -1) {
				int i = 0;
				for (; i < M && pos < pos_close - 3; i++) {
					pos++;
					sons[i] = bracket_input(s,pos,len);
				}
				pos = pos_close;
				for (i < M; i++) {
					sons[i] = nullptr;
				}
			}
		}
	}
}
Node* input(int prev_lev){
  int l;
  Node* node;
  if (lev > prev_lev) {
      node = new Node; l = lev;
      node->data = input_data;
      cout << "Lev = "; cin >> lev;
      cout << "Data = "; cin >> input_data;
      for (int i=0; i<m; i++)
        node->s[i] = input(l);
   } else node = nullptr;
  return node;
}
int main() {
	Node* root;
	cout << "Lev = "; cin >> lev;
	cout << "Data = "; cin >> input_data;
	if (lev > -1)
		root = input(0);
	else root = nullptr;
}
