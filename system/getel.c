#include <xinu.h>

uint32 listlen(qid16 q) {
	uint32 els  = 0;
	pid32  curr = queuetab[queuehead(q)].qnext;

	while (curr != queuetail(q)) {
		++els;
		curr = queuetab[curr].qnext;
	}

	return els;
}

pid32 getel(qid16 q, const uint32 index) {

	uint32 curr_index = 0;
	pid32  curr_pid   = queuetab[queuehead(q)].qnext;

	while (curr_pid != queuetail(q)) {
		if (index == curr_index) {
/*			kprintf("Attempting getitem on PID %d\n", curr_pid);*/
			return getitem(curr_pid);
		} else {
			++curr_index;
			curr_pid = queuetab[curr_pid].qnext;
		}
	}

	return NULLPROC;
}
