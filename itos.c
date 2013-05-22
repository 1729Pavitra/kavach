#include<string.h>
#include<stdio.h>
#include<stdlib.h>

/*
itos converts an integer into a string.
for example, itos(238) would return a pointer to a string "238"
For conversion from strings to integers, the-sh uses atoi, a function from string.h

itos is used in the implementation of the builtin function "itos"
itos is also used in the function "resolve_command" which is used to replaces variables by their values. Since all the arguments should be strings, itos is used is used while resolving every external command. (resolve_command and is_itos are implemented in variable.c)
*/


char* itos(int num)
{
char* s = malloc(20);
int i=0;
int tenpower=1;

	if(num > 0) {

		while(num>=tenpower) {
		tenpower=10*tenpower;
		i=i+1;
		}
	int a=0;
	int b=0;
	int c=0;
	int j=0;
	tenpower = tenpower/10;
		while(j<i) {
		a = (num/tenpower);
		c = (num/tenpower) - b;
		tenpower=tenpower/10;
		b=a*10;
		s[j]=(char)(((int)'0')+c);
		j++;
		}
		s[j]='\0';
		return s;
	}
	else if(num < 0){
	num = -num;
	while(num>=tenpower) {
		tenpower=10*tenpower;
		i=i+1;
		}
	int a=0;
	int b=0;
	int c=0;
	int j=1;
	s[0] = '-';
	tenpower = tenpower/10;
		while(j<(i+1)) {
		a = (num/tenpower);
		c = (num/tenpower) - b;
		tenpower=tenpower/10;
		b=a*10;
		s[j]=(char)(((int)'0')+c);
		j++;
		}
		s[j]='\0';
		return s;		
	}
	else {
	s[0] = '0';
	s[1] = '\0';
	return s;
	}
}

