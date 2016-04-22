#include <ipc_bench.h>

unsigned int follow_pip(int itr) { //, int *rdbuf, int *wrbuf) {

	int i, nbytes_read;
	int follow_write_fd, follow_read_fd;

	follow_read_fd = open(lead_pipfile(itr), O_RDONLY | O_CREAT);
	if (follow_read_fd < 0)
		printf("follow_pip Error opening follow_read_fd: %s\n",
				strerror( errno));

	nbytes_read = 0;
	int read_count;
	for (i = 0; i < MAX_BUF_SIZE; i++) {

		do {
			read_count = read(follow_read_fd, &rdbuf[i], sizeof(int));
		} while (read_count < 4);
		nbytes_read += read_count;
	}
	close(follow_read_fd);

//	printf("follow itr %d read %d: ", itr, nbytes_read);

//	unlink(follow_pipfile(itr));
	mkfifo(follow_pipfile(itr), S_IRUSR | S_IWUSR);
	follow_write_fd = open(follow_pipfile(itr), O_WRONLY | O_CREAT | O_TRUNC);
	if (follow_write_fd < 0)
		printf("follow_pip Error opening follow_write_fd: %s\n",
				strerror( errno));
	write(follow_write_fd, wrbuf, MAX_BUF_SIZE * sizeof(int));
	close(follow_write_fd);

	return 1;
}

unsigned int follow_file(int itr) {

	int fd, lockfd;

	/* Spin until lock is acquired */
	while (!file_exist(LEAD_FILE_BUF)) {
//		printf("FOLLOW SPINING 1\n");
	}
	while (-1 == (lockfd = open(LOCK_FILE_LEAD, O_CREAT | O_EXCL))) {
//		printf("FOLLOW SPINING 2\n");
	}

	/* Begin critical section */
//	printf("FOLLOW CS 1\n");
	fd = open(LEAD_FILE_BUF, O_CREAT | O_RDONLY);
	int nbytes_read;
	do {
		nbytes_read = read(fd, rdbuf, MAX_BUF_SIZE * sizeof(int));
	} while (nbytes_read < MAX_BUF_SIZE * sizeof(int));
//	printf("follow itr %d read %d: \n", itr, nbytes_read);
	close(fd);

//	printf("FOLLOW CS 1 DONE\n");
	/* End critical section */

	/* Release lock */
	close(lockfd);
	unlink(LOCK_FILE_LEAD);

	/* Acquire lock */
	if (-1 == (lockfd = open(LOCK_FILE_FOLO, O_CREAT | O_EXCL))) {
		perror("Locking failes\n");
		exit(errno);
	}

	/* Begin critical section */
//	printf("FOLLOW CS 1\n");
	fd = open(FOLO_FILE_BUF, O_CREAT | O_WRONLY);
	write(fd, wrbuf, MAX_BUF_SIZE * sizeof(int));
	close(fd);
	/* End critical section */

	/* Release lock */
	close(lockfd);
	unlink(LOCK_FILE_FOLO);

	return 1;
}

unsigned int follow_shm(int itr) {
	int semid, shmid;

	struct sembuf down = { LEADSEM, -1, SEM_UNDO };
	struct sembuf up = { FOLOSEM, 1, SEM_UNDO };

	key_t semkey = ftok(SLEADKEY, 'S');
	key_t shmkey = ftok(BUFKEY, 'B');
	semid = semget(semkey, NUMSEM, IPC_CREAT);
	shmid = shmget(shmkey, MAX_BUF_SIZE * sizeof(int),
	IPC_CREAT | S_IRUSR | S_IWUSR);
	int * buf = (int *) shmat(shmid, 0, 0);

	semop(semid, &down, 1);
//	printf("follow is reading\n");
	int i;
	for (i = 0; i < MAX_BUF_SIZE; i++) {
		rdbuf[i] = buf[i];
	}


//	printf("follow read\n");

	int offset = lead_offset(itr);
	for (i = 0; i < MAX_BUF_SIZE; i++) {
		buf[i] = wrbuf[i];
	}
//	printf("follow done\n");
	semop(semid, &up, 1);

	shmdt(buf);
	return 0;
}

unsigned int follow(int itr, int flag) {

	int offset = follow_offset(itr);
	int i;
	for (i = 0; i < MAX_BUF_SIZE; i++) {
		wrbuf[i] = i + offset;
	}

	switch (flag) {
	case FILE_IPC_ID:
		follow_file(itr);
		break;
	case PIP_IPC_ID:
		follow_pip(itr);
		break;
	case SHM_IPC_ID:
		follow_shm(itr);
		break;
	default:
		return 0;
	}

	struct timespec start, end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	if (verify(rdbuf, lead_offset(itr)) == 0) {
		perror("Follower received unexpected message\n");
		exit(0);
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	unsigned int verify_time_elapced = ((end.tv_sec - start.tv_sec)
			+ (end.tv_nsec - start.tv_nsec)) / BILLION;

	return verify_time_elapced;
}

