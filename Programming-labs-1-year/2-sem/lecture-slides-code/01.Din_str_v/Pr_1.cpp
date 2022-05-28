#include <iostream>
using namespace std;

typedef struct Node {int dat;
             Node *next;} Listn, *Listp;

Listp lform(int, int, int);
void lprint(Listp);
void ldel(Listp);

int main() {
   Listp p;
   p = lform(1, 2, 3); //побудова списку
   print(p);           //друкування елементів
   ldel(p);            //знищення списку
   system("pause");
   return 0;
}

//побудова списку з 3 елементів
Listp lform(int d1, int d2, int d3){
   Listp p, t;
   p = new Listn;  p->dat = d3; p->next = NULL;
   t = new Listn;  t->dat = d2; t->next = p; p = t;
   t = new Listn;  t->dat = d1; t->next = p; p = t;
   return p;
}

//друкування 3-елементного списку
void lprint(Listp p){
   cout << p->dat << ' '; p = p->next;
   cout << p->dat << ' '; p = p->next;
   cout << p->dat << endl;
}

//знищення 3-елементного списку
void ldel(Listp p){
   Listp t;
   t = p->next; delete p; p = t;
   t = p->next; delete p; p = t;
   delete p;
}