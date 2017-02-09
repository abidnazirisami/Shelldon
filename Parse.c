#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char **paarse(char *str)												// Function to parse the commands
{
	int size=100, ind=0;
	char *arg; 															// For each single argument
	
	char **args = malloc(sizeof(char*) * size);							// An array of arguments, or pointers where arguments ar kept
	
	if(!args)															// Error in memory allocation
	{
		fprintf(stderr, "Sheldon: allocation error\n");
		exit(EXIT_FAILURE);
	}
	
	arg = strtok(str, " \t\r\n\a");										// The argument string is seperated using the given seperating arguments as parameter
	
	while(arg!=NULL)													// Until there are no arguments left to parse
	{
		args[ind++]=arg;												// Every single argument is taken into the array of arguments
		
		if(ind == size-5)												// Re-allocation
		{
			size += 100;
			args = realloc(args, size * sizeof(char*));					
			if(!args)													// Re-allocation error
			{
				fprintf(stderr, "Sheldon: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		
		arg = strtok(NULL, " \t\r\n\a");								// The next argument is seperated and ready to be pushed into the array
	}
	args[ind]=NULL;														// Defining the end of arguments
	
	if(strcmp(args[0], "ls")==0)										// This part adds colors to the ls command to differentiate between
	{																	// files and folders easily
		if(args[1]==NULL)
		{
			args[1]= "--color";
			args[2]=NULL;
		}																
		else if(strcmp(args[1], "-l")==0  && args[2]==NULL|| strcmp(args[1], "-a")==0 && args[2]==NULL)
		{
			args[2]= "--color";
			args[3]=NULL;
		}
	}
	
	return args;
}
