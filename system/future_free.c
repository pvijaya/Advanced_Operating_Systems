#include <xinu.h>
#include <future.h>

//typedef struct future_t future;

syscall future_free(future_t* future)
{	
	int free_mem =0;
	intmask im;
	im = disable();
	/* only for shared mode
	if(future->mode == FUTURE_SHARED )
	{
		if(freemem((char *)future->get_queue, sizeof(future->get_queue)))
			return OK;
		else
			return SYSERR;
	}*/
	free_mem = freemem((char *)future, sizeof(future));
	future = NULL;
	restore(im);
	if(SYSERR == free_mem)
		return SYSERR;
	else
		return OK;		

}