//���������� ���� ���� ���������� �������
const int n=10, m=40;
typedef struct Node {int nj, dat;
             Node *next;} Listn, *Listp;

void SumMtr(const Listp A[], const Listp B[], Listp C[], int nn, int mm){
  Listp p, pa, pb, pc;
  for (int i=0; i<nn; i++) //������ �����
   {pa = A[i]; pb = B[i];
  	pc = new Node; C[i] = pc;
  	while (pa && pb) //������ ����� �� ����������
  	{if (pa->nj == pb->nj){
  		pc->nj = pa->nj; pc->dat = pa->dat + pb->dat;
  		pa = pa->next; pb = pb->next;
  		} else if (pa->nj < pb->nj){
  			   pc->nj = pa->nj; pc->dat = pa->dat; pa = pa->next;
  			} else {
  				 pc->nj = pb->nj; pc->dat = pb->dat; pb = pb->next;}
  	 if (pc->dat)  //����������� ��������� ���� ���� 0
  		{p = pc; pc = new Node; p->next = pc;}
  	 }//while
   if (pb) pa = pb; //���� ��������������� �� ���� �����
   while (pa){ //��������� �����, �� ���������
   	   pc->nj = pa->nj; pc->dat = pa->dat; pa = pa->next;
   	    p = pc; pc = new Node; p->next = pc;
   	}//while
   //������������ ������
   if (pc == C[i]) C[i] = NULL;
   else p->next = NULL;
   delete pc;
   }//for
}