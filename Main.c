#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell_header.h"												// Custom header file

int main(int argc, char **argv)
{
	char *str, **array_of_args, directory[8192];
	int stat=0;
	do {
		getcwd(directory, 8192);										// Gets the current directory
		
		printf("[At: %s] Shell we? : ", directory);						// The command line starts after displaying this
		
		str = reaad();	
		
		if(str==0)
		{
			stat=1;
			continue;
		}												// The input is read
		
		array_of_args = paarse(str);									// The commands are parsed
		 
		stat = launch(array_of_args);									// The parsed commands are executed
		
		free(str);														// The input string is freed
		
		free(array_of_args);											// The pointed array for the arguments is freed
		
	} while(stat);
	return EXIT_SUCCESS;
	}
