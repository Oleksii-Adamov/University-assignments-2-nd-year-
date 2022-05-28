#include <iostream>
using namespace std;

const int M = 100;
struct mem {
  int ns, xs, ys;
} st[M];
int p=M, n, x, y;

int acc(int, int, int);
int smacc(int, int);
void adds(int, int, int);
void reads();

int main(){
	int n, x, y;
	cout << "Function Accerman n= x= y=" << endl;
	cin >> n >> x >> y; cout << endl;
	cout << "Acc = " << acc(n, x, y) << endl;
	system("pause");
  return 0;
}

//--------------------------------
//нерекурсивна функція Аккермана
int acc(int ni, int xi, int yi) {
  int t;
  adds(ni, xi, yi);
  do {
  	reads();
  	if (n&&y) adds(n, x, y-1);
  	else {
  		  t = smacc(n, x);
  		  if (++p < M){
  		  	  reads(); p++;
  		  	  adds(n-1, t, x);
  		  	}
  		}
  	} while (p < M);
  return t;
}
//--------------------------------
//функція Аккермана при n=0|y=0
int smacc(int n, int x) {
  switch (n) {
    case 0: return x+1;
    case 1: return x;
    case 2: return 0;
    case 3: return 1;
    default: return 2;}
}
//--------------------------------
//додавання в стек st нової трійки
void adds(int ni, int xi, int yi) {
  if (p--) {
  	  st[p].ns = ni; st[p].xs = xi; st[p].ys = yi;
  	}
  else cout << "Steck full" << endl;
}
//--------------------------------
//читання з стека st трійки
void reads() {
  n = st[p].ns; x = st[p].xs; y = st[p].ys;
}