#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include "minishell.h"
struct command_t command;


//executes regular command
int executeCommand() {
	int child_pid;

	child_pid = fork();
	if(child_pid < 0 ) {
		printf(stderr, "Fork fails \n");
		return 1;
	}
 	/* This is the child process */
	//???
	else if(child_pid==0) {
 		/* Create child and execute the command */
		execve(command.name, command.argv,0);
		printf("Process[%d]: child in execution ... \n",getpid());
 		sleep(1);
 		printf("Process[%d]: child terminating ... \n", getpid());
		exit(0); /* should never reach here */
	}
}


int main(int argc, char* argv[]) {
	int i;
	int debug = 0;

	/* Shell initialization */
  	parsePath(pathv); /* Get directory paths from PATH */

  	while(TRUE) {
    	
	printPrompt();
    
  	/* Read the command line and parse it */
	commandInput = getchar(); //gets first char
	if(commandInput == '\n') { // if not input 
		continue;
	}

	else{
		readCommand(commandLine, &commandInput); // read command
		
		//check for exit and quit in command line
		if((strcmp(commandLine, "exit") == 0) || (strcmp(commandLine, "quit") == 0)){
				break;
		}
		
		parseCommand(commandLine, &command); //parses command into array
		
		/* Get the full pathname for the file */
		command.name = lookupPath(command.argv, pathv);

		if(command.name == NULL) {
			/* Report error */
			printf("Error\n");
			continue;
		}

 /* Create child and execute the command - Wait for the child to terminate */

			executeCommand();
	}

  	}//end while

	/* Shell termination */
	/* When exit is typed */

	if (wait(NULL) > 0) /* child is terminating */
 	printf("Process[%d]: Parent detects terminating child\n", getpid());
 	printf("Process[%d]: Parent terminating ...\n",getpid());
 	return 0;
}
