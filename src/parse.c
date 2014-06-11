#include "cmd.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "macros.h"

/*
This function is used inside parse function(see below) to create a 'struct arg' for a particular argument 
*/
struct arg* construct_argument(int size,char* string) ;

/*
this command takes as input a string which is to be executed, and then creates a linked list of (struct arg). Note that Command is typedef struct arg*
This funtion then returns a pointer to the head of the linked list. This pointer now symbolizes a command.
*/

Command parse(char* cmd_string) 
{

	char word[MAXARGLEN];
	unsigned long len = strlen(cmd_string);
	int i=0;
	int j=0;
	int flag = 0; // first argument or not
	struct arg *c,*d; //helpers
	
	Command cmd;
	
	while(i<len) 
    {
		
		if(cmd_string[i]==32) 
        {
			word[j]='\0';
			j=0;
			i=i+1;
			if(flag == 0) 
            {
				flag = 1;
				c = construct_argument(strlen(word),word); 
				cmd = c;				
			}
			else 
            {
				d =	construct_argument(strlen(word),word);
				c->next = d;
				c = d;
			}
			// create new structure to hold argument

		}
		if(cmd_string[i]=='\n') 
        {
			word[j]='\0';
			if(flag == 0) 
            {
				c = construct_argument(strlen(word),word); 
				cmd = c;	
			}
			else 
            {
				d =	construct_argument(strlen(word),word);
				c->next = d;
				c = d;
				c->next = NULL;
			}
			// create new structure to hold argument
			break;	
		
		}
		word[j] = cmd_string[i];
		j=j+1;
		i=i+1;
	}
	
    return cmd;
}


struct arg* construct_argument(int size,char* string) 
{
    struct arg* p = malloc(sizeof(struct arg));
    char* string_pointer = malloc(size+1);
    p->string = string_pointer;
    strcpy(p->string,string);
    p->next = NULL;
    return p;
}

/*
command_length returns the number of number of arguments in the Command.
*/


int command_length(Command cmd)
{
	int len = 0;
	struct arg* p = cmd;
	while(p!=NULL) 
    {
        len = len+1;
        p = p->next;
	}
    return len;
}

