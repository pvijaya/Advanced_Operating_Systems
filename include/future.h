<<<<<<< HEAD
#ifndef _FUTURE_H_
#define _FUTURE_H_  


#define LIMIT 10

//extern int getq_front, getq_rear, setq_front, setq_rear, gf_front, gf_rear;

typedef enum {
  FUTURE_EMPTY,
  FUTURE_WAITING,
  FUTURE_READY
} future_state_t;

typedef enum {
  FUTURE_EXCLUSIVE,
  FUTURE_SHARED,
  FUTURE_QUEUE
}future_mode_t;

typedef struct {
  int value;
  future_state_t state;
  future_mode_t mode;
  //int tid;
  int head_getq;
  int tail_getq;
  int head_setq;
  int tail_setq;
  pid32 pid;
  /*queue set_queue;
  queue get_queue;*/
  int get_queue[LIMIT];
  int set_queue[LIMIT];
} future_t;

/* Interface for the Futures system calls */
future_t* future_alloc(future_mode_t mode);
syscall future_free(future_t*);
syscall future_get(future_t*, int*);
syscall future_set(future_t*, int*);

/*implementation of queue
int getenqueue(int get_queue[], pid32 pid);
pid32 getdequeue(int get_queue[]);

int setenqueue(int set_queue[], pid32 pid);
pid32 setdequeue(int set_queue[]);

int getfutureq(int get_queue[], pid32 pid)
pid32 getfuturedeq(int get_queue[])

//===================================*/

  /*function Prototype*/
uint32 future_cons(future_t *fut);
uint32 future_prod(future_t *fut);

/* Queue function prototypes */

void enQ(int queue[LIMIT], pid32 pid, int * head, int * tail);
void deQ(int queue[LIMIT], int * head, int * tail);
int isQEmpty(int * head, int * tail);

#endif /* _FUTURE_H_ */
=======

#ifndef _FUTURE_H_
#define _FUTURE_H_  


typedef enum {
  FUTURE_EMPTY,
  FUTURE_WAITING,
  FUTURE_VALID
} future_state_t;

typedef enum {
  FUTURE_EXCLUSIVE,
  FUTURE_SHARED,
  FUTURE_QUEUE
} future_mode_t;

typedef struct {
  int value;
  future_state_t state;
  future_mode_t mode;
  pid32 pid;
  qid16 set_queue;
  qid16 get_queue;
} future_t;

/* Interface for the Futures system calls */
future_t* future_alloc(future_mode_t mode);
syscall future_free(future_t*);
syscall future_get(future_t*, int*);
syscall future_set(future_t*, int);

uint16 future_prod(future_t* fut);
uint16 future_cons(future_t* fut);
#endif /* _FUTURE_H_ */
>>>>>>> afd95f39e2d82c17efec5a100d3624ef7985c62f
