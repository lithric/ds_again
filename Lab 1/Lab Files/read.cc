#include "lab1.h"

int readData(int data[],int maxItems) {
  int i=0,item;

  while (i < maxItems) {
    cin >> item;
    if (!cin)
      break;
    data[i] = item;
    i++;
  }

  return i;
}
