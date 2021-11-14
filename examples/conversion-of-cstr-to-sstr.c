#include <stdio.h>
#include <stdlib.h>
#include "sstring.h"


/*
Example usage of converting c-style array string to modern type sstring!

Function used: sstr.convC2S

parameters:- sstr.convC2S(char * _Buff)

_Buff -> the c-style array string that we want to convert!

Return type:- sstring

initially we dont need to include stdlib.h
But are included for error functions defined here!
*/

//User can handle errors in their **Own** Way

void checkforerrs(sstring str){
	if(str._err!=_SSTRING_NO_ERR){
		sstr.showerrs(str._err);
		exit(str._err);
	}
}


int main(){
	//array-style cstring!
	char cstring[100] = "Hello World!";
	
	//advanced sstring!
	sstring a;
	
	//convert cstring to sstring
	a = sstr.convC2S(cstring);
	checkforerrs(a);
	
	//display
	printf("%s",sstr.val(a));
	
	return 0;
}
