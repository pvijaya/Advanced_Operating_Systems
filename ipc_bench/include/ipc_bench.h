#include <stdio.h>
#include <unistd.h> /* for fork */
#include <sys/wait.h> /* for wait */
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define LEAD     "/tmp/LEAD"
#define FOLO     "/tmp/LEAD"
#define MAX_BUF_SIZE 1048575//(int) pow(2,20)-1

int rdbuf[MAX_BUF_SIZE];
int wrbuf[MAX_BUF_SIZE];

#define BILLION 1000000000.0

#define SHM_IPC "SHM"
#define FILE_IPC "FILE"
#define PIP_IPC "PIP"

#define SHM_IPC_ID 0
#define FILE_IPC_ID 1
#define PIP_IPC_ID 2

#define NUMSEMS 2

#define NUM_ITRS 20

#define FILE_MODE (S_IRUSR | S_IRGRP | S_IROTH)
#define readw_lock(fd, offset, whence, len)lock_file(fd, F_SETLKW, F_RDLCK, offset, whence, len)
#define writew_lock(fd, offset, whence, len) lock_file(fd, F_SETLKW, F_WRLCK, offset, whence, len)
#define un_lock(fd, offset, whence, len) lock_file(fd, F_SETLK, F_UNLCK, offset, whence, len)

#define LOCK_FILE_LEAD "/tmp/lead.lck"
#define LOCK_FILE_FOLO "/tmp/folo.lck"
#define FOLO_FILE_BUF "/tmp/folobuf.txt"
#define LEAD_FILE_BUF "/tmp/leadbuf.txt"

double lead(int itr, int flag);
unsigned int follow(int itr, int flag);

int verify(int rdbuf[], int offset);
int lead_offset(int itr);
int follow_offset(int itr);

char* lead_pipfile(int itr);
char* follow_pipfile(int itr);

int lock_file(int fd, int cmd, int type, off_t offset, int whence, off_t len);

int file_exist(char *filename);

#define SLEADKEY "SEM"
#define BUFKEY "BUF"

//struct sembuf down = {0, -1, SEM_UNDO}, up = {0, 1, SEM_UNDO};

#define LEADSEM 0
#define FOLOSEM 1

#define NUMSEM 2
