#include <xinu.h>

uint16 future_prod(future_t* fut) {
  int32 i, j;
  j = (int32)fut;
  for (i = 0; i < 1000; ++i) {
    j += i;
  }
//  printf("prod set: %d\n",j);
  future_set(fut, j);
  return OK;
}

uint16 future_cons(future_t* fut) {
	int32 value, status;
  status = (int)future_get(fut, &value);
  if (status < 1) {
    printf("future_get failed\n");
    return -1;
  }
  printf("it produced %d\n", value);
  return OK;
}
