#include <stdio.h>
#include "cmd.h"

void execute(Command cmd) 
{
	extern int latest_status;
	latest_status  = is_internal(cmd);
	if(latest_status==1) 
    {
		latest_status = is_external(cmd);
	}

	if(latest_status==256) 
    {
		printf("what??\n");
	}		
}


