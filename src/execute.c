#include <stdio.h>
#include "command.h"
#include "macros.h"

/**
 * @brief First checks whether the input command is an internal command;
 * If not, then the command is assumed to be an external command.
 * If the command is not executed successfully as an external command, 
 * an error message is printed
 *
 * @param cmd The command being processed
 */
void execute(command_t cmd) 
{
	int status  = is_internal(cmd);
	if(status == NO) 
    {
		status = is_external(cmd);
	}

	if(status == 256) 
    {
		printf("what??\n");
	}		
}


