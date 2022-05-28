#include <iostream>
using namespace std;

typedef struct Node {int dat;
             Node *next;} Listn, *Listp;

void index(Listp x[100]);
void lprint(Listp);

int main(){
	Listp xx[100];
	index(xx);
	cout << "Rezult list : " << endl;
	for (int i=0; i<100; i++)
	  if(xx[i]) {cout << i << " : "; lprint(xx[i]); cout << endl;}
  system("pause");
  return 0;
}
//-------------------------------------------------------
//формування індексного зберігання
void index(Listp x[100]) {
  Listp t;
  int inp, i;
  for (i=0; i<100; i++) x[i] = NULL;  //порожня структура
  //побудова сукупності циклічних списків з покажчиками в x[i]
  cout << "List : " << endl;
  cin >> inp;
  while (inp){
    if (x[i=inp%100]) {
    	t = new Node;
    	t->dat = inp; t->next = x[i]->next;
    	x[i]->next = t; x[i] = t;
    } else {
    	  x[i] = new Node;
    	  x[i]->dat = inp; x[i]->next = x[i];
    	}
    cin >> inp;
  } cout << endl;
  //перетворення циклічних списків у звичайні
  for (i=0; i<100; i++)
    if (t=x[i]) {
    	x[i] = t->next; t->next = NULL;}
}
//-------------------------------------------------------
//виведення списку
void lprint(Listp p){
		while (p){
		cout << p->dat << ' ';
		p = p->next;
	}
}