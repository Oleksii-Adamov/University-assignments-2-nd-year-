#include <iostream>
using namespace std;

const int k = 100;
int dat[k], pdat[k];

int lform(int, int, int);
void lprint(int);
int ldel(int);

int main() {
   int pbeg;
   pbeg = lform(1, 2, 3);  //побудова списку
   lprint(pbeg);           //друкування елементів
   pbeg = ldel(pbeg);      //знищення списку
   system("pause");
   return 0;
}

//побудова списку з 3 елементів
int lform(int d1, int d2, int d3){
   int p, t;
   p = 40;  dat[p]= d3; pdat[p]= -1;
   t = 20;  dat[t]= d2; pdat[t]= p; p = t;
   t = 30;  dat[t]= d1; pdat[t]= p; p = t;
   return p;
}

//друкування 3-елементного списку
void lprint(int p){
   cout << dat[p] << ' '; p = pdat[p];
   cout << dat[p] << ' '; p = pdat[p];
   cout << dat[p] << endl;
}

//знищення 3-елементного списку
int ldel(int p){
   return -1;
}
