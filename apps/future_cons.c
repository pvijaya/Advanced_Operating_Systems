#include <xinu.h>
#include <future.h>

uint32 future_cons(future_t* future)
 {
	int  status,i;
	//printf("in future cons\n");
	status = future_get(future, &i); 
    if (status < 1)
		{
			printf("future_get failed\n");
			return -1;
		}
	/*kprintf("it produced %d\n", i);
    future_free(future);*/
	intmask im=disable();
	kprintf("it produced %d\n", i);
	restore(im);
    return OK;
}
