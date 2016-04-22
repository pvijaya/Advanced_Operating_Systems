/* xsh_led.c - xsh_led */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <prodcons.h>


/*------------------------------------------------------------------------
 * xsh_babybird - shell command to simulates the baby birds problem
 *------------------------------------------------------------------------
 */
shellcmd xsh_babybird(int nargs, char *args[])
{
	char	*chptr;			/* Walks through argument	*/
	char	ch;			/* Next character of argument	*/
	int num_baby_birds, num_fetch_worms, num_eat_worms, total_to_be_produced;

	/* For argument '--help', emit help about the 'led' command	*/

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Use: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tSimulates the baby birds problem\n");
		printf("Input argumenst:\n");
		printf("\t<num_baby_birds>\tnumber of baby birds\n");
		printf("\t<num_fetch_worms>\tnumber of worms parents should put in the dish when it becomes empty\n");
		printf("\t<num_eat_worms>\tnumber of total worms to be eaten by each bird\n");
		printf("\t--help\t display this help and exit\n");
		return 0;
	}

	if (nargs != 4) {
			fprintf(stderr, "%s: too many/few arguments\n", args[0]);
					fprintf(stderr, "Try '%s --help' for more information\n",
						args[0]);
					return 1;
	}

	num_baby_birds= num_fetch_worms= num_eat_worms=0;
	if (nargs == 4) {

		int i;
		for (i = 1; i < 4; i++){
			chptr = args[i];
			ch = *chptr++;
			while (ch != NULLCH) {
				if ( (ch < '0') || (ch > '9') ) {

					fprintf(stderr, "%s: nondigit in argument\n",args[0]);
					printf("\t--help\t display this help and exit\n");
					return 1;
				}

				if(i == 1)
					num_baby_birds = 10*num_baby_birds + (ch - '0');
				else if(i == 2)
					num_fetch_worms = 10*num_fetch_worms + (ch - '0');
				else if(i == 3)
					num_eat_worms = 10*num_eat_worms + (ch - '0');

				ch = *chptr++;
			}
		}
	}


	total_to_be_produced = num_baby_birds*num_eat_worms;


	mutex_t* lock;
	mutex_init(&lock);


	cond_t* empty;
	cond_init(&empty);

	cond_t* fill;
	cond_init(&fill);

	int *total_eaten, *dish;
//	printf("total_to_be_produced %d \n", total_to_be_produced);

	total_eaten = (int *) getmem(sizeof(int));
	*total_eaten = 0;

	dish = (int *) getmem(sizeof(int));
	*dish = 0;

	char thread_name[10];
	sprintf(thread_name,"parent");
	resume(create(producer_,256,20,thread_name,6, num_fetch_worms, total_to_be_produced, lock, empty,fill, dish ));

	int thread_id;
	for (thread_id = 0 ; thread_id < num_baby_birds; thread_id++){

		char thread_name[10];
		sprintf(thread_name,"%d",thread_id);
		resume(create(consumer_, 256, 20, thread_name , 8, thread_id, num_eat_worms, lock, empty, fill, total_eaten, dish,total_to_be_produced));
	}



	while((*total_eaten) < total_to_be_produced-1){
//		printf("total_eaten %d \n", (*total_eaten));
	}
//	printf("total_eaten %d \n", *total_eaten);
//	printf("total_to_be_produced %d \n", total_to_be_produced);

	return 0;
}
