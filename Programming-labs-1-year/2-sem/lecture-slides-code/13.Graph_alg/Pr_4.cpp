//дії з графами
#include <iostream>
using namespace std;

const int MaxN=16;
typedef struct Node {int nn;
             Node *next;} Listn, *Listp;
typedef struct {int n;
	           Listp e[MaxN];} StrAdj;

void dfs_st(StrAdj, int);
void search_st(StrAdj);
void bld_gr(StrAdj &);
void addq(Listp *, Listp *, int);
int popq(Listp *, Listp *);
void search_bst(StrAdj);
void bfs_st(StrAdj, int);
void linkcm(StrAdj, int []);
void comp(StrAdj, int, int [], int);

bool num[MaxN];

int main(){
  StrAdj s;
  int cnm[MaxN];
  bld_gr(s);
  cout << "Depth first search: ";
  search_st(s); cout << endl;
  cout << "Breadth first search: ";
  search_bst(s); cout << endl;
  cout << "Components connection" << endl;
  linkcm(s, cnm);
  system("pause");
  return 0;
}

//побудова струкури суміжності графа
void bld_gr(StrAdj &s){
  int nv, i, v;
  Listp p, t;
  cout << "Building graph G=(V, E)  ";
  cout << "|V| = ";
  cin >> nv; cout << endl;
  s.n = nv;
  for (i=0; i<nv; i++){
    cout << "v" << i << ": ";
    cin >> v;
    p = new Node;
    s.e[i] = p;
    while (v > -1) {
      t = p;
      t->nn = v;
      p = new Node; t->next = p;
      cin >> v;
    }
    if (s.e[i] == p) s.e[i] = NULL;
    else t->next = NULL;
    delete p;
  }
}

//пошук у глибину
void search_st(StrAdj s){
  int v;
  for (v=0; v<MaxN; v++)
    num[v] = v < s.n;
  for (v=0; v<s.n; v++)
    if (num[v]) dfs_st(s, v);
}

void dfs_st(StrAdj s, int v) {
  Listp w;
  cout << v << "  "; num[v] = 0;
  for (w=s.e[v]; w; w=w->next)
    if (num[w->nn]) dfs_st(s, w->nn);
}

//пошук у ширину
void search_bst(StrAdj s){
  int v;
  for (v=0; v<MaxN; v++)
    num[v] = v < s.n;
  for (v=0; v<s.n; v++)
    if (num[v]) bfs_st(s, v);
}

void bfs_st(StrAdj s, int v) {
  int u, w;
  Listp dl=NULL, l=NULL, p;
  addq(&dl, &l, v); num[v] = 0;
  while (dl) {
    u = popq(&dl, &l);
    cout << u << "  ";
    for (p=s.e[u]; p; p=p->next){ w = p->nn;
      if (num[w]) {
        addq(&dl, &l, w); num[w] = 0;}
    }
  }
}

//дії з чергою
void addq(Listp *dl, Listp *l, int v){
  Listp q;
  q = new Node;
  q->nn = v;  q->next = NULL;
  if (*dl)  (*l)->next = q;
  else *dl = q;
  *l = q;
}

int popq(Listp *dl, Listp *l){
  int v;
  Listp q;
  if (!(q = *dl)) return 0; //черга порожня
  if (q == *l) *dl = *l = NULL;
  else (*dl) = q->next;
  v = q->nn; delete q;
  return v;
}

//пошук компонент зв`язності
void linkcm(StrAdj s, int cnm[MaxN]){
  int v, c;
  for (v=0; v<MaxN; v++){
    num[v]=v<s.n; cnm[v]=0;}
  for (c=v=0; v<s.n; v++)
    if (num[v]) {
      c++;  cout << c << " :  ";
      comp(s, v, cnm, c); cout << endl;}
}

void comp(StrAdj s, int v, int cnm[], int c){
  Listp w;
  cout << v << " ";  num[v]=0; cnm[v]=c;
  for (w=s.e[v]; w; w=w->next)
    if (num[w->nn]) comp(s, w->nn, cnm, c);
}
