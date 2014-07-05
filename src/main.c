/* 
 * main.c
 * Author: Anaykumar Joshi
 *
 * This file implements the main() function. 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "command.h"
#include "prompt.h"
#include "variable.h"

/* a global variable which stores the current directory name */
char current_dir[MAXDIRLEN] = ""; 

/* holds the variables defined by user */
struct variable* var_list; 

int main(int argc,char** argv)
{
    var_list = NULL;
    
    if(argc==1) 
    {
        display_prompt(current_dir);
    }
    
    fflush(stdout);
    char cmd_string[MAXCMDLEN+1];

    if(argc > 1) 
    {
        FILE* f = fopen(argv[1],"r");
        if(f==NULL) 
        {
            perror("could not open the script file\n");
            exit(EXIT_FAILURE);
        }
        //ignore first line #!/bin/kavach
        fgets(cmd_string,MAXLEN_STR,f);

        while(fgets(cmd_string,MAXLEN_STR,f)!=NULL) 
        {
            command_t cmd =  parse(cmd_string);
            execute(cmd);
        }
    }
    else 
    {
        while(1) 
        {
            fgets(cmd_string,MAXLEN_STR,stdin);
            command_t cmd =  parse(cmd_string);
            
            if(!strcmp(cmd->string,"end")) 
            {
                execute(cmd);
            }
            execute(cmd);           
            display_prompt(current_dir);    
        }
    }   
    
    return 0;

}



