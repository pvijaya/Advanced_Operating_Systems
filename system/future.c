#include <xinu.h>

future_t* future_alloc(future_mode_t mode) {
	future_t* fut_pointer = NULL;
	intmask mask = disable();

	fut_pointer = (future_t*) getmem(sizeof(future_t));

	// Initialising the future to initial state
//	if (fut_pointer != NULL) {
	fut_pointer->value = (int) NULL;
	fut_pointer->mode = mode;
	fut_pointer->pid = NULL;
	fut_pointer->state = FUTURE_EMPTY;
	fut_pointer->get_queue = newqueue();
	fut_pointer->set_queue = newqueue();
//	}
	restore(mask);
	return fut_pointer;
}

// Free the future and destroy queue

syscall future_free(future_t* f) {
	return freemem(f, sizeof(future_t));
}

// the processes or threades in get_queue

syscall future_get(future_t* f, int32* value) {
	intmask mask;
	mask = disable();
	if (f->mode == FUTURE_EXCLUSIVE) {
		if (f->state != FUTURE_VALID) {
			f->state = FUTURE_WAITING;
			f->pid = getpid();
			suspend(getpid());
		}

		*value = f->value;
		f->state = FUTURE_EMPTY;

		restore(mask);
		return OK;
	} else if (f->mode == FUTURE_SHARED) {

		if (f->state != FUTURE_VALID) {
			f->state = FUTURE_WAITING;
			enqueue(getpid(), f->get_queue);
			suspend(getpid());
		}
		*value = f->value;

		restore(mask);
		return OK;
	} else if (f->mode == FUTURE_QUEUE) {

		if (isempty(f->set_queue)) {
			f->state = FUTURE_WAITING;
			enqueue(getpid(), f->get_queue);
		} else {
			f->state = FUTURE_WAITING;
			resume(dequeue(f->set_queue));
			enqueue(getpid(), f->get_queue);
		}
		suspend(getpid());
		*value = f->value;

		restore(mask);
		return OK;
	}
	restore(mask);
	return SYSERR;
}
// threads to set the value

syscall future_set(future_t* f, int32 value) {
	intmask mask = disable();

	if (f->mode == FUTURE_EXCLUSIVE) {

		f->value = value;

		if (f->state == FUTURE_WAITING) {
			f->state = FUTURE_VALID;
			resume(f->pid);
		} else {
			f->state = FUTURE_VALID;
		}
		restore(mask);
		return OK;
	} else if (f->mode == FUTURE_SHARED) {

		f->value = value;

		if (f->state == FUTURE_WAITING) {
			f->state = FUTURE_VALID;
			while (!isempty(f->get_queue)) {
				resume(dequeue(f->get_queue));
			}
		}
		f->state = FUTURE_VALID;

		restore(mask);
		return OK;
	} else if (f->mode == FUTURE_QUEUE) {

		if (isempty(f->get_queue)) {

			enqueue(getpid(), f->set_queue);
			suspend(getpid());
		}
		f->value = value;
		f->state = FUTURE_VALID;
		resume(dequeue(f->get_queue));

		restore(mask);
		return OK;
	}

	restore(mask);
	return SYSERR;
}
