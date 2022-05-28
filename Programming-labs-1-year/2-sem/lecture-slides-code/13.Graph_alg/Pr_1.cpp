//пошук у глибину на графі
//представлення - структура суміжності
const int MaxN=16;
typedef struct Node {int nn;
             Node *next;} Listn, *Listp;
typedef struct {int n;             
	           Listp e[MaxN];} StrAdj;

void dfs_st(StrAdj, int);

bool num[MaxN];

void search_st(StrAdj s){
  int v;
  for (v=0; v<MaxN; v++)
    num[v] = v < s.n;
  for (v=0; v<s.n; v++)
    if (num[v]) dfs_st(s, v);
}

void dfs_st(StrAdj s, int v) {
  Listp w;
  cout << v << ", "; num[v] = 0;
  for (w=s.e[v]; w; w=w->next)
    if (num[w->nn]) dfs_st(s, w->nn);
}