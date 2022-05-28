//��������� �� ����������� ������������ �������� ������
#include <iostream>
using namespace std;

typedef struct BTN {int dat;
                    BTN *lt, *rt;
                   } BINTRN, *BINTRP;
BINTRP build(int);
void symord(BINTRP);
void preord(BINTRP);
void postord(BINTRP);

int main() {
 int n;
 BINTRP t;
 cout << "Create and display binary tree" << endl;
 cout << "Enter number of trees nodes: "; cin >> n; cout << endl;
 t = build(n);
 cout << "Created tree:" << endl;
 cout << "Sym_order: ";
 symord(t); cout << endl;
 cout << "Pre_order: ";
 preord(t); cout << endl;
 cout << "Post_order: ";
 postord(t); cout << endl;
 system("pause");
 return 0;
}

//-------------------------
//��������� ������������ �������� ������
BINTRP build(int nn){
  BINTRP p;
  int dd, nleft, nright;
  if (!nn) return NULL;  //������ ������
  nleft = nn /2;  //������� ����� � ����� �������
  nright = nn - nleft - 1;  //������� ����� � ������� �������
  cout << "Enter node data: "; cin >> dd; cout << endl;
  p = new BINTRN; p->dat = dd; //��������� �����
  p->lt = build(nleft);  //������ ���
  p->rt = build(nright);  //������ �����
  return p;
}
//-------------------------
//��������� ������ � ������������ �������
void symord(BINTRP p){
  if (p) {
        symord(p->lt);
        cout << p->dat << ", ";
        symord(p->rt);
        }
}
//��������� ������ � ������� �������
void preord(BINTRP p){
  if (p) {
        cout << p->dat << ", ";
        preord(p->lt);
        preord(p->rt);
        }
}
//��������� ������ � ���������� �������
void postord(BINTRP p){
  if (p) {
        postord(p->lt);
        postord(p->rt);
        cout << p->dat << ", ";
        }
}
