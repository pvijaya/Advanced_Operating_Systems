#include <xinu.h>

syscall mutex_unlock( mutex_t* lock){
	*lock = UNLOCKED;
	return OK;
}
