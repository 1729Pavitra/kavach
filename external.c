#include"cmd.h"
#include"macros.h"
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"variable.h"


void print_command(Command cmd) {
struct arg* p = cmd;
	while(p!=NULL) {
	printf("%s ",p->string);
	p=p->next;
	}
	printf("\n");
	fflush(stdout);

}


int local_exec(Command cmd,int fd_in,int fd_out)
{


//printf("%s %d %d\n",cmd->string,fd_in,fd_out);
fflush(stdout);
int a = 0;
char* program = malloc(strlen(cmd->string)+1);
strcpy(program,cmd->string);

	pid_t pid;

	char* argv[100]={program,NULL};

	int i = 0;
	struct arg* p = cmd;
		while(p != NULL) {
	
	
				char* argument = malloc(strlen(p->string)+1);
				strcpy(argument,p->string);

				argv[i] = argument;
				p = p->next;
				i++;
	
		}
		argv[i] = NULL;
		if(cmd->string[0]=='/') {
		pid = fork();
			if(pid==0) {
			a = execv(program,argv);
			exit(1);
			}
			wait(&a);
		}
		else if(cmd->string[0]=='~') {
		pid = fork();
			if(pid==0) {
			dup2(fd_in,0);
			dup2(fd_out,1);
			char* home;
			char home_program[MAXLEN_STR];
			home = getenv("HOME");
			strcpy(home_program,home);
			strcat(home_program,program+1);
			a = execv(home_program,argv);
			exit(1);
			}
			wait(&a);
		}
	
		else{
		pid = fork();
			if(pid==0) {

			dup2(fd_in,0);
			dup2(fd_out,1);
			a = execvp(program,argv);
			exit(1);
			}
			wait(&a);
		}
	

	return a;



}


int is_external(Command cmd_in)
{

Command cmd = resolve_cmd(cmd_in);

int fd_in=0;
int fd_out=1;
int npipes=0;
is_redirect(cmd,&fd_in,&fd_out,&npipes);

	if(npipes==0) {
	int a = local_exec(cmd,fd_in,fd_out);
		if(fd_in!=0) {
		close(fd_in);
		}
		if(fd_out!=1) {
	 	close(fd_out);
	 	}
	free_command(cmd);
	return a;
	}
	
	else {

	Command c[npipes+1];
	c[0]=cmd;
	int i=0;
	int j=npipes;

		
	struct arg* p = cmd;
		while(j!=0) {
			if(p->next!=NULL){
				if(!strcmp(p->next->string,"|")) {
				i=i+1;
				c[i]=p->next->next;
				struct arg* q = p;
				p = p->next->next;
				q->next=NULL;								
				j = j-1;
				}
				else{
				p=p->next;	
				}
			}
		}

		/*
		j=npipes;
		while(j!=-1) {	
		print_command(c[j]);
		j=j-1;
		}
		*/
		
		int f[npipes][2];
		int l=0;
		while(l<npipes) {
		pipe(f[l]);
		printf("%d %d\n",f[l][0],f[l][1]);
		l=l+1;
		}		
	}	

}




