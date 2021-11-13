#include <stdio.h>
#include <stdlib.h>
#include "sstring.h"


/*
Example usage of sstring.h function -> sstr.convC2s
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
	printf("%s",a.val);
	
	return 0;
}
