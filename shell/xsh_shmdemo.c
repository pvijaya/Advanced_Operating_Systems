#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_shdemo - Shared memory demo
 *------------------------------------------------------------------------
 */
shellcmd xsh_shmdemo(int nargs, char *args[]) {


	/* Output info for '--help' argument */

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s <string>\n\n", args[0]);
		printf("Description:\n");
		printf("\tPrints welcome message to the <string>\n");
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}

	/* Check argument count */

	if (nargs < 2) {
		fprintf(stderr, "%s: too few arguments\n", args[0]);
                fprintf(stderr, "Try '%s --help' for more information\n",
                        args[0]);
                return 1;
	}

	if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
			args[0]);
		return 1;
	}


	char * message = args[1];
	
	sid32 written, clean;
	written  = semcreate(0);
	clean  = semcreate(0);
	
	resume(create(write_process, 1024, 20, "write_rocess", 3, written,clean,message));
	resume(create(read_process, 1024, 20, "read_rocess", 2, written,clean));
	
	
	return 0;
}

