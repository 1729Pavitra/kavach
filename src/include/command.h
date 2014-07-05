#ifndef CMD_H
#define CMD_H

struct arg
{
	struct arg* next;
	char* string;
};

typedef struct arg* command_t;

int command_length(command_t cmd);
	
command_t parse(char* cmd);

int is_internal(command_t cmd);

int is_external(command_t cmd);

void execute(command_t cmd);

int is_variable_assignment(command_t cmd);

int is_cd(command_t cmd);

int is_exit(command_t cmd);

void free_command(command_t cmd);

void is_redirect(command_t cmd,int* fd_in,int* fd_out,int* npipes );

command_t resolve_cmd(command_t cmd_in);

struct cmd_list_element
{
    command_t cmd;
    struct cmd_list_element* next;
    struct cmd_list_element* prev;
};

typedef struct cmd_list_element* List;

void cmd_push(struct cmd_list_element* c);

void pop_free_cmd();

void print_command(command_t cmd);


#endif
