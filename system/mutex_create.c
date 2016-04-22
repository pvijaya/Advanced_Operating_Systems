#include <xinu.h>

syscall mutex_init(mutex_t** lock)
{


	  *lock = NULL;
	  *lock = (_Bool *) getmem(sizeof(_Bool));
      **lock = UNLOCKED;

      return OK;
}
