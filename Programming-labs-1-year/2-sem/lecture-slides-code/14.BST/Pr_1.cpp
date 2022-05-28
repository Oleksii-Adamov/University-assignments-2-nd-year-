//дерева бінарного пошуку
//побудова та основні дії
#include <iostream>
using namespace std;

const int NMAX=100;
typedef struct BTN {int dat;
                    BTN *lt, *rt;
                    } BINTRN, *BINTRP;
BINTRP nwnode(int, BINTRP, BINTRP);
BINTRP build(int [], int);
void symord(BINTRP);
BINTRP find(BINTRP, int);
BINTRP fnd(BINTRP, int);
int fmin(BINTRP);
int vmin(BINTRP p);
bool test(BINTRP);
BINTRP insert(BINTRP, int);
BINTRP ndel(BINTRP, int);
BINTRP delmax(BINTRP, BINTRP);

int vv;

int main() {
  BINTRP t, p;
  int nn, v;
  int a[NMAX];
  cout << "Enter number of trees nodes: ";
  cin >> nn; cout << endl;
  for (int i=0; i<nn; i++) a[i] = 2*i+1;
  //a[10] = 75; //для перевірки дерева бути деревом бінарного пошуку
  cout << "Created tree:" << endl;
  t = build(a, nn);
  cout << "Sym_order: "<< endl;
  symord(t); cout << endl;
  cout << "Enter key: "; cin >> v; cout << endl;
  cout << "Search : ";
  p = find(t, v);
  if (p) cout << p->dat;
  else cout << "No elements equal key !!!";
  cout << endl;
  cout << "Search : ";
  p = fnd(t, v);
  if (p) cout << p->dat;
  else cout << "No elements equal key !!!";
  cout << endl;
  cout << "Search min element : ";
  cout << fmin(t) << endl;
  cout << "Search min element : ";
  cout << vmin(t) << endl;
  vv = -32650;
  cout << "Test binary tree : ";
  if (test(t)) cout << "OK !!!";
  else cout << "NOT !!!"; cout << endl;
  cout << "Enter new element of trees : "; cin >> v; cout << endl;
  t = insert(t, v);
  cout << "Sym_order: "<< endl;
  symord(t); cout << endl;
  cout << "Enter element for delete : "; cin >> v; cout << endl;
  t = ndel(t, v);
  cout << "Sym_order: "<< endl;
  symord(t); cout << endl;
  system("pause");
 return 0;
}
//-------------------------
//побудова повністю сбалансованого дерева
//за даними у впорядкованому масиві
BINTRP build(int a[], int n) {
  int m;
  if (n) {
  	m = n/2;
    return(nwnode(a[m], build(&a[0], m), build(&a[m+1], n-m-1)));
   } return NULL;
}
//-------------------------
//формування вузла бінарного дерева
BINTRP nwnode(int v, BINTRP pl, BINTRP pr){
  BINTRP p = new BINTRN;
  p->dat = v; p->lt = pl; p->rt = pr;
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
//пошук у дереві бінарного пошуку рекурсивний
BINTRP find(BINTRP p, int key) {
  if (p && p->dat != key)
    return(p->dat>key ? find(p->lt, key) : find(p->rt, key));
  return p;
}
//-------------------------
//пошук у дереві бінарного пошуку нерекурсивний
BINTRP fnd(BINTRP p, int key) {
  while (p) {
    if (p->dat > key) p = p->lt;
    else if (p->dat < key) p = p->rt;
         else break;
  }
  return p;
}
//-------------------------
//пошук найменшого значення у дереві бінарного пошуку рекурсивний
int fmin(BINTRP p) {
  if (p->lt) return (fmin(p->lt));
  return (p->dat);
}
//-------------------------
//пошук найменшого значення у дереві бінарного пошуку нерекурсивний
int vmin(BINTRP p) {
  while (p->lt) p = p->lt;
  return (p->dat);
}
//-------------------------
//перевірка дерева бінарного пошуку
bool test(BINTRP p) {
  if (!p) return 1;
  if (!test(p->lt)) return 0;
  if (p->dat < vv) return 0;
  vv = p->dat;
  return (test(p->rt));
}
//-------------------------
//вставка у дерево бінарного пошуку
BINTRP insert(BINTRP p, int v) {
  if (!p) return (nwnode(v, NULL, NULL));
  if (p->dat > v) p->lt = insert(p->lt, v);
  else if (p->dat <v) p->rt = insert(p->rt, v);
  return p;
}
//-------------------------
//вилучення вузла з дерева бінарного пошуку
BINTRP ndel(BINTRP p, int v) {
  BINTRP q;
  if (p)
   {if (p->dat > v) p->lt = ndel(p->lt, v);
    else if (p->dat < v) p->rt = ndel(p->rt, v);
         else if (p->lt) p->lt = delmax(p->lt, p);
              else {q = p; p = p->rt; delete q;}
   } return p;
}
//-------------------------
//пошук вузла з максимальним значенням у дереві бінарного пошуку
//вилучення цього вузла після пересилання значення у вузел p
BINTRP delmax(BINTRP p, BINTRP t) {
  BINTRP q;
  if (p->rt) p->rt = delmax(p->rt, t);
  else {t->dat = p->dat; q = p; p = p->lt; delete q;}
  return p;
}