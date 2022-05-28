//вилучення вузла з АВЛ-дерева

//вилучення вузла
//повертає ознаку того, що висота зменшилась
bool bdelete(BALTRP *p, int v) {
  BALTRP t;
  if (!(t = *p)) return 0;
  else if (t->dat > v)
  	     return(bdelete(&(t->lt), v) ? lbald(p) : 0);
  	   else if (t->dat < v)
  	           return(bdelete(&(t->rt), v) ? rbald(p) : 0);
  	         else if (t->lt)
  	         	       return(bdelmax(&(t->lt), t) ? lbald(p) : 0);
  	         	    else {*p = t->rt; delete t; return 1;}
}

//вилучення вузла з максимальним значенням після пересилання його значення
//у вузол з покажчиком t
//повертає ознаку того, що висота зменшилась
bool bdelmax(BALTRP *p, BALTRP t) {
  BALTRP q;
  if ((q = *p)->rt)
  	return(bdelmax(&(q->rt), t) ? rbald(p) : 0);
  else {t->dat = q->dat; *p = q->lt; delete q; return 1;}
}

//ліве перебалансування при вилученні
//повертає ознаку того, що висота зменшилась
bool lbald(BALTRP *p) {
  BALTRP t;
  switch((t = *p)->bal)
  { case -1: t->bal = 0; return 1;
    case 0:  t->bal = 1; return 0;
    case 1:  switch((t = t->rt)->bal)
  		  { case -1:
  		  	 switch((t->lt)->bal)
  		  	 { case -1: dbleft(p, 0, 1, 0);  return 1;
  		  	   case 0:  dbleft(p, 0, 0, 0);  return 1;
  		  	   case 1:  dbleft(p, -1, 0, 0); return 1;
  		  	 }
  		    case 0: left(p, 1, -1); return 0;
  		    case 1: left(p, 0, 0);  return 1;
  		  }
  }
}
//аналогічний вигляд має функція rbald(p) для правого перебалансування
//!!!самостійно додати звільнення пам`яті вилученного вузла