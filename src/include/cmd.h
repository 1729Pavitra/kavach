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

int evaluate_expression(struct arg* exp);

int is_variable_assignment(Command cmd);

int is_cd(Command cmd);

int is_exit(Command cmd);

int is_stoi(Command cmd);

int is_itos(Command cmd);

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

struct Block
{
struct cmd_list_element* head;
struct cmd_list_element* end;
struct Block_container* child;
struct Block* parent;
int depth;
};

struct Block_container
{
struct Block* block;
struct Block_container* next;
};

void execute_block(struct Block* blk);

void execute_set(struct Block* blk, struct cmd_list_element* cle);

void add_to_tree(Command cmd);
