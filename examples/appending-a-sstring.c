#include <stdio.h>
#include <stdlib.h>
#include "sstring.h"


/*
Example usage of appending a string!
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
	a = sstr.newstr("Hello");
	checkforerrs(a);
	
	//append
	a = sstr.append(a," World!");
	checkforerrs(a);
	
	//display
	printf("%s",sstr.val(a));
	
	return 0;
}
