#include <ipc_bench.h>

unsigned int lead_pip(int itr) {

	int i, nbytes_read;
	int lead_write_fd, lead_read_fd;

//	unlink(lead_pipfile(itr));
	mkfifo(lead_pipfile(itr), S_IRUSR | S_IWUSR);
	lead_write_fd = open(lead_pipfile(itr), O_WRONLY | O_CREAT | O_TRUNC);
	if (lead_write_fd < 0)
		printf("lead_pip Error opening lead_write_fd: %s\n", strerror( errno));
	write(lead_write_fd, wrbuf, MAX_BUF_SIZE * sizeof(int));
	close(lead_write_fd);

	lead_read_fd = open(follow_pipfile(itr), O_RDONLY | O_CREAT);
	if (lead_read_fd < 0)
		printf("lead_pip Error opening lead_read_fd: %s\n", strerror( errno));

	nbytes_read = 0;
	int read_count;
	for (i = 0; i < MAX_BUF_SIZE; i++) {
		do {
			read_count = read(lead_read_fd, &rdbuf[i], sizeof(int));
		} while (read_count < 4);
		nbytes_read += read_count;
	}
	close(lead_read_fd);
//	printf("lead itr %d read %d: ", itr, nbytes_read);

	return 1;
}

unsigned int lead_file(int itr) {

	int fd, lockfd;

	/* Acquire lock */
	if (-1 == (lockfd = open(LOCK_FILE_LEAD, O_CREAT | O_EXCL))) {
		perror("Locking failes\n");
		exit(errno);
	}

	/* Begin critical section */
//	printf("LEAD CS 1\n");
	fd = open(LEAD_FILE_BUF, O_CREAT | O_WRONLY);
	write(fd, wrbuf, MAX_BUF_SIZE * sizeof(int));
	close(fd);
	/* End critical section */

	/* Release lock */
	close(lockfd);
	unlink(LOCK_FILE_LEAD);

	/* Spin until lock is acquired */
	while (!file_exist(FOLO_FILE_BUF)) {
//		printf("LEAD SPINING 1\n");
	}
	while (-1 == (lockfd = open(LOCK_FILE_FOLO, O_CREAT | O_EXCL))) {
//		printf("LEAD SPINING 2\n");
	}

	/* Begin critical section */
//	printf("LEAD CS 2\n");
	fd = open(FOLO_FILE_BUF, O_CREAT | O_RDONLY);
	int nbytes_read;
	do {
		nbytes_read = read(fd, rdbuf, MAX_BUF_SIZE * sizeof(int));
	} while (nbytes_read < MAX_BUF_SIZE * sizeof(int));
//	printf("lead itr %d read %d: \n", itr, nbytes_read);
	close(fd);

	/* End critical section */

	/* Release lock */
	close(lockfd);
	unlink(LOCK_FILE_FOLO);
	return 1;

}

unsigned int lead_shm(int itr) {
	int semid, shmid;

	struct sembuf down = {FOLOSEM, -1, SEM_UNDO};
	struct sembuf up = {LEADSEM, 1, SEM_UNDO};

	key_t semkey = ftok(SLEADKEY, 'S');
	key_t shmkey = ftok(BUFKEY, 'B');
	semid = semget(semkey, NUMSEM, IPC_CREAT);
	shmid = shmget(shmkey, MAX_BUF_SIZE * sizeof(int),
	IPC_CREAT | S_IRUSR | S_IWUSR);
	int * buf = (int *) shmat(shmid, 0, 0);

//	printf("lead is writing\n");
	int offset = lead_offset(itr);
	int i;
	for (i = 0; i < MAX_BUF_SIZE; i++) {
		buf[i] = wrbuf[i];
	}

	semop(semid, &up, 1);
//	printf("lead wrote\n");
//	for (i = 0; i < MAX_BUF_SIZE; i++) {
//		printf("%d ",buf[i]);
//	}
//	printf("\n");
	semop(semid, &down, 1);
//	printf("lead is reading\n");
	for (i = 0; i < MAX_BUF_SIZE; i++) {
		rdbuf[i] = buf[i];
	}

	shmdt(buf);

	return 0;
}

double lead(int itr, int flag) {

	struct timespec start, end;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

	int offset = lead_offset(itr);
	int i;
	for (i = 0; i < MAX_BUF_SIZE; i++) {
		wrbuf[i] = i + offset;
	}

	switch (flag) {
	case FILE_IPC_ID:
		lead_file(itr);
		break;
	case PIP_IPC_ID:
		lead_pip(itr);
		break;
	case SHM_IPC_ID:
		lead_shm(itr);
		break;
	default:
		return 0;
	}

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

	if (verify(rdbuf, follow_offset(itr)) == 0) {
		printf("Leader received unexpected message\n");
		exit(0);
	}

	double time_elapced = (double) (end.tv_sec - start.tv_sec)
			+ (double) (end.tv_nsec - start.tv_nsec) / BILLION;
//	printf("time_elapced: %f\n", time_elapced);
	return time_elapced;
}

