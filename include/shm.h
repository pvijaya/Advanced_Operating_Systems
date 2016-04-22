#define HMENT 10
#define SHMEMPTY -1
#define SHM_CREAT 0x01
#define SHM_FETCH 0x02
#define SHM_EXIST (SHM_CREAT | SHM_FETCH)
#define SHM_RND 0x01
#define SHM_RDONLY 0x02
#define NSHMENT 10
#define SHMSIZE 1024

struct shment{
    int key, refcount, size;
    char *shmemory;
};

extern struct shment shmtab[];

//char *shmat(int16 ,char *, int16);
//char *shmdt(int16 ,int16);
//int16 shmget(int16, uint32, int16);
