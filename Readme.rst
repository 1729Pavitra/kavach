######
the-sh
######

the-sh is a minimal shell written out of curiousity, in order to understand how shells work. The goal is not to write a complete shell; but to write an educational shell with which you can spend a day or two. The only features which I intend to add are

Hopefully, the-sh would serve as a tutorial for students who want to understand how a shell works

---------
Features: 
---------

* internal commands :
		
-		exit : does what it is supposed to do!
-		cd : do i need to tell what this does??
-		export : add a variable in the exvironment variable list
-		print : prints value of a variable on stdout
		

Minimal Support for variables is available (for exporting them)

-       X = "some_value"
-       export X

Minimal Support for IO redirection is available

-       echo "hello" > a.txt
