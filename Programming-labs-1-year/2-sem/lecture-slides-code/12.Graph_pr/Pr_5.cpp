//обчислення транзитивного замикання
//представлення вектором суміжності
#define ised(gr, i, j) ((gr.e[i]>>(j))&01)
const int MaxN=16;
typedef struct {int n;
                unsigned e[MaxN];} VctAdj;
void count(VctAdj a){
  for (int k=0; k<a.n; k++)
    for (int i=0; i<a.n; i++ )
      if (ised(a, i, k)) a.e[i] |=a.e[k];
}