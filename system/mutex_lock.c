#include <xinu.h>

_Bool TestAndSet( mutex_t* lock){

	_Bool return_val = 0;

	intmask mask = disable();//Disable interrupts

    if (*lock == UNLOCKED){
    	return_val = 1;
    	*lock = LOCKED;
    }

    restore(mask);//restore interrupts
    return return_val;
}

syscall mutex_lock( mutex_t* lock)
{
	while (!TestAndSet(lock));
	return OK;
}

