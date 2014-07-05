#include <stdio.h>
#include "command.h"

void execute(command_t cmd) 
{
	int status  = is_internal(cmd);
	if(status == 1) 
    {
		status = is_external(cmd);
	}

	if(status == 256) 
    {
		printf("what??\n");
	}		
}


