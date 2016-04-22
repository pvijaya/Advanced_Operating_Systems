#include <ipc_bench.h>

//char * LEAD[NUM_ITRS] = { "/tmp/LEAD0", "/tmp/LEAD1", "/tmp/LEAD2",
//		"/tmp/LEAD3", "/tmp/LEAD4", "/tmp/LEAD5", "/tmp/LEAD6", "/tmp/LEAD7",
//		"/tmp/LEAD8", "/tmp/LEAD9" };
//char * FOLO[NUM_ITRS] = { "/tmp/FOLO0", "/tmp/FOLO1", "/tmp/FOLO2",
//		"/tmp/FOLO3", "/tmp/FOLO4", "/tmp/FOLO5", "/tmp/FOLO6", "/tmp/FOLO7",
//		"/tmp/FOLO8", "/tmp/FOLO9" };

int main() {
	printf(
			"Average time over %d iterations for sharing 4MiB data using different IPC methods:\n",
			NUM_ITRS);
	ipc_bench(SHM_IPC);
	ipc_bench(FILE_IPC);
	ipc_bench(PIP_IPC);
}

int ipc_bench(char * flag_str) {

	double time_elapced;
	struct shmid_ds ds;
	int semid, shmid;
	short sarray[NUMSEMS] = { 1, 1 };

//	if (argc < 2) {
//		printf(
//				"Please specifivy the IPC method.\nAvailable methotds:\nPIP\nFILE\nSHM\n");
//		exit(0);
//	}

	int flag;
	if (strcmp(flag_str, (char *) SHM_IPC) == 0) {

		key_t semkey = ftok(SLEADKEY, 'S');
		key_t shmkey = ftok(BUFKEY, 'B');
		semid = semget(semkey, NUMSEM, IPC_CREAT | IPC_EXCL);
		if (semid == -1) {
//			printf ("SEMMSL is %d \n",SEMMNI);
			perror("semget: semget failed");
			exit(1);
		}
		shmid = shmget(shmkey, MAX_BUF_SIZE * sizeof(int),
		IPC_CREAT | S_IRUSR | S_IWUSR);
		flag = SHM_IPC_ID;
	} else if (strcmp(flag_str, (char *) FILE_IPC) == 0) {
		flag = FILE_IPC_ID;
	} else if (strcmp(flag_str, (char *) PIP_IPC) == 0) {
		flag = PIP_IPC_ID;
	} else {
		printf(
				"BAD INPUT\nPlease specifivy the IPC method.\nAvailable methotds:\nPIP\nFILE\nSHM\n");
		exit(1);
	}

//	if (file_exist(LEAD_FILE_BUF)){
//		printf("exist\n");
//	}
//	exit(0);

	int itr;
	for (itr = 0; itr < NUM_ITRS; itr++) {
//		printf("Iteration %d\n", itr);

		switch (flag) {

		case PIP_IPC_ID:
			unlink(lead_pipfile(itr));
			unlink(follow_pipfile(itr));
			break;
		case FILE_IPC_ID:
			unlink(LOCK_FILE_LEAD);
			unlink(LOCK_FILE_FOLO);
			unlink(LEAD_FILE_BUF);
			unlink(FOLO_FILE_BUF);
			break;
		case SHM_IPC_ID:
			shmctl(shmid, IPC_STAT, &ds);
			semctl(semid, 0, SETVAL, sarray);
			break;
		default:
			exit(1);
		}

		pid_t pid = fork();
		if (pid == 0) {

			follow(itr, flag);
			exit(0);
		} else {

			double lead_time = 0;
			lead_time = lead(itr, flag);
			lead_time /= (double) NUM_ITRS;
			time_elapced += lead_time;
			wait(NULL);
		}
	}
	if (flag == SHM_IPC_ID) {
		semctl(semid, 1, IPC_RMID);
	}

	printf("> %s IPC: %f seconds\n", flag_str, time_elapced);

	return 0;
}

int verify(int rdbuf[], int offset) {

	int i;
	for (i = 0; i < MAX_BUF_SIZE; i++) {
		if (rdbuf[i] != offset + i) {

			printf("ERROR. RECEIVED:\n");
			for (i = 0; i < MAX_BUF_SIZE; i++) {
				printf("%d ", rdbuf[i]);
			}
			printf("\n");
			return 0;
		}
	}
	return 1;
}

int lead_offset(int itr) {
	return (2 * itr);
}

int follow_offset(int itr) {
	return (1 + (2 * itr));
}

char* lead_pipfile(int itr) {
//	return LEAD[0];
	return LEAD;
}

char* follow_pipfile(int itr) {
//	return FOLO[0];
	return FOLO;
}

int file_exist(char *filename) {
	struct stat buffer;
	return (stat(filename, &buffer) == 0);
}

