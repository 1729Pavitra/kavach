
struct variable
{
char* name;
char* string;
int value;
struct variable* next;
};

void print(char* variable_name);

struct variable* search_variable(char* var_name);

char* itos(int num);

