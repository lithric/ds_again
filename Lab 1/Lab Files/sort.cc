#include "lab1.h"

void recursiveSort(int data[],int start,int end) {
  int i,tmp,bdy=start;

  if (start < end) {
    for (i=start+1;i<=end;i++)
      if (data[i] < data[start]) {
        bdy++;
        tmp = data[bdy];
        data[bdy] = data[i];
        data[i] = tmp;
      }

    tmp = data[start];
    data[start] = data[bdy];
    data[bdy] = tmp;

    recursiveSort(data,start,bdy-1);
    recursiveSort(data,bdy+1,end);
  }
}

void sortData(int data[],int nItems) {

  recursiveSort(data,0,nItems-1);
}
