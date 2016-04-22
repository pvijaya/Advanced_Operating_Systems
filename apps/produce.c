#include <xinu.h>


void producer_(int count_to_produce, int totl_to_be_produced,  mutex_t* lock,  cond_t* empty, cond_t* fill,  int *dish) {


	int total_produced = 0;
	while (total_produced < totl_to_be_produced){
		mutex_lock(lock);

		while(*dish != 0){
			cond_wait(fill,lock);
		}

		*dish = count_to_produce;
//		printf("dish %d\n",*dish);
		total_produced += count_to_produce;
		cond_signal(empty);
		printf("Parent bird filled the dish with %d worms!\n",count_to_produce);
		mutex_unlock(lock);
	}
//	printf("Parent is done\n");
}
