#include <iostream>
#include <cstdlib>
#define MIN(x, y) ((y)<(x)?(y):(x))
#define MAX(x, y) ((y)<(x)?(x):(y))
using namespace std;

const int k = 100;
int arr[k];

void gen(int a[], int);
void aprint(int a[], int);
void smerge(int a[], int);
void srecmg(int a[], int);
void merge(int w[], int, int);

int main() {
   gen(arr, k);  //���������� ������ ����������������� �������
   aprint(arr, k); //����������� ������ �� ����������

 //  smerge(arr, k);  //���������� ������������
   srecmg(arr, k);  //���������� ����������

   aprint(arr, k); //����������� ������ ���� ����������
   system("pause");
   return 0;
}
//-------------------
//������������ ���������� �������
void smerge(int a[], int n){
  int *p, *q;
  q = a + n;
  for (int l=1; l<n; l*=2)
    for (p=a; p+l < q; p+=2*l)
      merge(p, l, MIN(l*2, q-p));
}
//-------------------
//���������� ���������� �������
void srecmg(int a[], int n){
  int i;
  if (n>1){
  	i = n/2; srecmg(a,i);
  	srecmg(a+i, n-i); merge(a, i, n);
  	}
}
//-------------------
//������ ���� ������������� �������� 0,...,l1-1  ��  l1,..., l2
void merge(int w[], int l1, int l2){
  int i, *a, *pa, *pb;
  a = new int[l2+2];  //��������� ���������� ������
  pa = a; pb = a + l1 + 1;
  //��������� � ��������� �����
  for (i=0; i<l1; i++)  *pa++ = w[i];
  for (i=l1; i<l2; i++) *pb++ = w[i];
  *pa = *pb = MAX(w[l1-1], w[l2-1]) + 1;
  pa = a; pb = a + l1 + 1;
  for (i=0; i<l2; i++)
    w[i] = (*pa < *pb ? *pa++ : *pb++);
  delete [] a;
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
