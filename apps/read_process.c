#include <xinu.h>

void read_process( sid32 written, sid32 clean){

//	printf("read process\n");
	wait(written);

	char *shmaddr;
	int16 shmid =  shmget( (int16)KEY, NULL , SHM_FETCH);

//	shmaddr = shmat(shmid, NULL, (int16)SHM_RDONLY);

	//	shmaddr = getmem(size);
	//	shmaddr = shmat(shmid,shmaddr, (int16)SHM_RND);
	shmaddr = shmat(shmid,NULL, (int16)SHM_RND);

//	kprintf("read process: shmat done\n");

	printf("Read \"%s\" from shared memory\n", shmaddr);
	signal(clean);
}
