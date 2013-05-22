#include<stdio.h>
#include"cmd.h"
#include<stdlib.h>
#include<string.h>
#include"macros.h"

int is_exit(Command cmd) {

	if(!strcmp(cmd->string,"exit")) {

	exit(EXIT_SUCCESS);	
	printf("exited\n");
	}

return 1;

}


int is_cd(Command cmd) {
extern char current_dir[MAXLEN_STR];
int return_value = 1;

if(!strcmp(cmd->string,"cd")) {
	char backup_dir[MAXLEN_STR];
	strcpy(backup_dir,current_dir);
	
		if(cmd->next==NULL) {
			char* home_dir = getenv("HOME");
			strcpy(current_dir,home_dir);
				if(chdir(current_dir)==-1) {
				printf("no such directory\n");
				strcpy(current_dir,backup_dir);
			}
		}
	
		else if(cmd->next->string[0]=='/') {
			if(chdir(cmd->next->string)==-1) {				
				printf("no such directory\n");				
			}
			else {
				strcpy(current_dir,cmd->next->string);
			}			
		}
		else if(cmd->next->string[0]=='~') {
			char* home_dir = getenv("HOME");
			strcpy(current_dir,home_dir);
			strcat(current_dir,cmd->next->string+1);
				if(chdir(current_dir)==-1) {
				printf("no such directory\n");
				strcpy(current_dir,backup_dir);
			}	
		}
		
		else if(cmd->next->string[1]=='.'&&cmd->next->string[0]=='.') {

			int len = strlen(current_dir);
			int i=len;
			while(i>0) {
				if(current_dir[i]=='/'){
				current_dir[i] = '\0';
				break;
				}
			i=i-1;
			}
				if(chdir(current_dir)==-1) {
				printf("no such directory\n");
				strcpy(current_dir,backup_dir);
			}	
		}
		
		else if(cmd->next->string[0]=='.') {
			strcat(current_dir,cmd->next->string+1);
				if(chdir(current_dir)==-1) {
				printf("no such directory\n");
				strcpy(current_dir,backup_dir);
			}	
		}

		else {
		
		strcat(current_dir,"/");
		strcat(current_dir,cmd->next->string);
			if(chdir(current_dir)==-1) {
				printf("no such directory\n");
				strcpy(current_dir,backup_dir);
			}			
		}
	return_value = 0;
	}
return return_value;
}
