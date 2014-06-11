#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "cmd.h"
#include "prompt.h"
#include "variable.h"


char current_dir[MAXDIRLEN] = ""; // a global variable which stores the current directory name
int latest_status; // local exit status of the latest operation performed
struct variable* var_list; //holds the variables defined by user (strings and integers)
int cmd_push_status; //if cmd_string_status is 0, dont execute next command...(used in implementing conditional jumps and loops
List command_list; // used when we encounter commands like if..else, while
struct Block* tree; // the entire nested parent block is a tree
struct cmd_list_element* cmd_present;
int nested;


int main(int argc,char** argv)
{
    nested = 0;
    tree = NULL;
    cmd_push_status = 0;
    command_list = NULL;
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
            Command cmd =  parse(cmd_string);
            execute(cmd);
        }
    }
    else 
    {
        while(1) 
        {
            fgets(cmd_string,MAXLEN_STR,stdin);
            Command cmd =  parse(cmd_string);
            
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



