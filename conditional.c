
#include"cmd.h"
#include<stdlib.h>
#include<stdio.h>

int is_if(Command cmd)
{
	int len = command_length(cmd);

	if(len > 2){
		if(!strcmp(cmd->string,"if")) {
			extern nested;
			nested = nested+1;
			extern cmd_push_status;
			extern struct Block* tree;
			extern List command_list;

			push_cmd(cmd);

			add_to_tree(cmd);

			cmd_push_status=1;
			return 0;		
		}
		else {
			return 1;
		}
	}
	else {
		return 1;
	}
}



int is_while(Command cmd)
{
	int len = command_length(cmd);	
	if(len > 2) {

		if(!strcmp(cmd->string,"while")) {
			extern nested;
			nested = nested+1;
			extern cmd_push_status;
			extern struct Block* tree;
			extern List command_list;
			push_cmd(cmd);

			add_to_tree(cmd);

			cmd_push_status=1;
			return 0;		

		}
		else {
			return 1;
		}
	}
	else {
		return 1;
	}
}


void free_block()
{
	extern struct Block* tree;
	extern List command_list;
	struct cmd_list_element* e = command_list;

	while(e!=tree->head) {
		pop_free_cmd();
		e=command_list;
	}
	pop_free_cmd();
}


int is_end(Command cmd)
{
	if(!strcmp(cmd->string,"end")) {
		extern nested;
		push_cmd(cmd);
		extern struct Block* tree;
		update_end_tree(cmd);

		nested = nested - 1;

		if(nested==0) {

			execute_block(tree);				
			free_block();
			extern cmd_push_status;
			cmd_push_status = 2;
			//free_tree();
			tree = NULL;
		}
	}
	else {
		return 1;
	}
}


void free_command(Command cmd)
{
	struct arg* p=cmd;
	struct arg* q;
	while(p!=NULL) {
		q = p->next;
		free(p);
		p = q;
	}
}
