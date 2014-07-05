#include "command.h"
#include "macros.h"
#include "variable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern struct variable* var_list;   

/**
 * @brief Seaches for the variable with the given name
 *
 * @param var_name The name of the variable to be searched
 *
 * @return the variable structure if found, else None
 */
struct variable* search_variable(char* var_name)
{
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
*/


/**
 * @brief is_variable_assignment is called when the user command is of the form var = something
 * (provided var is not an internal or external command)
 * This function searches the var_list and if it finds exiting variable with the same name, 
 * then the corresponding structure of the variable is updated; 
 * else, a new variable structure is created and is added to varlist
 *
 * @param cmd The command being processed
 *
 * @return YES, if cmd is indeed of the form 'x = something'; else NO
 */
int is_variable_assignment(command_t cmd)
{
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
                    return YES;
                }
                else 
                {
                    v->string = malloc(sizeof(strlen(cmd->next->next->string) + 1));
                    strcpy(v->string,cmd->next->next->string + 1);
                    v->string[strlen(cmd->next->next->string) - 2] = '\0';
                    return YES;
                }       
            }           
            else
            {
                return NO;
            }
        }
        else 
        {
            return NO;
        }   
    }   
    else 
    {
        return NO;
    }
}

/*
*/


/**
 * @brief this function is used to implement "export var" command
 *
 * @param cmd The command being processed
 *
 * @return YES, if cmd is of form 'export var'; else NO
 */
int is_export(command_t cmd)
{
    if(!strcmp(cmd->string, "export")) 
    {

        if(command_length(cmd) != 2) 
        {
            printf("improper usage of export command\n");
            return YES;
        }
        else 
        {
            struct variable* v = search_variable(cmd->next->string);
            if(v == NULL) 
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
        return YES;
    }
    else 
    {
        return NO;
    }
}


/**
 * @brief This function checks for occurences of the symbol $ in the copied command. 
 * If $ is found, then the string following $ is searched as a variable name. 
 * If a variable with the same name is found, then the $var is replaced with the value of var. 
 * Note that only external commands use this function.
 *
 * @param cmd_in The command being processed
 *
 * @return A new command with possibly substituted $var
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

        l = l->next;
    }
    return cmd_in;
}
