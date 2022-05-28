//введення, вивведення та диференцювання виразу
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef struct BTN {int dat;
                    BTN *lt, *rt;
                    } BINTRN, *BINTRP;
int next=' ';

BINTRP inpexp();
void nsym();
BINTRP nwnode(int, BINTRP, BINTRP);
BINTRP expr();
int numb();
void prnexp(BINTRP);
BINTRP diff(BINTRP, int);
BINTRP copytr(BINTRP);

int main() {
  BINTRP t, p;
  char vr;
  cout << "Expression: ";
  t = inpexp(); cout << endl;
  cout << "Tree -> Expression: ";
  prnexp(t); cout << endl;
  cout << "Variable Diff : ";
  cin >> vr; cout << endl;
  p = diff(t, vr);
  cout << "Diff Expression: ";
  prnexp(p); cout << endl;
  system("pause");
 return 0;
}
//-------------------------
//введення виразу в повному дужковому записі
BINTRP inpexp(){
  nsym(); return expr();
}
//-------------------------
//введення чергового символу в next
void nsym(){
  if (next == EOF) return;
  while ((next = getchar())== ' ' || next == '\n');
}
//-------------------------
//формування вузла бінарного дерева
BINTRP nwnode(int v, BINTRP pl, BINTRP pr){
  BINTRP p = new BINTRN;
  p->dat = v; p->lt = pl; p->rt = pr;
  return p;
}
//-------------------------
//розпізнавання виразу
BINTRP expr(){
  BINTRP p;
  char nx;
  if (next == '('){
  	 nsym(); p = expr();
  	 if (strchr ("+-*/", next)){
  	 	 nx = next; nsym();
  	 	 p = nwnode(nx, p, expr());
  	 	}
  	 if (next != ')'){
  	 	  cout << "ERROR " << (char) next << endl; return NULL;
  	 	}
  	 nsym(); return p;
  	}
  if(strchr("xyz", next)){
     	nx = next; nsym();
  	return nwnode(nx, NULL, NULL);
  	}
  else return nwnode(-numb(), NULL, NULL);
}
//-------------------------
//введення числа
int numb(){
  int v;
  if (next <'0' || next > '9'){
  	 cout << "ERROR " << (char) next << endl; return -1;
  	}
  for (v=0; next >= '0' && next <= '9'; nsym())
     v = v * 10 + (next - '0');
  return v;
}
//-------------------------
//друкування виразу в повному дужковому записі
void prnexp(BINTRP p){
  int v;
  v = p->dat;
  if (v <= 0) cout << -v;
  else if (strchr("+-*/", v)){
	      cout << '('; prnexp(p->lt);
	      cout << (char) v; prnexp(p->rt); cout << ')';
	     }else cout << (char) v;
}
//-------------------------
//диферецювання виразу за змінною var
BINTRP diff(BINTRP p, int var){
  if (p->dat == var)
    return nwnode(-1, NULL, NULL);
  switch (p->dat) {
    case '+': return nwnode('+', diff(p->lt, var), diff(p->rt, var));
    case '-': return nwnode('-', diff(p->lt, var), diff(p->rt, var));
    case '*': return nwnode('+',
              nwnode('*', diff(p->lt,var), copytr(p->rt)),
              nwnode('*', copytr(p->lt), diff(p->rt, var)));
    case '/': return nwnode('/',
              nwnode('-', nwnode('*', diff(p->lt, var), copytr(p->rt)),
                     nwnode('*', copytr(p->lt), diff(p->rt, var))),
              nwnode('*', copytr(p->rt), copytr(p->rt)));
    default : return nwnode(0, NULL, NULL);
  }
}
//-------------------------
//створення копії бінарного дерева
BINTRP copytr(BINTRP p){
  if (p)
    return nwnode(p->dat, copytr(p->lt), copytr(p->rt));
  else return NULL;
}
