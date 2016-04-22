#include<xinu.h>

syscall cond_init(cond_t** cv)
{

	   *cv = NULL;
	   *cv = (int16 *) getmem(sizeof(int16));
	   **cv=newqueue();

       return OK;
}
