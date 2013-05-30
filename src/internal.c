#include"cmd.h"
#include"macros.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"variable.h"



int is_internal(Command cmd) {
int return_value=1;

	if(!strcmp(cmd->string,"")) {
	return 0;
	}
	
	return_value = is_exit(cmd);
	if(return_value == 1) {
	return_value = is_cd(cmd);
	}
	if(return_value == 1) {
	return_value = is_variable_assignment(cmd);
	}
	if(return_value == 1) {
	return_value = is_print(cmd);
	}
	if(return_value == 1) {
	return_value = is_export(cmd);
	}
//	if(return_value == 1) {
//	return_value = is_show(cmd);
//	}	

return return_value;
}




