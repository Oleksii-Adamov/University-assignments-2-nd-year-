//Побудова матриці суміжності за її 
//структурою суміжності
const int MaxN=16;
typedef struct Node {int nn;
             Node *next;} Listn, *Listp;
typedef struct {int n;             
	           Listp e[MaxN];} StrAdj;

void AdjMtr(StrAdj s, bool A[MaxN][MaxN], int *nn){
  Listp p;
  int i, j, k;
  *nn = k = s.n;
  for (i=0; i<MaxN; i++)
    for (j=0; j<MaxN; j++) A[i][j] = 0;
  for (i=0; i<k; i++) {p = s.e[i];
  	while (p) {
  		A[i][p->nn] = 1; p = p->next;}
  	}
}