#include<stdio.h>
#include"cmd.h"

void execute(Command cmd) 
{
extern int latest_status;
latest_status  = is_internal(cmd);
	if(latest_status==1) {
	latest_status = is_external(cmd);
	}
		
	if(latest_status==256) {
	printf("what??\n");
	}		
}

void execute_while_block(struct Block* blk)
{
	struct cmd_list_element* e = blk->head->prev;
	while(evaluate_expression(blk->head->cmd->next)!=0) {
		while(e->cmd!=blk->end->cmd) {
		execute(e->cmd);
		e=e->prev;
		}
	e = blk->head->prev;
	}
}


void execute_if_block(struct Block* blk)
{
	struct cmd_list_element* e = blk->head->prev;
	if(evaluate_expression(blk->head->cmd->next)!=0) {
		while(e->cmd!=blk->end->cmd && strcmp(e->cmd->string,"else")) {
		execute(e->cmd);
		e=e->prev;
		}
	}
	else {
		while(e->cmd!=blk->end->cmd && strcmp(e->cmd->string,"else")) {
		e = e->prev;
		}
		
		if(!strcmp(e->cmd->string,"else")) {
		e = e->prev;
			while(e->cmd!=blk->end->cmd) {
			execute(e->cmd);
			e=e->prev;
			}
		}
	}
	
	
}



void execute_block(struct Block* blk)
{

if(!strcmp(blk->head->cmd->string,"while")){
execute_while_block(blk);
}
else if(!strcmp(blk->head->cmd->string,"if")){
execute_if_block(blk);
}

}


