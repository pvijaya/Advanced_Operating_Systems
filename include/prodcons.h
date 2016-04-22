
#include<mutex.h>
#include<cond_var.h>

void consumer_(int id, int count_to_eat, mutex_t* lock, cond_t* empty, cond_t* fill, int *total_eaten,  int *dish, int total_to_be_produced );
void producer_(int count_to_produce, int totl_to_be_produced,  mutex_t* lock,  cond_t* empty, cond_t* fill,  int *dish);
