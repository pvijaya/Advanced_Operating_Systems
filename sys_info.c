/* Taken inspiration from http://stackoverflow.com/questions/16500247/c-system-calls-pipe-fork-and-execl */

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv){
   int file_descriptor[2];
   char buffer[95];
      
   if(pipe(file_descriptor) == -1){
      perror("creating pipe failure");
      exit(EXIT_FAILURE);
   }
    if (argc != 2) {
    fprintf(stderr, "Should use one argument: %s <string>\n", argv[0]);
    exit(EXIT_FAILURE);
    }

   switch (fork()){
	//child
    case 0:
       close(file_descriptor[1]); 
       read(file_descriptor[0],buffer,strlen(argv[1])+1);
	   printf("Parent PID: %u \n", getppid());
	   printf("Child PID: %u \n", getpid());
	   if(strcmp(argv[1],"date")==0)
	   {   
		execl("/usr/bin/date","date",(char *)0);
	   }
	   else if(strcmp(argv[1],"uname")==0)
	   {   
		execl("/usr/bin/uname","uname",(char *)0);
	   }
	   else if(strcmp(argv[1],"hostname")==0)
	   {   
		execl("/usr/bin/hostname","hostname",(char *)0);
	   }
	   else if(strcmp(argv[1],"echo")==0)
		{   
		execl("/usr/bin/echo","echo","Hello World!",(char *)0);
	   } 
	   else
	   {  
	   perror("execl() system call failed");
	   }
       break;
	   
	  //fork failure
      case -1: 
       perror("fork failure");
       exit(EXIT_FAILURE);
		
		//parent 
      default: 
       close(file_descriptor[0]); 
       write(file_descriptor[1],argv[1], strlen(argv[1])+1);
	   wait(NULL);
   }   

   return 0;
}