#include<xinu.h>

char *shmdt(int16 shmid, int16 shmflag){

	struct  shment *shmptr = &shmtab[shmid];
	freemem(shmptr->shmemory, shmptr->size);

	shmptr->key = SHMEMPTY;
	shmptr->size=SHMEMPTY;
	shmptr->refcount=SHMEMPTY;
	shmptr->shmemory=SHMEMPTY;
}
