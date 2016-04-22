#include <xinu.h>

void write_process(sid32 written, sid32 clean,char * message ){

//	printf("write process\n");


	char *shmaddr;
	uint32 size = (uint32)strlen(message);
	int16 shmid =  shmget( (int16)KEY, size , SHM_CREAT);

	//shmaddr = shmat(shmid, NULL, (int16)SHM_RDONLY);

	shmaddr = getmem(size);
	//shmaddr = shmat(shmid,shmaddr, (int16)SHM_RND);
	shmaddr = shmat(shmid,NULL, (int16)SHM_RND);

	//	kprintf("write process: shmat done\n");
	sprintf(shmaddr,message);
	//	kprintf("write process: message is written to shm\n");
	signal(written);
	wait(clean);
	shmdt(shmid, (int16)NULL);
}
