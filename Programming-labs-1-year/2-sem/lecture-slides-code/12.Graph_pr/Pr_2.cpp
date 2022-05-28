//додавання дуги у орієнтований граф,
//що заданий структурою суміжності
const int MaxN=16;
typedef struct Node {int nn;
             Node *next;} Listn, *Listp;
typedef struct {int n;             
	           Listp e[MaxN];} StrAdj;

void add(StrAdj gr, int i, int j){
  Listp p, q;
  if (i<0 || j<0 || i>=gr.n || j>=gr.n) return;
  for (p=q=gr.e[i]; q; q=q->next)
    if (q->nn == j) return;
  gr.e[i]=q = new Node; q->nn = j; q->next = p;
}
