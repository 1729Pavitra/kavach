#include "command.h"
#include "variable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
this function is not exposed to the user. It searches the var_list for a variable name and returns the pointer to the structure of the variable( if found), else, returns a NULL pointer
 */

struct variable* search_variable(char* var_name)
{
    extern struct variable* var_list;
    struct variable* p = var_list;
    while(p != NULL) 
    {
        if(!strcmp(p->name, var_name)) 
        {
            return p;
        }
        p = p->next;        
    }
    return NULL;
}

/*
is_variable_assignment is called when the user command is of the form
var = something
(provided var is not an internal or external command)
This function searches the var_list and if it finds exiting variable with the same name, then the corresponding structure of the variable is updated; else, a new variable structure is created and is added to varlist
*/


int is_variable_assignment(command_t cmd)
{

    extern struct variable* var_list;   
    int len = command_length(cmd);

    if(len > 2) 
    {
        if(!strcmp(cmd->next->string,"=")) 
        {
            struct variable* v = search_variable(cmd->string);
            if(cmd->next->next->string[0] == '"') 
            {
                if(v == NULL) 
                {
                    struct variable* v = malloc(sizeof(struct variable));
                    v->string = malloc(strlen(cmd->next->next->string) + 1);
                    strcpy(v->string, cmd->next->next->string + 1);
                    v->string[strlen(cmd->next->next->string) - 2] = '\0';
                    v->next = var_list;
                    v->name = malloc(sizeof(strlen(cmd->string) + 1));
                    strcpy(v->name, cmd->string);
                    var_list = v;
                    return 0;
                }
                else 
                {
                    v->string = malloc(sizeof(strlen(cmd->next->next->string) + 1));
                    strcpy(v->string,cmd->next->next->string + 1);
                    v->string[strlen(cmd->next->next->string) - 2] = '\0';
                    return 0;
                }       
            }           
            else
            {
                return 1;
            }
        }
        else 
        {
            return 1;
        }   
    }   
    else 
    {
        return 1;
    }
}

/*
this function is used to implement "export var" command
*/


int is_export(command_t cmd)
{
    if(!strcmp(cmd->string,"export")) 
    {

        if(command_length(cmd) != 2) 
        {
            printf("improper usage of export command\n");
            return 0;
        }
        else 
        {
            struct variable* v = search_variable(cmd->next->string);
            if(v==NULL) 
            {
                printf("no such variable\n");
            }
            else 
            {
                if(!strcmp(v->string,"")) 
                {
                    printf("sorry, kavach can only export strings and not integers :( \n");
                }
                else 
                {
                    setenv(v->name,v->string,1);
                }
            }       
        }
        return 0;
    }
    else 
    {
        return 1;
    }
}


/*
this function then checks for occurences of the symbol $ in the copied command. If $ is found, then the string followinf $ is searched as a variable name. If a variable with the same name is found, then the $var is replaced with the value of var (number or string). Note that only external commands use this function.
*/

command_t resolve_cmd(command_t cmd_in)
{
    extern struct variable* var_list;
    struct arg* l = cmd_in;
    while(l!=NULL) 
    {
        if(l->string[0]=='$') 
        {
            struct variable* v = search_variable(l->string+1);
            if(v==NULL) 
            {
                char* env = getenv(cmd_in->next->string+1);
                if(env!=NULL) 
                {
                    l->string= realloc(l->string,strlen(env)+1);
                    strcpy(l->string,env);
                }
                else 
                {
                    printf("variable called in the command does not exit\n");
                }
            }
            else 
            {
                l->string = realloc(l->string,strlen(v->string)+1);
                strcpy(l->string,v->string);
            }
        }

        l=l->next;
    }
    return cmd_in;
}




