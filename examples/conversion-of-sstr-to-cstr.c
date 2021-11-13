#include <stdio.h>
#include <stdlib.h>
#include "sstring.h"


/*
Example usage of sstring.h function -> sstr.convS2C
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
	//advanced sstring
	sstring a;
	a = sstr.newstr("Hello World!");
	
	//array-style cstring
	char cstring[100];
	
	//error check var
	int err;
	
	//convert sstring to cstring
	err = sstr.convS2C(a,cstring,sstr.len(a));
	if(err!=_SSTRING_NO_ERR){sstr.showerrs(err);exit(err);}
	
	//display
	printf("%s",cstring);
	
	return 0;
}
