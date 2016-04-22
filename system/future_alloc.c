#include <xinu.h>
#include <future.h>

//typedef struct future_t;

future_t* future_alloc(future_mode_t mode)
{
	intmask im;
	int q=0;
	im = disable();
	future_t* future;
	
	future = (future_t *)getmem(sizeof(future_t));
	if (SYSERR == (int)future)
	{
		restore(im);
		return NULL;
	}
	else
	{
		for(q=0;q<LIMIT;q++)
		{
			future->set_queue[q] = -1;
			future->get_queue[q] = -1;
		}
		future->head_getq = -1;
		future->tail_getq = -1;
		future->head_setq = -1;
		future->tail_setq = -1;
		future->state = FUTURE_EMPTY;
		future->mode = mode;
		printf("allocated future, mode:%d!\n", mode);
		restore(im);
		return future;
	}
}