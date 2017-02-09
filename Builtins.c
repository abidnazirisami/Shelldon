#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// This file contains the builtin functions

void execute_cd(char **array_of_args)									// For executing the command 'cd'
{
	if(array_of_args[1] == NULL)
			{
				fprintf(stderr, "Sheldon: expected argument to \"cd\"\n");
			}
			else if(chdir(array_of_args[1]) != 0)						// Using chdir to change directory, if 0 is returned, there was an error
			{
				perror("Error, Sheldon says");
			} 
			
	
}

void execute_echo(char **array_of_args)									// For executing echo
{
	int ind;
	for(ind=1;array_of_args[ind]!=NULL;ind++)
	{
		printf("%s", array_of_args[ind]);								// The input is saved in the pointer array, and printed omitting the first element
		if(array_of_args[ind+1]==NULL) {								// which is 'echo'
			printf("\n");
		}
		else
		{
			printf(" ");
		}
	}
}

void execute_help()														// For giving details about the shell
{
	printf("Shelldon Shell: The shell that sheldom fails\n\tWritten by: M M Abid Naziri\n");
	printf("\tDepartment of Computer Science and Engineering (21st Batch)\n\tUniversity of Dhaka\n\nDate: 5th February, 2017\n\n");
	printf("Write a command on the console, press enter and it's done\n\n");
	printf("List of builtin shell functions: \n");
	printf("#1 cd: go to any specific directory\n#2 echo: display a mesassage\n#3 exit: exit the shell\n");
	printf("#4 help: get a list of builtin functions and features\n#5 pwd: display the current directory\n");
	printf("Use man for other commands\n\n");
	printf("Features:\n\t-- Can use pipe\n\t-- Can use I/O redirection\n");
	printf("\t-- Can use background processes\n\t-- 'ls' commands are color-coded for user's convenience\n\n");
	printf("Bugs:\n\t-- Creates zombies while creating background processes\n\n");
	printf("Thank you for using this shell ^_^\n");
}


void execute_pwd()														// For executing pwd
{
	char directory[8192];
	getcwd(directory, 8192);											// Gets the current directory in string directory
	printf("%s\n", directory);
}


void execute_exit()														// For exiting the shell
{
	exit(EXIT_SUCCESS);
}

