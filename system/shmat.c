#include<xinu.h>

char *shmat(int16 shmid, char *shmaddr, int16 shmflag){

	struct shment *shmptr;
	shmptr = &shmtab[shmid];

//	kprintf("shmat\n");
	if (shmflag  == SHM_RDONLY){
		return shmptr->shmemory;
	}

	if (shmflag == SHM_RND){

		if (shmaddr == NULL){
			shmaddr = getmem((uint32)  shmptr->size);
		}
//		kprintf("creating shared pointero");

		shmaddr = shmptr->shmemory;
		shmptr->refcount++;
	}
	return shmaddr;
}
