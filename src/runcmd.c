#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "runcmd.h"
#include "parser.h"
#include "prochelp.h"
#include "config.h"
#include "builtins.h"
#include "main.h"
#include "signals.h"

int command(int input, int first, int last, char **args)
{
	pid_t pid;
	int pipettes[2];
 
 	pipe( pipettes );	
	pid = fork();

	if (pid == 0) {
		unhandle_signal(SIGINT);
		
		if (first == 1 && last == 0 && input == 0) {
			dup2(pipettes[WRITE], STDOUT_FILENO);
		} else if (first == 0 && last == 0 && input != 0) {
			dup2(input, STDIN_FILENO);
			dup2(pipettes[WRITE], STDOUT_FILENO);
		} else {
			dup2( input, STDIN_FILENO );
		}
 
		if (execvp( args[0], args) == -1)
		{
			switch(errno)
			{
				case EPERM:
					fprintf(stderr, "%s: %s: Access denied!\n", CFG_SHORT_NAME, args[0]);
					break;
				case ENOENT:
					fprintf(stderr, "%s: %s: No such file or directory!\n", CFG_SHORT_NAME, args[0]);
					break;
				default:
					fprintf(stderr, "%s, %s: Unknown execution error!\n", CFG_SHORT_NAME, args[0]);
					break;
			}
			free(args);
			uninit_shell();
			_exit(EXIT_FAILURE);
		}
		free(args);
		uninit_shell();
	}
 
	if (input != 0) 
		close(input);
 
	close(pipettes[WRITE]);
 
	if (last == 1)
		close(pipettes[READ]);
		
	return pipettes[READ];
}

int run(char* cmd, int input, int first, int last)
{
	char **args = NULL;
	int retval = -1;

	args = split(cmd);
	
	if(args == NULL)
	{
		free(args);
		return -1;
	}
	
	if (args[0] != NULL) {
		if(check_builtin(args[0]) == TRUE && args[0][strlen(args[0])-1] != '^')
			return run_builtin(args);
		if(args[0][strlen(args[0])-1] == '^')
		{
			printf("WARN: Overriding builtin function!\n");
			args[0][strlen(args[0])-1] = '\0';
		}
		register_process();
		retval = command(input, first, last, args);
		free(args);
		return retval;
	}
	
	free(args);
	return -1;
}
