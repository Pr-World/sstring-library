#include <stdio.h>
#include <stdlib.h>
#include "sstring.h"


/*
Example usage of sstring.h functions
initially we dont need to include stdlib.h or string.h
But are included for c-style arr conversion showcase and error functions defined here
*/

//User can handle errors in their **Own** Way

void ErrCheck(sstrfuncerr _str){
	if(_str._err!=SSTRING_NO_ERR){
		printf("\n--- Error %d ---",_str._err);
		showerr(_str._err);
		//terminate the program upon error
		//again user can do anything like return value and etc.
		exit(_str._err);
	}	
}

void ErrCodeCheck(int _code){
	if(_code<SSTRING_NO_ERR){
		printf("\n--- Error %d ---",_code);
		showerr(_code);
		//terminate the program upon error
		//again user can do anything like return value and etc.
		exit(_code);
	}
}

void GenerateErr(int _code){
	if(_code!=SSTRING_NO_ERR){
		printf("\n--- Error %d ---",_code);
		showerr(_code);
		exit(_code);
	}
}

int main(){
	//variable a for storing strings, errcheck for checking errors
	sstring a;
	sstrfunc errcheck;
	
	//input a!
	printf("\n------- Example Of SSTRING --------\n\nEnter a string: ");
	errcheck = sstrinput();
	ErrCheck(errcheck);
	a = errcheck._str;
	printf("You entered: %s\n\n",a);
	
	//replacing in strings so easy!!
	errcheck = sstrreplace(a," ","_");
	ErrCheck(errcheck);
	a = errcheck._str;
	printf("Replacing space with underscores: %s\n\n",a);
	
	//inputting passwords so easy
	printf("Enter password: ");
	errcheck = sstrinputpass("*");
	ErrCheck(errcheck);
	a = errcheck._str;
	printf("Shhh!! Your password is: %s\n",a);
	
	
}
