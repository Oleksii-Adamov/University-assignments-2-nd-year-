//Відновлення розрідженої матриці по її 
//послідовно-зв`язаному індексному зберіганню
const int n=10, m=40;
typedef struct Node {int nj, dat;
             Node *next;} Listn, *Listp;

void IndMtr(const Listp A[], int B[][m], int nn, int mm){
  Listp p;
  int i, j;
  for (i=0; i<nn; i++)
    for (j=0; j<mm; j++) B[i][j] = 0;
  for (i=0; i<nn; i++) {p = A[i];
  	while (p) {
  		B[i][p->nj] = p->dat; p = p->next;}
  	}
}