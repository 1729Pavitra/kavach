#include<stdlib.h>
#include<stdio.h>
#include"stack.h"
#include"cmd.h"
#include"variable.h"



void push(Stack *addr_s,struct element* e)
{
	e->next = *addr_s;
	*addr_s = e;
	//printf("pushed :%d\n",(*addr_s)->value);
}

struct element* pop(Stack *addr_s)
{
	struct element* e;
	e = (*addr_s);
	*addr_s = (*addr_s)->next;
	return e;
}


int calculate(struct element* e,int j)
{
	int answer;
	if (j == 3) {

		if((e->next->op)==1) {
			answer = e->value + e->next->next->value;
		}
		else if((e->next->op)==2) {
			answer = e->value * e->next->next->value;
		}
		else if((e->next->op)==3) {
			answer =  e->next->next->value - e->value ;
		}
		else if((e->next->op)==4) {
			if(e->next->next->value > e->value) {
				answer = 1;
			}
			else {
				answer = 0;
			}	
		}
		else if((e->next->op)==5) {
			if(e->next->next->value < e->value) {
				answer = 1;
			}
			else {
				answer = 0;
			}
		}
	}
	else {
		answer = e->value;
	}


	return answer;

}


int evaluate_expression(struct arg* exp)
{
	if( exp->string[0]!='"')
	{
		int answer;
		Stack s=NULL;
		struct arg* p = exp;
		struct variable* v;
		//printf("dfd\n");


		while(p!=NULL) {

			struct element* e = malloc(sizeof (struct element));
			if(!strcmp(p->string,"(")) {
				//printf("df\n");
				e->value = 0;
				e->op = 0;
				e->bracket = 1;
				push(&s,e);
			}
			else if(!strcmp(p->string,"+")) {
				e->value = 0;
				e->bracket = 0;
				e->op = 1; 
				push(&s,e);		
			}
			else if(!strcmp(p->string,"*")) {
				e->value = 0;
				e->bracket = 0;
				e->op = 2; 
				push(&s,e);		
			}
			else if(!strcmp(p->string,"-")) {
				e->value = 0;
				e->bracket = 0;
				e->op = 3; 
				push(&s,e);		
			}
			else if(!strcmp(p->string,">")) {
				e->value = 0;
				e->bracket = 0;
				e->op = 4; 
				push(&s,e);		
			}
			else if(!strcmp(p->string,"<")) {
				e->value = 0;
				e->bracket = 0;
				e->op = 5; 
				push(&s,e);		
			}		
			else if((v=search_variable(p->string))!=NULL) {
				e->value = v->value;
				e->bracket = 0;
				e->op = 0;
				push(&s,e);
			}
			else if(strcmp(p->string,")")) {
				e->value = atoi(p->string);
				e->bracket = 0;
				e->op = 0;
				push(&s,e);
			}

			else {
				struct element* e;
				int j = 0;
				while(s->bracket!=1) {

					if( j==0) {
						//	printf("popped :%d\n",s->value);
						e = pop(&s);

					}
					if( j!= 0) {
						//printf("popped :%d\n",s->value);
						pop(&s);
					}
					j = j+1;

				}
				pop(&s);
				//printf("%d %d %d %d\n",e->value,e->next->op,e->next->next->value,j);
				answer = calculate(e,j);
				//printf("%d\n",local_answer);
				int k; //helper
				struct element* p = e->next;
				for(k = 2; k<j; k++) {
					struct element* q = p;
					free(p);
					p = q->next;				
				}
				e->value = answer;
				e->bracket = 0;
				e->op = 0;
				push(&s,e);
			}


			p = p->next;
		}
		//printf("%d\n",answer);

		return answer;
	}

}


