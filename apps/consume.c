#include <xinu.h>

void consumer_(int id, int count_to_eat, mutex_t* lock, cond_t* empty, cond_t* fill, int *total_eaten,  int *dish, int total_to_be_produced) {

	int eaten = 0;
	int old_total_eaten=-1;
	while (eaten < count_to_eat){

		mutex_lock(lock);

		while(*dish == 0){
			cond_wait(empty,lock);
		}

		if (old_total_eaten != *total_eaten || (count_to_eat-eaten) == (total_to_be_produced - *total_eaten)){

			(*dish)--;
			//printf("dish %d\n",dish);
//			printf("dish %d\n",*dish);
			eaten++;
			printf("Baby bird %d ate a worm!\n",id);
			(*total_eaten)++;
//			printf("total_eaten %d \n", *total_eaten);
			old_total_eaten = *total_eaten;
			if (*dish == 0 ){
				cond_signal(fill);
			}
		}

		mutex_unlock(lock);
	}
//	printf("Bird %d is done\n",id);
}
