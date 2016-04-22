#include <stdint.h>

#define LOCKED 1
#define UNLOCKED 0

typedef _Bool mutex_t;
_Bool TestAndSet( mutex_t* lock);
