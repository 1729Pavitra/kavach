#include"cmd.h"
#include<stdio.h>
#include<stdlib.h>

extern List command_list;

void push_cmd(Command cmd)
{
struct cmd_list_element* e = (struct cmd_list_element*) malloc(sizeof (struct cmd_list_element));
e->cmd = cmd;
e->next = command_list;
e->prev = NULL;
	if(command_list!=NULL) {
	command_list->prev = e;
	}
command_list = e;
}

void pop_free_cmd()
{
struct cmd_list_element* c = command_list;
command_list=command_list->next;
struct arg* p = c->cmd;	
	while(p!=NULL) {
	struct arg* q = p;
	p=p->next;
	free(q);	
	}
}
