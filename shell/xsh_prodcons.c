<<<<<<< HEAD
#include <xinu.h>
#include <future.h>
#include <stdlib.h>

int n;                         //Definition for global variable 'n
sid32 consumed, produced;     //Definition for semaphores

shellcmd xsh_prodcons(int nargs, char *args[])
{

    n =0;

     /*Initialise semaphores*/
    consumed = semcreate(1);      
    produced = semcreate(0);

     /* Check argument count */

	if (nargs != 2) 
	{
		fprintf(stderr, "%s: incorrect number of arguments, need exactly two\n", args[0]);
        return 1;
	   
    }

    else
    {     
            /* Output info for '--help' argument */

	    if (2>1)
        {
			/*printf("Enter prodcons followed by -f\n");*/
			future_t *f_exclusive, *f_shared, *f_queue;
			f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
			f_shared = future_alloc(FUTURE_SHARED);
			f_queue = future_alloc(FUTURE_QUEUE);
		 
			// Test FUTURE_EXCLUSIVE
			resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
			resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );
			
			
			 //Test FUTURE_SHARED
		  resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
		  resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
		  resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
		  resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
		  resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );
		  
		  //Test FUTURE_QUEUE
		  resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
		 /* resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
		  resume( create(future_cons, 1024, 20, "fcons8", 1, f_queue) );
		  resume( create(future_cons, 1024, 20, "fcons9", 1, f_queue) );
		  resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );
		  resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );
		  resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );*/
		  resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) );
            return 0;
        }

	    if (nargs < 2)
			{
				fprintf(stderr, "%s: too few arguments\n", args[0]);
                fprintf(stderr, "Try '%s --help' for more information\n",args[0]);
                return 1;
			}

	if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
			args[0]);
		return 1;
	}      
		/*if(nargs == 2)
		{
	      future_t *f_exclusive, *f_shared, *f_queue;
 		  f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
		  /*f_shared = future_alloc(FUTURE_SHARED);
		  f_queue = future_alloc(FUTURE_QUEUE);*/
		 
		// Test FUTURE_EXCLUSIVE
		 /* resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
		  resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );
		   

		/* Test FUTURE_SHARED
		  resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
		  resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
		  resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
		  resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
		  resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );

	
		//Test FUTURE_QUEUE
		  resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
		  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
		  resume( create(future_cons, 1024, 20, "fcons8", 1, f_queue) );
		  resume( create(future_cons, 1024, 20, "fcons9", 1, f_queue) );
		  resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );
		  resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );
		  resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );
		  resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) ); */

	    //}
    }
return 0;
}
=======
#include <xinu.h>
#include <stdio.h> 
#include <string.h>

shellcmd xsh_prodcons(int nargs, char *args[]) {

	if (nargs == 2 && strcmp(args[1], "-f") == 0) {
		future_t* f_exclusive, *f_shared, *f_queue;

		// Test FUTURE_EXCLUSIVE
		f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
		resume(create(future_cons, 1024, 20, "fcons1", 1, f_exclusive));
		resume(create(future_prod, 1024, 20, "fprod1", 1, f_exclusive));
		//future_free(f_exclusive);

		// Test FUTURE_SHARED
		f_shared = future_alloc(FUTURE_SHARED);
		resume(create(future_cons, 1024, 20, "fcons2", 1, f_shared));
		resume(create(future_cons, 1024, 20, "fcons3", 1, f_shared));
		resume(create(future_cons, 1024, 20, "fcons4", 1, f_shared));
		resume(create(future_cons, 1024, 20, "fcons5", 1, f_shared));
		resume(create(future_prod, 1024, 20, "fprod2", 1, f_shared));
//		  future_free(f_shared);

// Test FUTURE_QUEUE
		f_queue = future_alloc(FUTURE_QUEUE);
		resume(create(future_cons, 1024, 20, "fcons6", 1, f_queue));
		resume(create(future_cons, 1024, 20, "fcons7", 1, f_queue));
		resume(create(future_cons, 1024, 20, "fcons7", 1, f_queue));
		resume(create(future_cons, 1024, 20, "fcons7", 1, f_queue));
		resume(create(future_prod, 1024, 20, "fprod3", 1, f_queue));
		resume(create(future_prod, 1024, 20, "fprod4", 1, f_queue));
		resume(create(future_prod, 1024, 20, "fprod5", 1, f_queue));
		resume(create(future_prod, 1024, 20, "fprod6", 1, f_queue));
//		  future_free(f_queue);

		return 0;
	} else if (nargs < 2) {
		fprintf(stderr, "%s: too few arguments\n", args[0]);
		fprintf(stderr, "Usage: 'prodcons  -f'\n");
		return 1;
	}else if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Usage: 'prodcons  -f'\n");
		return 1;
	}

	fprintf(stderr, "Usage: 'prodcons  -f'\n");
	return 0;
}
>>>>>>> afd95f39e2d82c17efec5a100d3624ef7985c62f
