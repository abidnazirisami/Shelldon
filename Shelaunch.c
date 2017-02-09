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

int launch(char **arguments)											// Function for managing pipes and/or I/O redirection before executing
{
	int ind, background=0, size=100;
	int pipefd[2];														// File descriptor array for pipe
	int in=0;
	int out=1;															// in and out are two file descriptor initialized with default values for input and output
	char **args = malloc(size*sizeof(char *));
	int pos=0;
	char *inputFile=NULL;
	char *outputFile=NULL;
	char *appendFile=NULL;												// Arguments for I/O redirection
	
	for(ind=0;arguments[ind+1]!=NULL;ind++);							// For background processes
	if(strcmp(arguments[ind], "&")==0)
	{
		background=1;													// It means there is a background process
		arguments[ind]=NULL;
		printf("Background process activated\n");
	}
	
	
	// Pipe and I/O redirection:
	
	for(ind=0;arguments[ind]!=NULL;ind++)
	{
		if(strcmp(arguments[ind], "|")==0)								// When a pipe is encountered
		{
			args[pos]=NULL;												// The pointer array args now has the list of arguments this far
			
			pipe(pipefd);												// Pipe is used to create a channel between two file descriptors
			
			runProcess(args, in, pipefd[1], background);				// The argument encountered so far is executed and the output side of the pipe is
																		// used as the output file descriptor
																		
			in=pipefd[0];												// The other end of the pipe is saved as the input file descriptor for
																		// the next set of arguments
																		
			close(pipefd[1]);											// The file descriptor which was used is closed
			
			pos=0;														// The pointer array's position is reset to take a new set of arguments
		}
		else if(strcmp(arguments[ind],"<")==0)							// Taking inputs from a file
		{
			inputFile=arguments[ind+1];									// Taking the file as an argument
			in=open(inputFile, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);	// Which is then used to create the file descriptor for input
			args[pos]=NULL;
		}
		else if(strcmp(arguments[ind], ">")==0)							// Giving output to a file
		{
			outputFile=arguments[ind+1];								
			out=open(outputFile, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
			args[pos]=NULL;
			break;
		}
		else if(strcmp(arguments[ind], ">>")==0)						// Similarly appending to a file
		{
			appendFile=arguments[ind+1];
			out=open(appendFile, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);	// In both cases, output file descriptor is created with different
			args[pos]=NULL;																		// permissions and functionality
			break;
		}
		else
		{
			args[pos++]=arguments[ind];									// The arguments are being saved in a temporary pointer array
		}
	}	
	args[pos]=NULL;														
	runProcess(args, in, out, background);								// The temporary set of arguments is executed
	
	if(in!=0) close(in);												// If any file descriptor has been used, they're being closed here
	if(out!=1) close(out);
	return 1;															// When everything is executed, 1 tells the program that it can continue executing the next command
}
