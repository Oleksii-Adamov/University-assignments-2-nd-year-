//обчислення виразу в ПОЛІЗ
//вираз зберігається у n перших елементах масиву a
int seval(int a[], int n){
  int st[100], p, c, t=-1;
  for (p=0; p<n; p++)
    if (a[p] < 0) { c = st[t--];
      switch (a[p]){
       case -1: st[t] += c; break;
       case -2: st[t] -= c; break;
       case -3: st[t] *= c; break;
       case -4: st[t] /= c; break;}
    } else st[++t] = a[p];
  return st[t];
}
//відсутня перевірка на правильність вхідної інформації
//відсутня перевірка на порожність стека  в кінці