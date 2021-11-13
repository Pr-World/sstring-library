#include <stdio.h>
#include <stdlib.h>
#include "sstring.h"


/*
Example usage of obtaining substring of a string!

Function used: sstr.substr()

parameters:- sstr.substr(sstring var,size_t pos,size_t len)

var -> the sstring from which we want substring
pos -> from which position to start
len -> how much length of substring to take

initially we dont need to include stdlib.h
But are included for functions defined here!
*/

//User can handle errors in their **Own** Way

void checkforerrs(sstring str){
	if(str._err!=_SSTRING_NO_ERR){
		sstr.showerrs(str._err);
		exit(str._err);
	}
}


int main(){
	//create a sstring
	sstring a;
	a = sstr.newstr("Hello World! I am a Program!");
	checkforerrs(a);
	
	//substring!
	a = sstr.substr(a,0,12);
	
	//display
	printf("%s",sstr.val(a));
	
	return 0;
}
