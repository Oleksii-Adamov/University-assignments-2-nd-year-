//пошук у глибину на графі
//представлення - вектор суміжності
#define ised(gr, i, j) ((gr.e[i]>>(j))&01)

const int MaxN=16;
typedef struct {int n;
                unsigned e[MaxN];} VctAdj;

bool num[MaxN];

void search_st(VctAdj a){
  int v;
  for (v=0; v<MaxN; v++)
    num[v] = v < a.n;
  for (v=0; v<a.n; v++)
    if (num[v]) dfs_vc(a, v);
}

void dfs_vc(VctAdj a, v) {
  cout << v << ", "; num[v] = 0;
  for (int w=0; w<a.n; w++)
    if (ised(a, v, w) && num[w]) dfs_vc(a, w);
}