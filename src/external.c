#include "command.h"
#include "macros.h"
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "variable.h"



/**
 * @brief 
 *
 * @param cmd The command being processed
 * @param fd_in The input file descriptor
 * @param fd_out The output file descriptor
 *
 * @return 
 */
int local_exec(command_t cmd, int fd_in, int fd_out)
{
    fflush(stdout);
    char* program = malloc(strlen(cmd->string) + 1);
    strcpy(program, cmd->string);
    char* argv[100]= {program, NULL};
    struct arg* p = cmd;

    int i = 0;
    while(p != NULL) 
    {
        char* argument = malloc(strlen(p->string)+1);
        strcpy(argument,p->string);
        argv[i] = argument;
        p = p->next;
        i++;
    }

    argv[i] = NULL;
    int error_value = 0;
    pid_t pid;
    if(cmd->string[0]=='/') 
    {
        pid = fork();
        if(pid == 0) 
        {
            error_value = execv(program, argv);
            exit(1);
        }
        wait(&error_value);
    }
    else if(cmd->string[0] == '~') {
        pid = fork();
        if(pid == 0) 
        {
            dup2(fd_in, 0);
            dup2(fd_out, 1);
            char* home;
            char home_program[MAXLEN_STR];
            home = getenv("HOME");
            strcpy(home_program, home);
            strcat(home_program, program + 1);
            error_value = execv(home_program, argv);
            exit(1);
        }
        wait(&error_value);
    }
    else
    {
        pid = fork();
        if(pid == 0) 
        {
            dup2(fd_in, 0);
            dup2(fd_out, 1);
            error_value = execvp(program, argv);
            exit(1);
        }
        wait(&error_value);
    }
    return error_value;
}


/**
 * @brief Attempts to execute a non-internal command
 *
 * @param cmd_in The command being processed
 *
 * @return ERROR in case of error, else returns YES
 */
int is_external(command_t cmd_in)
{
    int fd_in = 0;
    int fd_out = 1;
    int npipes = 0;
    command_t cmd = resolve_cmd(cmd_in);
    is_redirect(cmd, &fd_in, &fd_out, &npipes);

    if(npipes == 0) 
    {
        int error_value = local_exec(cmd, fd_in, fd_out);
        if(fd_in != 0) 
        {
            close(fd_in);
        }
        if(fd_out != 1) 
        {
            close(fd_out);
        }
        free_command(cmd);
        return error_value;
    }
    else 
    {
        command_t c[npipes + 1];
        c[0] = cmd;
        int i = 0;
        int j = npipes;
        struct arg* p = cmd;
        while(j != 0) 
        {
            if(p->next != NULL)
            {
                if(!strcmp(p->next->string, "|")) 
                {
                    i = i + 1;
                    c[i] = p->next->next;
                    struct arg* q = p;
                    p = p->next->next;
                    q->next = NULL;                               
                    j = j - 1;
                }
                else
                {
                    p = p->next;  
                }
            }
        }
        int f[npipes][2];
        int l = 0;
        while(l < npipes) 
        {
            pipe(f[l]);
            printf("%d %d\n", f[l][0], f[l][1]);
            l = l + 1;
        }
    }   
}
