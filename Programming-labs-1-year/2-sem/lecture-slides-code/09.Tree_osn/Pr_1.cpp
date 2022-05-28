#include <iostream>
using namespace std;

const int m=3, n=1000;
typedef struct TrNd {int dat;
                     TrNd *s[m];
                     TrNd *f;} TrNde, *TrNdp;
TrNdp arrp[n];

TrNdp trform(TrNdp arrpt[], int *);
void preord(TrNdp);
void postord(TrNdp);

int main() {
  TrNdp p;
  int k;
  p = trform(arrp, &k); //побудова дерева
  cout << "Tree (preord) = ";
  preord(p); cout << endl; //виведення у прямому порядку
  cout << "Tree (postord) = ";
  postord(p); cout << endl; //виведення у оберненому порядку
  system("pause");
  return 0;
}

TrNdp trform(TrNdp arrpt[], int *k) {
  TrNdp p, t;
  p = new TrNd;
  p->dat = 15; p->f = NULL;
  p->s[0] = t = new TrNd;
  t->s[0] = t->s[1] = t->s[2] = NULL;
  t->dat = 17; t->f = p; arrpt[0] = t;
  p->s[1] = t = new TrNd;
  t->s[0] = t->s[1] = t->s[2] = NULL;
  t->dat = 10; t->f = p; arrpt[1] = t; *k = 2;
  p->s[2] = NULL; return p;}


//-------------------------
//виведення дерева в прямому порядку
void preord(TrNdp p){
  if (p) {
          cout << p->dat << ' ';
          for (int i=0; i<m; i++) preord(p->s[i]);
         }
}

//-------------------------
//виведення дерева в оберненому порядку
void postord(TrNdp p){
  if (p) {
          for (int i=0; i<m; i++) preord(p->s[i]);
          cout << p->dat << ' ';
         }
}
