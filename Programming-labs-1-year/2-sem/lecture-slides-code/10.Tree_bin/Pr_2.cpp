//створення та відображення симетричного бінарного дерева
#include <iostream>
using namespace std;

typedef struct BTN {int dat;
                    BTN *lt, *rt;
                    } BINTRN, *BINTRP;
typedef struct TH {int dat;
                   TH *lt, *rt;
                   bool li, ri;
                   } THN , * THP;
BINTRP build(int);
void symord(BINTRP);
void symm(THP);
THP suc(THP);
THP buildh(BINTRP);
THP buildo(BINTRP, THP, THP);

int main() {
 int n;
 BINTRP t;
 THP q;
 cout << "Create and display binary tree" << endl;
 cout << "Enter number of trees nodes: "; cin >> n; cout << endl;
 t = build(n);
 cout << "Created tree:" << endl;
 cout << "Sym_order: ";
 symord(t); cout << endl;
 cout << "Created threaded tree:"<< endl;
 q = buildh(t);
 cout << "Sym_order: ";
 symm(q);
 system("pause");
 return 0;
}

//-------------------------
//створення симетричного бінарного дерева
BINTRP build(int nn){
  BINTRP p;
  int dd, nleft, nright;
  if (!nn) return NULL;  //порожнє дерево
  nleft = nn /2;  //кількість вузлів у лівому піддереві
  nright = nn - nleft - 1;  //кількість вузлів у правому піддереві
  cout << "Enter node data: "; cin >> dd; cout << endl;
  p = new BINTRN; p->dat = dd; //створюємо корінь
  p->lt = build(nleft);  //будуємо ліве
  p->rt = build(nright);  //будуємо праве
  return p;
}
//-------------------------
//виведення дерева в симетричному порядку
void symord(BINTRP p){
  if (p) {
        symord(p->lt);
        cout << p->dat << ", ";
        symord(p->rt);
        }
}
//-------------------------
//проходження прошитого  дерева
void symm(THP p){
  while (p->li) p = p->lt;
  while (p) {
  	  cout << p->dat << ", "; p = suc(p);}
}
//-------------------------
//пошук наступного вузла у симетричному порядку
THP suc(THP p){
  THP q=p->rt;
  if (p->ri)
  	while (q->li) q = q->lt;
  return q;
}
//-------------------------
//створення прошитого дерева
THP buildh(BINTRP p){
  return (p ? buildo(p, NULL, NULL) : NULL);
}
//-------------------------
THP buildo(BINTRP p, THP sl, THP sr){
  THP t;
  t = new TH;
  t->dat = p->dat;
  if ((t->li = (p->lt != NULL)))
  	t->lt = buildo(p->lt, sl, t);
  else t->lt = sl;
  if ((t->ri = (p->rt != NULL)))
  	t->rt = buildo(p->rt, t, sr);
  else t->rt = sr;
  return t;
}
