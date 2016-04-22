#include<xinu.h>

local uint32 newidentifier(void);

int16 shmget(int16 key, uint32 size, int16 shmflag) {

	struct shment *shmptr;
	uint16 identifier;
	uint16 i;

	for (i = 0; i < NSHMENT; i++) {
		if (shmtab[i].key == key) {
			identifier = i;

			if (shmflag == SHM_EXIST|| shmflag ==  SHM_FETCH) {
				return identifier;
			}
			if (shmflag == SHM_CREAT) {
				return (uint16) SYSERR;
			}
		}
	}

	if (shmflag == SHM_FETCH) {
		return (uint16) SYSERR;
	}

	identifier = newidentifier();
	shmptr = &shmtab[identifier];
	shmptr->key = key;
	shmptr->size = size;
	shmptr->refcount = 0;
	shmptr->shmemory = (char *)getmem(size);
	return identifier;
}

local uint32 newidentifier(void) {
//	printf("Find an empty entry in shmtab\n");
	uint32 i;
	static uint32 nextiden = 0;

	for (i = 0; i < NSHMENT; i++) {
		nextiden %= NSHMENT; /* wrap around to beginning */
		if (shmtab[nextiden].refcount == SHMEMPTY) {
			return nextiden;
		} else {
			nextiden++;
		}
	}
	return (uint32) SYSERR;
}

