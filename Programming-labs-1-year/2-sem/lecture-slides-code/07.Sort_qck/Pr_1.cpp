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
   gen(arr, k);  //���������� ������ ����������������� �������
   aprint(arr, k); //����������� ������ �� ����������
   quick(&arr[0], &arr[k-1]);  //����������
   aprint(arr, k); //����������� ������ ���� ����������
   system("pause");
   return 0;
}

//-------------------
//������ ���������� �������� *low, ..., *hi
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
//���� ������� *p �� *q
void swap(int *p, int *q) {
  int c;
  c = *q; *q = *p; *p = c;
}
//-------------------
//���������� ������ ����������������� �������
void gen(int a[], int n) {
  int seed=16;
  srand(seed);
  for (int i=0; i<n; i++)
    a[i] = rand();
}
//-------------------
//����������� ������
void aprint(int a[], int n) {
  cout << "Array: " << endl;
  for (int i=0; i<n; i++)
    cout << a[i] << ' ';
  cout << endl;
}
