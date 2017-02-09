#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char *reaad() 										// Function for reading from the input
{
	int size =100, ind=0; 							// A primary size (100) of the input string
	
	char *str = malloc(sizeof(char) * size); 		// Allocating memory for the input string
	
	int character=0; 								// character is an integer type variable because EOF is an integer which can specify the end of user input
	
	if(!str) { 										// In case there was a problem in memory allocation
		fprintf(stderr, "Sheldon: allocation error\n");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		character = getchar();
		
		if(character == EOF || character == '\n') 	// The end of user input
		{
			str[ind++]= '\0';
			return str;
		}
		
		// This part of the code handles the cases where user doesn't use space before using pipes or I/O redirection
		
		else if(ind >= 1 && str[ind-1] == '>' && character != '>') 	// A space is given after either a single '>', or the last '>' of an append call '>>'
		{
			str[ind++]= ' ';
			str[ind++]=character;
		}
		else if(character == '|' || character == '<')				// A space is given before and after '|' or '>'
		{
			str[ind++]=' ';											// Extra spaces won't hurt, so no check to see if there's already a space
			str[ind++]=character;
			str[ind++]=' ';
		}
		else if(character == '>')									// The space after '>' is already managed, now it's time for the space before
		{
			if(ind>=1 && str[ind-1]=='>') str[ind++]=character;		// If this is the second '>' of a '>>', then there's no space in between
				
			else if(ind>=1 && str[ind-1]!='>') {					// If this is a single '>' or the first '>' of a '>>', a space is put before
				str[ind++] = ' ';
				str[ind++] = character;
			}
			
		}
		
		// The trouble with spaces is handled
		// This can also be done by using strtok to seperate after '|', '<', '>' or '>>' 
		
		else
		{
			str[ind++]=character;									// Any other character is sent into the string
		}
		if(ind>=size-5) 											// Re-allocating before reaching the maximum size, just to be safe
		{
			size+=100;

			str = realloc(str, size*sizeof(char));
			if(!str) {
				fprintf(stderr, "Sheldon: allocation error\n");		// Re-allocation error
				exit(EXIT_FAILURE);
			}
		} 
	}
	
}
