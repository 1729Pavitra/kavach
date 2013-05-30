#include"prompt.h"
#include<stdio.h>
#include"macros.h"
#include<stdlib.h>
#include<string.h>
extern char current_dir[MAXLEN_STR];

void display_prompt(char* current_dir) {
	
	if(strcmp(current_dir,"")==0) {
		char* current_dir = malloc(100);
		getcwd(current_dir,100);
		printf("%s :the-sh $ ",current_dir);
	}
	else {
		printf("%s :the-sh $ ",current_dir);
	}	

}
