#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include "minishell.h"


/* Build the prompt string to have the machine name,
 * current directory, or other desired information.
 */
void printPrompt() {
	char promptString[] = "mini shell >";
  	printf("%s",promptString);
}


/* This function searches the directories identified by the dir
 * argument to see if argv[0] (the file name) appears there.
 * Allocate a new string, place the full path name in it, then
 * return the string.
 */
char * lookupPath(char **argv, char **dir) {
	char *result;
	char pName[MAX_PATH_LEN];

	// Check to see if file name is already an absolute path
	//look if it begins with / .
	if( *argv[0] == '/') {
		return argv[0];
	}
	else if( *argv[0] == '.') {
		if( *++argv[0] == '.') {
			 if(getcwd(pName,sizeof(pName)) == NULL)
				 perror("getcwd(): error\n");
			 else {
				 *--argv[0];
				 asprintf(&result,"%s%s%s",pName,"/",argv[0]);
			 }
			 return result;
		}
		*--argv[0];
		if( *++argv[0] == '/') {
			if(getcwd(pName,sizeof(pName)) == NULL)
				perror("getcwd(): error\n");
			else {
				asprintf(&result,"%s%s",pName,argv[0]);
			}
			return result;
		}
	}

	// look in PATH directories
	int i;
	for(i = 0 ; i < MAX_PATHS ; i++ ) {
		if(dir[i] != NULL) {
			asprintf(&result,"%s%s%s",  dir[i],"/",argv[0]);
			if(access(result, X_OK) == 0) {
				return result;
			}
		}
		else {continue;}
	}

	// File name not found in any path variable
	fprintf(stderr, "%s: command not found\n", argv[0]);
	return NULL;
}

/*This function parses commandLine, build argv[] and argv value*/
int parseCommand(char * commandLine, struct command_t * command) {
	int debug = 0;

	char * pch;
	pch = strtok (commandLine," ");
	int i=0;
	while (pch != NULL) {
		command->argv[i] = pch;
		pch = strtok (NULL, " ");
		i++;
	}
	command->argc = i;
	command->argv[i++] = NULL;

	return 0;
}


/* This function reads the PATH variable for this
 * environment, then builds an array, dirs[], of the
 * directories in PATH
 */
int parsePath(char* dirs[]){
	char* pathEnvVar;
	char* thePath;
	int i;

	for(i=0 ; i < MAX_ARGS ; i++ ){
		dirs[i] = NULL;
	}
	pathEnvVar = (char*) getenv("PATH");
	thePath = (char*) malloc(strlen(pathEnvVar) + 1);
	strcpy(thePath, pathEnvVar);

	char* pch;
	pch = strtok(thePath, ":");
	int j=0;
	// loop through for ':' delimiter 
	while(pch != NULL) {
		pch = strtok(NULL, ":");
		dirs[j] = pch;
		j++;
	}
}

/*This function reads user input into commandLine*/
int readCommand(char * buffer, char * commandInput) {
	int debug = 0;
	buf_chars = 0;


	while((*commandInput != '\n') && (buf_chars < LINE_LEN)) {
		buffer[buf_chars++] = *commandInput;
		*commandInput = getchar();
	}
	buffer[buf_chars] = '\0';

	return 0;
}