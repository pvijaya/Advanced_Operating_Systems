#ifndef _FUT_Q_H_
#define _FUT_Q_H_

#include <xinu.h>

typedef struct qu_cell {
	pid32 index;
	qid16 *nxt;
} qu_cell;

typedef struct future_Q {
	qu_cell *head, *tail;
} future_Q;

future_Q *Q_create();
qu_cell* future_node(pid32);
int32 enQ(future_Q *, pid32);
pid32 deQ(future_Q *);
int32 QisEmp(future_Q *);

#endif
