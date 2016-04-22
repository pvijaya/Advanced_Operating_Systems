#include <xinu.h>
#include <future.h>

uint32 future_prod(future_t* future)
 {
  int i,j;
 // printf("in future prod");
  j = (int)future;
  for (i=0; i<1000; i++) 
  {
    j += i;
  }
  future_set(future, &j);
  //printf("Prod future set done");
  return OK;
}