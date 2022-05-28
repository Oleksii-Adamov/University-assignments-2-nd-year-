#include <iostream>
using namespace std;

typedef struct Node {int dat;
             Node *next;} Listn, *Listp;
//-------------------------
Listp lform(int);
Listp lform_r(int);
void lprint(Listp);
void lprint_r(Listp);
void ldel(Listp);
void ldel_r(Listp);
int numb(Listp);
int numb_r(Listp);
Listp find(Listp const, int);
Listp find_r(Listp const, int);
//-------------------------
int main(){
	int n, k;
	//визначаємось з кількістю елементів
	cout << "Number = ";
	cin >> n;
	cout << endl;
//	Listp pbeg = lform(n); //побудова списку з N
	Listp pbeg = lform_r(n); //рекурсивна побудова списку з N
	lprint(pbeg); //виведення списку
	lprint_r(pbeg); //рекурсивне виведення списку
    cout << endl;
    //кількість елементів списку
    cout << "Number = " << numb(pbeg);
    cout << endl;
    cout << "Number = " << numb_r(pbeg);
    cout << endl;
    cout << "Number = ";
	cin >> k;
	cout << endl;
	Listp p = find(pbeg, k);
    if (p) cout << p->dat << endl;
    else cout << "not find" << endl;
    p = find_r(pbeg, k);
    if (p) cout << p->dat << endl;
    else cout << "not find" << endl;
    ldel(pbeg); //знищення списку
	//ldel_r(pbeg); //рекурсивне знищення списку
  system("pause");
  return 0;
}
//-------------------------
//побудова списку з N елементів n, n-1, n-2, ..., 2, 1
Listp lform(int n){
 Listp p, t= NULL;
  for (int i = 1; i <= n; i++){
   p = new Node;
   p->dat = i;
   p->next = t;
   t = p;
   }
   return p;
}
//-------------------------------------------------------
//рекурсивна побудова списку з N елементів n, n-1, n-2, ..., 2, 1
Listp lform_r(int n){
	if (n){
		 Listp p = new Node;
		 p->dat = n;
		 p->next = lform_r(n-1);
		 return p;
		}
	return NULL;
}
//-------------------------------------------------------
//виведення списку
void lprint(Listp p){
		while (p){
		cout << p->dat << ' ';
		p = p->next;
	} cout << endl;
}
//-------------------------------------------------------
//рекурсивне виведення списку
void lprint_r(Listp p){
	if (p){
		cout << p->dat << ' ';
		lprint_r(p->next);
	}
}
//-------------------------------------------------------
//знищення списку
void ldel(Listp p){
	Listp t;
	while (p){
		t = p;
		p = p->next;
		delete t;
	}
}
//-------------------------------------------------------
//рекурсивне знищення списку
void ldel_r(Listp p){
	if (p){
	  ldel_r(p->next);
      delete p;
	}
}
//-------------------------------------------------------
//кількість елементів списку
int numb(Listp p){
    int n = 0;
    while (p){
        n++; p = p->next;
    }
    return n;
}
//-------------------------------------------------------
//рекурсивно кількість елементів списку
int numb_r(Listp p){
    if (p) return (1 + numb_r(p->next));
    return 0;
}
//--------------------------------------------------------
//пошук елемента за ключем
Listp find(Listp const pbeg, int d){
	Listp t = pbeg;
	while (t){
		if (t->dat == d) break;
			t = t->next;
	}
	return t;
}
//--------------------------------------------------------
//рекурсивний пошук елемента за ключем
Listp find_r(Listp const pbeg, int d){
    if (pbeg) {
        if (pbeg->dat == d) return pbeg;
        else return(find_r(pbeg->next, d));
    }
    else return(pbeg);
}
