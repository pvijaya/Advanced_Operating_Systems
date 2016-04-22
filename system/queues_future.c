#include <xinu.h>
#include <future.h>

void enQ(int queue[LIMIT], pid32 pid, int* front, int* rear)
{
	if(*front == -1 && *rear == -1)	{
		queue[0] = pid;
		*front = 0;
		*rear = 0;
		return;
	}	
	
	if (*rear >-1 && *rear<(LIMIT-1))	{
		(*rear)++;
		queue[*rear] = pid;
		return;
	}
}
void deQ(int queue[LIMIT],int * front, int * rear)
{
	if(*front == -1 && *rear == -1)	{
		return;
	}
	if(*front >-1 && *rear > -1 && *front == *rear && *front < LIMIT)	{
		queue[*rear] = -1;
		*front = -1;
		*rear = -1;
		return;
	}	
	
	if (*front >-1 && *front<LIMIT)	{
		queue[*front] = -1;
		(*front)++;
		return;
	}
}
int isQEmpty(int* front, int* rear)
{
	if(*front == -1 && *rear == -1)
		return 1;
	return 0;
}

/*#include <xinu.h>
#include <future.h>

int getq_front = -1;
int getq_rear = -1;

int setq_front = -1;
int setq_rear = -1;

int gf_front = -1;
int gf_rear = -1;


int getenqueueue(int get_queueue[], pid32 pid)
{
	if (getq_rear == LIMIT -1) 
		return SYSERR;
	else
	{
		if (getq_front == -1)
			 getq_front = 0;
		getq_rear = getq_rear + 1;
		printf("rear pid enq %d %d\n",getq_rear, pid);
		get_queueue[getq_rear] = pid;
	}
	return 0;

}

pid32 getdequeueue(int get_queueue[])
{
	pid32 pid;
	if (getq_front == - 1 || getq_front > getq_rear)
      return SYSERR;
	else
	{
      pid = get_queueue[getq_front];
      getq_front = getq_front + 1;  
	  printf("rear pid enq %d %d\n",getq_front, pid);
      return pid;
    } 
}

int setenqueueue(int set_queueue[], pid32 pid)
{
	if (setq_rear == LIMIT-1) 
		return SYSERR;
	else
	{
		if (setq_front == -1)
			 setq_front = 0;
		setq_rear = setq_rear + 1;
		set_queueue[setq_rear] = pid;
	}
	return 0;

}
pid32 setdequeueue(int set_queueue[])
{
	pid32 pid;
	if (setq_front == - 1 || setq_front > setq_rear)
      return SYSERR;
	else
	{
      pid = set_queueue[setq_front];
      setq_front = setq_front + 1;  
      return pid;
    }
}

int getfutureq(int get_queueue[], pid32 pid)
{
	if (gf_rear == LIMIT -1) 
		return SYSERR;
	else
	{
		if (gf_front == -1)
			gf_front = 0;
		gf_rear = gf_rear + 1;
		get_queueue[gf_rear] = pid;
     }
	return 0;
}

pid32 getfuturedeq(int get_queueue[])
{
	pid32 pid;
	if (gf_front == - 1 || gf_front > gf_rear)
      return SYSERR;
	else
	{
      pid = get_queueue[gf_front];
      gf_front = gf_front + 1;  
      return pid;
     } 
	
}*/