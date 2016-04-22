#include <xinu.h>
#include <future.h>

syscall future_set(future_t* var, int* val)
{
	intmask im;
	im = disable();
	
	if (var->state == FUTURE_WAITING && var->mode == FUTURE_EXCLUSIVE)	{
		var->value = *val;
		var->state = FUTURE_READY;
		resume(var->pid);
		restore(im);
		return OK;
	}
	
	if (var->state == FUTURE_EMPTY && (var->mode == FUTURE_EXCLUSIVE || var->mode == FUTURE_SHARED))	{
		var->value = *val;
		var->state = FUTURE_READY;
		restore(im);
		return OK;
	}
	
	if (var->state == FUTURE_READY && (var->mode == FUTURE_EXCLUSIVE || var->mode == FUTURE_SHARED))	{
		restore(im);
		return SYSERR;
	}
	
	if (var->state == FUTURE_WAITING && var->mode == FUTURE_SHARED)	{
		var->value = *val;
		var->state = FUTURE_READY;
		if ((var->head_getq) > -1 && (var->tail_getq) >-1 && (var->head_getq)<LIMIT && (var->tail_getq)<LIMIT)	{
		int counter = var->head_getq;
			while(counter<=(var->tail_getq))	{
				resume(var->get_queue[counter]);
				counter++;
			}
		
		}	

		restore(im);
		return OK;
	}
	
	if(var->mode == FUTURE_QUEUE) {
		if(isQEmpty(&(var->head_getq),&(var->tail_getq)) && isQEmpty(&(var->head_setq),&(var->tail_setq)) )    {
						printf("\n in set both empty\n");
                        *val = var->value;      
                        var->state = FUTURE_READY;
			enQ(var->set_queue, getpid(), &(var->head_setq), &(var->tail_setq));
                        suspend(getpid()); // BOTH EMPTY
                        resume(var->get_queue[var->head_getq]);
                        printf("");
			restore(im);
			return OK;
		}
			//only setq empty	
		if(!isQEmpty(&(var->head_getq),&(var->tail_getq)) && isQEmpty(&(var->head_setq),&(var->tail_setq)) )    {
			//printf("\n in set only set empty\n");
                        *val = var->value;     
                        var->state = FUTURE_READY;
                        resume(var->get_queue[var->head_getq]);
						printf("");
                        deQ(var->get_queue, &(var->head_getq), &(var->tail_getq));
			restore(im);
			return OK;
		}
			//only getq empty
		if(isQEmpty(&(var->head_getq),&(var->tail_getq)) && !isQEmpty(&(var->head_setq),&(var->tail_setq)) )    {
			//printf("\n in set only get empty\n");
			enQ(var->set_queue, getpid(), &(var->head_setq), &(var->tail_setq));
            suspend(getpid()); 
            resume(var->get_queue[var->head_getq]);
			printf("");
            *val = var->value;     
            var->state = FUTURE_READY;
			restore(im);
			return OK;
		}
	
		if(!isQEmpty(&(var->head_getq),&(var->tail_getq)) && !isQEmpty(&(var->head_setq),&(var->tail_setq)) )    {
			enQ(var->set_queue, getpid(), &(var->head_setq), &(var->tail_setq));
			//printf("\n in set both not empty\n");
                        suspend(getpid()); // BOTH not EMPTY
                        printf("");
						printf("\n Q4 :%d", val);
                        resume(var->get_queue[var->head_getq]);
                        *val = var->value;      
                        var->state = FUTURE_READY;
			restore(im);
			return OK;
		}
	}
	return SYSERR;
}	