#include"cmd.h"
#include<stdio.h>
#include<stdlib.h>

void add_to_tree(Command cmd)
{
extern struct Block* tree;
extern List command_list;
extern nested;
struct Block* b = (struct Block*)malloc(sizeof(struct Block));
b->head = command_list;
b->depth = nested;
b->child = NULL;
b->parent = NULL;

tree = b;

}

void update_end_tree(Command cmd)
{
extern struct Block* tree;
extern List command_list;
tree->end = command_list;
}

void free_tree()
{

}

void execute_tree()
{
extern struct Block* tree;
execute_block(tree);

}
