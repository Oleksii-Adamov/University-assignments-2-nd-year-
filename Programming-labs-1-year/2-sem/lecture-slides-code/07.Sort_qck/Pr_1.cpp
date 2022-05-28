#include <iostream>
#include <cstdlib>
using namespace std;

const int k = 100;
int arr[k];

void quick(int *, int *);
void swap(int *, int *);
void gen(int a[], int);
void aprint(int a[], int);

int main() {
   gen(arr, k);  //заповнення масиву псевдовипадковими числами
   aprint(arr, k); //відображення масиву до сортування
   quick(&arr[0], &arr[k-1]);  //сортування
   aprint(arr, k); //відображення масиву після сортування
   system("pause");
   return 0;
}

//-------------------
//швидке сортування елементів *low, ..., *hi
void quick(int *low, int *hi) {
  int cnt, *p, *q;
  if ((hi-low == 1) && (*hi < *low)) swap(hi, low);
  if (hi-low > 1) {
    p = low+1; q = hi; cnt = *low;
    while (p < q)
      if (*p <= cnt) p++;
      else {if (*q <= cnt) swap(p, q); q--;}
    if (*p > cnt) p--;
    swap(p, low);
    quick(low, p-1); quick(p+1, hi);
  }
}
//-------------------
//обмін значень *p та *q
void swap(int *p, int *q) {
  int c;
  c = *q; *q = *p; *p = c;
}
//-------------------
//заповнення масиву псевдовипадковими числами
void gen(int a[], int n) {
  int seed=16;
  srand(seed);
  for (int i=0; i<n; i++)
    a[i] = rand();
}
//-------------------
//відображення масиву
void aprint(int a[], int n) {
  cout << "Array: " << endl;
  for (int i=0; i<n; i++)
    cout << a[i] << ' ';
  cout << endl;
}
