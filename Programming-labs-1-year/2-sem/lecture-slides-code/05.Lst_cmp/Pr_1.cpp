//скал€рний добуток вектор≥в
#include <iostream>
using namespace std;

const int NN=10000, KK=800;

int main() {
  int i, inp, sum;
  struct {int nm, val;} M[KK], *p;
  p = M;
  cout << "M : " << endl;
  for (i=0; i<NN; i++) {
  	  cin >> inp;
  	  if (p->val = inp) (p++)->nm = i;
  	}
  p->nm = NN; sum = 0; p = M;
  cout << "N : " << endl;
  for (i=0; i<NN; i++) {
    cin >> inp;
  	if (i == p->nm) sum += (p++)->val * inp;
  }
  cout << "SUM = " << sum << endl;
  system("pause");
  return 0;
}