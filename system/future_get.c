#include <xinu.h>
#include <future.h>

syscall future_get(future_t* var, int* val)
{
	intmask im;
	im = disable();
	int i;
	
	
	if (var->state == FUTURE_EMPTY && var->mode == FUTURE_EXCLUSIVE)	{ 
		var->pid = getpid();
		var->state = FUTURE_WAITING;
		suspend(getpid());
		printf("");
		*val = var->value;	
		restore(im);
		return OK;
	}	
	if (var->state == FUTURE_READY && var->mode == FUTURE_EXCLUSIVE)	{ 
		var->pid = getpid();
		printf("");
		*val = var->value;	// or int *
		restore(im);
		return OK;
	}	
	if (var->state == FUTURE_WAITING && var->mode == FUTURE_EXCLUSIVE)	{
		restore(im);
		return SYSERR;	
	}
	if (var->state == FUTURE_READY && var->mode == FUTURE_SHARED)	{ 
		var->pid = getpid();
		*val = var->value;	// or int *
		var->state = FUTURE_READY;
		restore(im);
		return OK;
	}	
	if ((var->state == FUTURE_EMPTY || var->state == FUTURE_WAITING) && var->mode == FUTURE_SHARED)	{ 
		var->pid = getpid();
		var->state = FUTURE_WAITING;
		enQ(var->get_queue, getpid(), &(var->head_getq), &(var->tail_getq));
		suspend(getpid());
		printf("");
		*val = var->value;	// or int *
		restore(im);
		return OK;
	}
	
	if(var->mode == FUTURE_QUEUE)	{
		if(isQEmpty(&(var->head_getq),&(var->tail_getq)) && isQEmpty(&(var->head_setq),&(var->tail_setq)) )	{
			enQ(var->get_queue, getpid(), &(var->head_getq), &(var->tail_getq));
			//printf("\n get empty and set empty");
			var->state = FUTURE_WAITING;
			var->pid = getpid();
			suspend(getpid()); // BOTH EMPTY
			printf("");
			*val = var->value;	
			}
				
	
			restore(im);
			return OK;
		}
					//GETQ EMPTY  && SETQ !EMPTY
		if(isQEmpty(&(var->head_getq),&(var->tail_getq)) && !isQEmpty(&(var->head_setq),&(var->tail_setq)) )	{
			resume(var->set_queue[var->tail_setq]);
			//printf("\n get empty and set empty");
			deQ(var->set_queue, &(var->head_setq), &(var->tail_setq));
			var->state = FUTURE_WAITING;
			var->pid = getpid();
			printf("");
			*val = var->value;	
			restore(im);
			return OK;
			
		}			// BOTH ARE NOT EMPTY
		if(!isQEmpty(&(var->head_getq),&(var->tail_getq)) && !isQEmpty(&(var->head_setq),&(var->tail_setq)) )	{
			enQ(var->get_queue, getpid(), &(var->head_getq), &(var->tail_getq));
			var->state = FUTURE_WAITING;
			var->pid = getpid();
			suspend(getpid()); 
			printf("");
			*val = var->value;
			printf("\n get not empty and not set empty");
			restore(im);
			return OK;
		}
	
					//GET !EMPTY   and SETQ EMPTY	
		if(!isQEmpty(&(var->head_getq),&(var->tail_getq)) && isQEmpty(&(var->head_setq),&(var->tail_setq)) )	{
			enQ(var->get_queue, getpid(), &(var->head_getq), &(var->tail_getq));
			suspend(getpid()); 
			resume(var->set_queue[var->tail_setq]);
			//printf("\n get not empty and set empty");
			deQ(var->set_queue, &(var->head_setq), &(var->tail_setq));
			printf("");
			var->state = FUTURE_WAITING;
			var->pid = getpid();
			*val = var->value;	
			restore(im);
			return OK;
			
		}

	}
	return SYSERR;
}	