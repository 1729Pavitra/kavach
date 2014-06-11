#include "cmd.h"
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
    int flag = 0;
    while(p!=NULL) 
    {
        if(!strcmp(p->name,var_name)) 
        {
            return p;
            flag = 1;
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


int is_variable_assignment(Command cmd)
{

    extern struct variable* var_list;   
    int len = command_length(cmd);

    if(len > 2) 
    {
        if(!strcmp(cmd->next->string,"=")) 
        {

            struct variable* v = search_variable(cmd->string);
            if(cmd->next->next->string[0]!='"') 
            {
                if(v==NULL) 
                {
                    struct variable* v = malloc(sizeof(struct variable));
                    v->string = "";
                    v->next = var_list;
                    v->name = malloc(sizeof(strlen(cmd->string)+1));
                    strcpy(v->name,cmd->string);
                    var_list = v;
                    return 0;
                }
                else 
                {
                    v->string = "";
                    return 0;
                }
            }
            else 
            {
                if(v==NULL) 
                {
                    struct variable* v = malloc(sizeof(struct variable));
                    v->string = malloc(strlen(cmd->next->next->string)+1);
                    strcpy(v->string,cmd->next->next->string + 1);
                    v->string[strlen(cmd->next->next->string)-2] = '\0';
                    v->next = var_list;
                    v->name = malloc(sizeof(strlen(cmd->string)+1));
                    strcpy(v->name,cmd->string);
                    var_list = v;
                    return 0;
                }
                else 
                {
                    v->string = malloc(sizeof(strlen(cmd->next->next->string)+1));
                    strcpy(v->string,cmd->next->next->string + 1);
                    v->string[strlen(cmd->next->next->string)-2] = '\0';

                    return 0;
                }       
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
this function is used to implement "print var" command
*/


int is_print(Command cmd)
{
    if(!strcmp(cmd->string,"print")) 
    {
        extern struct variable* var_list;
        int flag = 0;

        if(cmd->next==NULL) 
        {
            struct variable* p = var_list;
            
            while(p!=NULL) 
            {
                printf("%s ::%s \n",p->name,p->string);
                flag = 1;
                p = p->next;        
            }
            return 0;
        }
        else 
        {
            struct variable* p = var_list;
            while(p!=NULL) 
            {
                if(!strcmp(p->name,cmd->next->string)) 
                {
                    printf("%s\n",p->string);
                    flag = 1;
                }
                p = p->next;        
            }
            if (flag==0) 
            {
                char* env = getenv(cmd->next->string);
                
                if(env==NULL) 
                {
                    printf("no such variable..... : %s\n",cmd->next->string);
                }
                else 
                {
                    printf("%s\n",env);
                }
            }
            return 0;
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


int is_export(Command cmd)
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
used inside resolve_command. It simpy prepares a copy of the input command and returns the copy.
*/

Command copy_command(Command cmd_in)
{
    Command cmd_out=NULL;
    int flag = 0;
    struct arg* c = cmd_in;
    struct arg* dprev;
    while (c!=NULL) 
    {
        struct arg* d = malloc(sizeof (struct arg));
        char* s = malloc(strlen(c->string)+1);
        strcpy(s,c->string);
        d->string = s;
        if(flag==0) 
        {
            cmd_out = d;
            flag = 1;
        }
        else 
        {
            dprev->next = d;
        }
        d->next = NULL;
        dprev = d;
        c = c->next;
    }
    return cmd_out;

}

/*
This function first copies the entire command into a new command (by making a call to copy_command, so that the original command is pushed "as is" in the command_list, (in case this command is inside a nest)
this function then checks for occurences of the symbol $ in the copied command. If $ is found, then the string followinf $ is searched as a variable name. If a variable with the same name is found, then the $var is replaced with the value of var (number or string). Note that only external commands use this function.
*/

Command resolve_cmd(Command cmd_in)
{
    Command cmd_out = copy_command(cmd_in);
    extern struct variable* var_list;
    struct arg* l = cmd_out;
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
    return cmd_out;
}


/*
used to implement "itos var"
*/

int is_itos(Command cmd)
{
    int length = command_length(cmd);
    int flag=0;

    if(!strcmp(cmd->string,"itos")) 
    {
        if(length!=2) 
        {
            printf("improper usage\n");
            return 0;
        }
        extern struct variable* var_list;
        struct variable*v = var_list;
        while(v!=NULL) 
        {
            if(!strcmp(cmd->next->string,v->name))
            {
                //free(v->string);
                flag=1;
            }
            v=v->next;              
        }
        if(flag==0) 
        {
            printf("no such variable\n");
        }           
    }
    else
    {
        return 1;
    }
}

/*
used to implement "stoi var"
*/
int is_stoi(Command cmd)
{
    int length = command_length(cmd);
    int flag=0;

    if(!strcmp(cmd->string,"stoi")) 
    {
        if(length!=2) 
        {
            printf("improper usage\n");
            return 0;
        }
        extern struct variable* var_list;
        struct variable*v = var_list;
        while(v!=NULL) 
        {
            if(!strcmp(cmd->next->string,v->name)) 
            {
                strcpy(v->string,""); 
                flag=1;
            }
            v=v->next;              
        }
        if(flag==0) 
        {
            printf("no such variable\n");
        }           
    }
    else
    {
        return 1;
    }

}

