#include <stdio.h>
#include <stdlib.h>
#include "sstring.h"


/*
Example usage of converting sstring to cstring

Function used: sstr.convS2C()

parameters:- sstr.convS2C(sstring var,char * _Buff,size_t upto)

var -> the sstring which you want to convert
_Buff -> the cstring to which you want the value to be
_upto -> the specified value upto which the string value of var will be copied to _Buff

Return type:- sstring

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
