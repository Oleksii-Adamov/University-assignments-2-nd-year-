//додавання вузла в АВЛ-дерево

//формування нового вузла збалансованого дерева
BALTRP newbl(v) {
  BALTRP t;
  t = new BALTRN;
  t->lt = t->rt = NULL;
  t->bal = 0; t->dat = v;
  return t;
}

//додавання вузла
//повертає ознаку того, що висота збільшилась
bool binclude(BALTRP *p, int v) {
  BALTRP t;
  if (!(t = *p)) {*p = newbl(v); return 1;}
  else if (t->dat == v) return 0;
  	   else return (t->dat > v ?
  	   	            (binclude(&(t->lt), v) ? lbal(p) : 0) :
  	   	            (binclude(&(t->rt), v) ? rbal(p) : 0));
}

//ліве перебалансування при додаванні
//повертає ознаку того, що висота збільшилась
bool lbal(BALTRP *p) {
  BALTRP t;
  switch((t = *p)->bal)
  { case 1:  t->bal = 0; return 0;
    case 0:  t->bal = -1; return 1;
    case -1: if ((t = t->lt)->bal == -1) right(p, 0, 0);
  		else if ((t->rt)->bal == -1) dbright(p, 1, 0, 0);
  			   else dbright(p, 0, -1, 0);
  		return 0;
  }
}
//аналогічний вигляд має функція rbal(p) для правого перебалансування