#ifndef VARIABLE_H
#define VARIABLE_H

struct variable
{
char* name;
char* string;
struct variable* next;
};

void print(char* variable_name);

struct variable* search_variable(char* var_name);

#endif
