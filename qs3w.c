#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "qs3w.h"
int compare(void const *x, void const *y)
{
  int m,n;
  m=*((int *)x);
  n=*((int *)y);
  return m-n;
}
void swap(void *x, void *y, int size)
{
  char a[size];
  memcpy(a,x,size);
  memcpy(x,y,size);
  memcpy(y,a,size);
}
void qsort3way(void *a, int num, size_t size, int (*compare)(void const *, void const *))
{
  if(num<=1) return;
  int right=num-1;
  void *pivot= a;
  int i=0, j=right+1;
  int m=1, n=right;
  void *ai,*aj,*am,*an;
  while(1) {
    while(compare((void *)(a + ((++i)*size)),pivot)>0)
      if(i==right) break;
    while(compare((void *)(a + ((--j)*size)),pivot)<0);
    if(i>=j) break;
    ai=(void *)(a+(i*size));
    aj=(void *)(a+(j*size));
    swap(ai,aj,size);
    if(compare(pivot,ai)==0) {
      am=(void *)(a+(m*size));
      swap(am,ai,size);
      m++;
    }
    if(compare(pivot,aj)==0) {
      an=(void *)(a+(n*size));
      swap(an,aj,size);
      n--;
    }
  }
    void *ak;
    for(int k=0;k<m;k++,j--) {
      ak=(void *)(a+(k*size));
      aj=(void *)(a+(j*size));
      swap(ak,aj,size);
    }
    for(int k=n+1;k<=right;k++,i++) {
      ak=(void *)(a+(k*size));
      ai=(void *)(a+(i*size));
      swap(ak,ai,size);
    }
    qsort3way(a,j+1,size,compare);
    qsort3way((void *)(a+(i*size)),num-i,size,compare);
}

