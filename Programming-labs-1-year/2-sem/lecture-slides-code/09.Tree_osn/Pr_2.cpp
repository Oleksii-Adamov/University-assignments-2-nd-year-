#include <iostream>
using namespace std;

const int m=3, n=1000, Mst=100;
typedef struct TrNd {int dat;
                     TrNd *s[m];
                     TrNd *f;} TrNde, *TrNdp;
TrNdp arrp[n];
int sp=0;
TrNdp st[Mst];
int lev, dn;

TrNdp input(int, TrNdp);
void push(TrNdp);
TrNdp pop();
void preord_st(TrNdp);
void postord(TrNdp p);
TrNdp copytr(TrNdp, TrNdp);

int main() {
  TrNdp p, q;
  cout << "Lev = "; cin >> lev;
  cout << "Data = "; cin >> dn; cout << endl;
  if (lev > -1)
    p = input(0, NULL);
  else p = NULL;
  cout << "Tree (preord) = ";
  preord_st(p); cout << endl;
  cout << "Tree (postord) = ";
  postord(p); cout << endl;
  q = copytr(p, NULL);
  cout << "Tree (preord) = ";
  preord_st(q); cout << endl;
  system("pause");
  return 0;
}

//-------------------------
//введення з рівневого подання
//ознака кінця - рівень -1
TrNdp input(int lf, TrNdp pf){
  int l;
  TrNdp p;
  if (lev > lf) {
      p = new TrNd; l = lev;
      p->dat = dn; p->f = pf;
      cout << "Lev = "; cin >> lev;
      cout << "Data = "; cin >> dn; cout << endl;
      for (int i=0; i<m; i++)
        p->s[i] = input(l, p);
   } else p = NULL;
  return p;
}


//-------------------------
//занесення у стек
void push(TrNdp p) {
  if (sp < Mst) st[sp++] = p;
  else cout << "Steck is FULL !!!" << endl;
}

//-------------------------
//вилучення зі стеку
TrNdp pop(){
  if (sp) return st[--sp];
  cout << "Steck is EMPTY !!!" << endl; return NULL;
}

//-------------------------
//виведення дерева в прямому порядку
void preord_st(TrNdp p){
  push(p);
  while(sp){
    if (p = pop()) {
           cout << p->dat << ' ';
           for (int i=m-1; i>=0; i--) //перебір піддерев
              push(p->s[i]);  //занесення у стек
       }
  }
}
//-------------------------
//виведення дерева в оберненому порядку
void postord(TrNdp p){
  if (p) {
          for (int i=0; i<m; i++) postord(p->s[i]);
          cout << p->dat << ' ';
         }
}
//-------------------------
//копіювання дерева у розширеній стандартній формі
TrNdp copytr(TrNdp t, TrNdp r){
  TrNdp p;
  if (!t) return t;
  p = new TrNd;  p->dat = t->dat;  p->f = r;
  p->s[0] = copytr(t->s[0], p);
  p->s[1] = copytr(t->s[1], p);
  p->s[2] = copytr(t->s[2], p);
  return p;
}
