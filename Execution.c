#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include "shell_header.h"

void runProcess(char **args, int in, int out, int background)			// Function which actually executes the process using fork and execvp
{
	
	// This part is for executing the builtin functions
	
	if(strcmp(args[0], "cd")==0)
	{
		execute_cd(args);
	}
	else if(strcmp(args[0], "help")==0)
	{
		execute_help();
	}
	else if(strcmp(args[0], "pwd")==0)
	{
		execute_pwd();
	}
	else if(strcmp(args[0], "exit")==0)
	{
		execute_exit();
	}
	else if(strcmp(args[0], "echo")==0)
	{
		execute_echo(args);
	}
	else {
		
		pid_t child_id;													// Process id of child
		
		int status;														// Running status of a process
		
		child_id=fork();												// A child process is created using fork
		
		if(child_id==0)													// Inside the child process
		{
			if(in!=0)													// If the file descriptor 'in' has been used, it's for replacing stdin
			{
				dup2(in,0);												// The file in file descriptor 'in' is now the input
				
				close(in);												// Closing after using the file descriptor
			}
			if(out!=1)													// If the file descriptor 'out' has been used, it's for replacing stdout
			{
				dup2(out,1);											// The file in file descriptor 'out' is now the output
				
				close(out);												// Closing after using the file descriptor
			}
			execvp(args[0], args); 										// Executing the arguments in the array, and the name of the command is in the first element
			
			perror("Error, Sheldon says");								// If it ever returns, it's because there was an error
			exit(EXIT_FAILURE);
			}
		else if(child_id<0) perror("Error, Sheldon says");				// Error in creating the child pid
		
		else 															// Inside the parent process
		{
			if(background==0) {											// Unless it's a background process, it needs to wait
				do {
				pid_t wait_id = waitpid(child_id, &status, WUNTRACED);	// Function for waiting
		
				} while(!WIFEXITED(status) && (!WIFSIGNALED(status)));
			}
		}
	}
	
}
