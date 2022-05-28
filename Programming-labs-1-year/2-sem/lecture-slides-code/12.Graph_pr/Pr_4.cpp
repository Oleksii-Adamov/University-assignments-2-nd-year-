//обчислення транзитивного замикання
//представлення матрицею суміжності
const int MaxN=100;
void tran(bool A[MaxN][MaxN], int nn){
  for (int k=0; k<nn; k++)
    for (int i=0; i<nn; i++)
      if (A[i][k])
        for (int j=0; j<nn; j++) A[i][j] = A[i][j] || A[k][j];
}