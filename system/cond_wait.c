#include <mutex.h>
#include <cond_var.h>
#include <kernel.h>

syscall cond_wait(volatile cond_t* cv,  mutex_t* lock)
  {

		qid16* q=cv;
		enqueue (getpid(), *q); /* enqueue */
		mutex_unlock(lock);
    	suspend (getpid());  /* Sleep 'til someone wakes us */
    	mutex_lock(lock); /* Woke up -- our turn, get resource lock */
    	return OK;
  }
