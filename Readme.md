the-sh
======

the-sh is a minimal shell written out of curiousity, in order to understand how shells work. The goal is not to write a complete shell; but to write an educational shell with which you can spend a day or two. The only features which I intend to add are

Hopefully, the-sh would serve as a tutorial for students who want to understand how a shell works

Features: 
---------

Internal commands:
		
> 1. exit : does what it is supposed to do!
> 2. cd : do i need to tell what this does??
> 3. export : add a variable in the exvironment variable list
> 4. print : prints value of a variable on stdout
		

Minimal Support for variables is available (for exporting them)

> X = "some_value"
> export X

Minimal Support for IO redirection is available

>  echo "hello" > a.txt

Ofcourse, all the external commands work (ls, vim ..), and you can invoke programs using the shell.
