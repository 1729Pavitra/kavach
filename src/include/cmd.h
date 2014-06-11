#ifndef CMD_H
#define CMD_H

struct arg
{
	struct arg* next;
	char* string;
};

typedef struct arg* Command;

int command_length(Command cmd);
	
Command parse(char* cmd);

int is_internal(Command cmd);

int is_external(Command cmd);

void execute(Command cmd);

int is_variable_assignment(Command cmd);

int is_cd(Command cmd);

int is_exit(Command cmd);

void free_command(Command cmd);

void is_redirect(Command cmd,int* fd_in,int* fd_out,int* npipes );

Command resolve_cmd(Command cmd_in);

struct cmd_list_element
{
    Command cmd;
    struct cmd_list_element* next;
    struct cmd_list_element* prev;
};

typedef struct cmd_list_element* List;

void cmd_push(struct cmd_list_element* c);

void pop_free_cmd();

void print_command(Command cmd);


#endif
