#include <iostream>
using namespace std;

int accrec(int, int, int);
int smacc(int, int);

int main(){
	int n, x, y;
	cout << "Function Accerman n= x= y=" << endl;
	cin >> n >> x >> y; cout << endl;
	cout << "Acc = " << accrec(n, x, y) << endl;
	system("pause");
  return 0;
}
//--------------------------------
//рекурсивна функція Аккермана
int accrec(int n, int x, int y){
  return (n&&y ?
     accrec(n-1, accrec(n, x, y-1), x) :
     smacc(n, x));
}
//--------------------------------
//функція Аккермана при n=0|y=0
int smacc(int n, int x){
  switch (n) {
    case 0: return x+1;
    case 1: return x;
    case 2: return 0;
    case 3: return 1;
    default: return 2;}
}