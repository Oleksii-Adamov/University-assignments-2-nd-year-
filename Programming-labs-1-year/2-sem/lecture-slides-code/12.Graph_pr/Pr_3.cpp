//кількість дуг
//степінь вершин
//граф заданий вектором суміжності
#define ised(gr, i, j) ((gr.e[i]>>(j))&01)
const int MaxN=16;
typedef struct {int n;
                unsigned e[MaxN];} VctAdj;
void count(VctAdj a, int cnt[MaxN], int *s){
  int v, t;
  for (v=0; v<MaxN; v++) cnt[v] = 0;
  for (*s=v=0; v<a.n; v++)
    { for (t=0; t<a.n; t++)
        if (ised(a, v, t)) cnt[v]++;
      (*s) += cnt[v];}
}