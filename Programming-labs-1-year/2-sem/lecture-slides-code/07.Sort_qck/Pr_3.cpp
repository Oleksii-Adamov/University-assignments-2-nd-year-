#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct Node {int dat;
             Node *next;} Listn, *Listp;

Listp pocket(Listp, int);
Listp lform(int);
void lprint(Listp);

int main() {
  Listp pbeg = lform(100); //побудова списку з 100 елементів
  cout << "Spisok before sort:" << endl;
  lprint(pbeg); //виведення списку
  pocket(pbeg, 5);
  cout << "Spisok after sort:" << endl;
  lprint(pbeg); //виведення списку
  system("pause");
  return 0;
}
//-------------------
//розподільне сортування зв`язного списку
Listp pocket(Listp q, int t){
  Listp A[10], B[10], r;
  int k, m;
  for (m=1; t--; m*=10){
  	for (k=0; k<10; k++) //розподіл по кишеням
  	  A[k]= B[k]= NULL;
  	for (; q; q = q->next){
  		k = (q->dat/m)%10;
  		if (!A[k]) A[k] = q;
  		else (B[k]->next) = q;
  		B[k] = q;
  		}
  	for (k=0; !A[k]; k++); //складання непорожніх кишень
  	q = A[k]; r = B[k];
  	for (k++; k<10; k++)
  	  if (A[k]){
  	  	r->next = A[k]; r = B[k];
  	  	}
  	 r->next = NULL;
  	}
  return q;
}
//-------------------
//побудова списку з N псевдовипадкових чисел
Listp lform(int n){
 Listp p, t;
 int seed=16;
 srand(seed);
 t = NULL;
 for (int i = 1; i <= n; i++){
   p = new Node;
   p->dat = rand();
   p->next = t;
   t = p;
   }
   return p;
}
//-------------------
//виведення списку
void lprint(Listp p){
   while (p){
	cout << p->dat << ' ';
	p = p->next;
	}  cout << endl;
}
