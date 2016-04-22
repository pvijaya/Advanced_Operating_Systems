#include<xinu.h>

syscall cond_signal( cond_t* cv)
{
	qid16* q = cv;
	while (!isempty(*q)){
		resume(dequeue(*q));
	}
    return OK;
	
}
