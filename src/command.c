#include "command.h"
#include <stdio.h>
#include <stdlib.h>


void free_command(command_t cmd)
{
    struct arg* p=cmd;
    struct arg* q;
    while(p!=NULL) 
    {
        q = p->next;
        free(p);
        p = q;
    }
}
