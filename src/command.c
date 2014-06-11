#include "cmd.h"
#include <stdio.h>
#include <stdlib.h>


void free_command(Command cmd)
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
