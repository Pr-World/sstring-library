#include<stdio.h>
#include<string.h>
#include "sstring.h"
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<stddef.h>

/*
A Big Note To the ones saying dont return Local Variable Adresses

Below functions dont return any local variable addresses
to prove it, call the functions MULTIPLE times  -> you will see yourself

They return a typedef of strfunc which contains the string in array format
when the user does [functionname]([parameters])._str; the str array value is sent to the pointer
so no issue will be created! :D

*/


size_t sstrlen(sstring _str){
	//just as support for sstrings
	//same as strlen!
	return strlen(_str);
}

bool isGMCLCorrupt(void){
	//checks if global max char limit is corrupted
	if(SSTRING_GLOBAL_MAX_CHAR_LIMIT<=0){
		return true;
	}else{
		return false;
	}
}

sstrfunc cstr2sstr(char * _Buff){
	sstrfunc _null;
	nullify(_null._str,SSTRING_GLOBAL_MAX_CHAR_LIMIT);
	_null._err = SSTRING_NO_ERR;
	if(isGMCLCorrupt()){
		_null._err = SSTRING_GMCL_CORRUPT;
		return _null;
	}
	if(strlen(_Buff)>=SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = SSTRING_GMCL_ERR;
		return _null;
	}
	//blank string
	if(strlen(_Buff)==0){
		return _null;
	}
	sstrfunc _ret;
	strncpy(_ret._str,_Buff,strlen(_Buff));
	_ret._err = SSTRING_NO_ERR;
	return _ret;
}

Errtype sstr2cstr(sstring _sstr,char * _Cstr,size_t _upto){
	
	//first null out the _Cstr upto given length
	nullify(_Cstr,_upto);
	
	if(isGMCLCorrupt()){
		return SSTRING_GMCL_CORRUPT;
	}
	if(sstrlen(_sstr)>=SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		return SSTRING_GMCL_ERR;
	}
	
	//blank string
	if(sstrlen(_sstr)==0){
		return SSTRING_NO_ERR;
	}
	
	strncpy(_Cstr,_sstr,_upto);
	return SSTRING_NO_ERR;
}

sstrnum sstr2num(sstring _str){
	char cchar;
	int minus = 1;
	int plus=0;
	sstrnum _return;
	int pointplace=0;
	_return._err = SSTRING_NO_ERR;
	_return.is_num = true;
	if(isGMCLCorrupt()){
		_return._err = SSTRING_GMCL_CORRUPT;
		_return._num = 0;
		_return.is_num = false;
		return _return;
	}else if(sstrlen(_str)>=SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_return._err = SSTRING_GMCL_ERR;
		_return._num = 0;
		_return.is_num = false;
		return _return;
	}
	for(size_t i=0;i<sstrlen(_str);i++){
		cchar = _str[i];
		//if non integer found
		if(cchar<'0'||cchar>'9'){
			if(cchar=='-'&&i==0){
				minus = -1;
			}else if(cchar=='-'&&i>0){
				_return._num = 0;
				_return.is_num = false;
				_return._err = SSTRING_NO_ERR;
				return _return;
			}else if(cchar=='.'&&pointplace==0){
				pointplace+=1;
			}else if(cchar=='.'&&!(pointplace==0)){
				_return._num = 0;
				_return.is_num = false;
				_return._err = SSTRING_NO_ERR;
				return _return;
			}else if(cchar=='+'&&plus==0){
				plus=1;
			}else if(cchar=='+'&&plus==1){
				_return._num = 0;
				_return.is_num = false;
				_return._err = SSTRING_NO_ERR;
				return _return;
			}else{
				_return._num = 0;
				_return.is_num = false;
				_return._err = SSTRING_NO_ERR;
				return _return;
			}
		}else{
			//if integer
			
			//if position is '0'
			if(i==0){
				_return._num = cchar-'0';
				
			//if position not '0'
			}else{
				if(pointplace){
					_return._num+= (cchar-'0')/pow(10,pointplace);
					pointplace+=1;
				}else{
					_return._num*=10;
					_return._num+= (cchar-'0');
				}
			}
		}
	}
	_return._num*=minus;
	return _return;
	
}

sstrfunc ssubstr(sstring _str,int _pos,size_t _len){
	//dont store anything make null return value
	sstrfunc _null;
	
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(isGMCLCorrupt()){
		//gmcl is corrupt! errcode: #defined in sstring.h
		_null._err = SSTRING_GMCL_CORRUPT;
		return _null;
	}
	if(_pos<0){
		_null._err = SSTRING_INVALID_ARGS;
		return _null;
	}
	if(sstrlen(_str)>=SSTRING_GLOBAL_MAX_CHAR_LIMIT||_pos>=SSTRING_GLOBAL_MAX_CHAR_LIMIT||_len>=SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = SSTRING_GMCL_ERR;
		return _null;
	}
	
	if(_pos>=sstrlen(_str)||_pos<0||_len>=sstrlen(_str)||_len<0){
		_null._err = SSTRING_INVALID_ARGS;
		return _null;
	}
	
	sstrfunc _ret;
	
	_ret._err = SSTRING_NO_ERR;
	strncpy(_ret._str,_str+_pos,_len);
	_ret._str[_len] = '\0';
	return _ret;
	
}

sstrfunc sstrappend(sstring _var1,sstring _var2){
	//dont store anything make null return value
	sstrfunc _null;
	
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(isGMCLCorrupt()){
		//gmcl is corrupt! errcode: #defined in sstring.h
		_null._err = SSTRING_GMCL_CORRUPT;
		return _null;
	}
	
	
	if(sstrlen(_var1)+sstrlen(_var2)>=SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = SSTRING_GMCL_ERR;
		return _null;
	}
	//use of string.h functions -> far easier than my previous headscratching!
	char _ret1[sstrlen(_var1)+sstrlen(_var2)];
	strcpy(_ret1,_var1);
	strcat(_ret1,_var2);
	sstrfunc _ret;
	//no errors :D
	_ret._err = SSTRING_NO_ERR;
	strcpy(_ret._str,_ret1);
	return _ret;
}

Errtype nullify(char * _Buff,int _count){
	if(isGMCLCorrupt()){
		return SSTRING_GMCL_CORRUPT;		
	}else if(_count>SSTRING_GLOBAL_MAX_CHAR_LIMIT+1){
		return SSTRING_GMCL_ERR;
	}else{
		for(int i=0;i<_count;i++){
			_Buff[i] = '\0';
		}
		return SSTRING_NO_ERR;
	}
}

sstrfunc sstrinput(void){
	//dont store anything make null return value
	sstrfunc _null;
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(isGMCLCorrupt()){
		_null._err = SSTRING_GMCL_CORRUPT;
		return _null;
	}
	char _tmp[SSTRING_GLOBAL_MAX_CHAR_LIMIT];
	/*
	First, if i use fgets(_tmp,SSTRING_GLOBAL_MAX_CHAR_LIMIT,stdin) and limit it to gmcl,
	if the program is suppose inputting directory and filename and the path is greater
	than gmcl, the program will be in undefined behaviour if the rest code tries to open the file! because only
	string upto gmcl has been stored. and there are no errors when checking. to solve this :-
	created a bugcheck variable having greater space than gmcl i.e gmcl+1
	input into the variable limit it to gmcl+1
	check if its length exceeds or is equal to gmcl [i.e the extra byte is occupied]
	if yes: return gmcl_error immediately and terminate further process in the function -> now user will recieve error!
	if not, copy the input into tmp and execute rest of the code!

	*/
	char _bugcheck[SSTRING_GLOBAL_MAX_CHAR_LIMIT+1];
	//fgets for safety :)
	char * check_for_eof;
	check_for_eof=fgets(_bugcheck,SSTRING_GLOBAL_MAX_CHAR_LIMIT+1,stdin);
	if(check_for_eof==NULL){
		_null._err = SSTRING_EOF_ERR;
		return _null;
	}
	if(strlen(_bugcheck)>=SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = SSTRING_GMCL_ERR;
		return _null;
	}
	
	strncpy(_tmp,_bugcheck,SSTRING_GLOBAL_MAX_CHAR_LIMIT);
	
	sstrfunc _ret;
	//ret._str is array upto GLOBAL_MAX_CHAR_LIMIT
	//also tmp is array upto GLOBAL_MAX_CHAR_LIMIT
	//so its safe :) to use strcpy same as strncpy
	strcpy(_ret._str,_tmp);
	//'\n' avoided
	_ret._str[strlen(_tmp)-1] = '\0';
	_ret._err = SSTRING_NO_ERR;
	return _ret;
}

sstrfunc sstrinputpass(sstring show){
	//dont store anything make null return value
	sstrfunc _null;
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(isGMCLCorrupt()){
		_null._err = SSTRING_GMCL_CORRUPT;
		return _null;
	}
	char _tmp[SSTRING_GLOBAL_MAX_CHAR_LIMIT];
	//nullify string [if i dont use this WiErD things happen]
	int check_for_err;
	check_for_err = nullify(_tmp,SSTRING_GLOBAL_MAX_CHAR_LIMIT+1);
	if(check_for_err!=SSTRING_NO_ERR)
	{
		_null._err = SSTRING_NO_ERR;
		return _null;
	}
	char tmpchar;
	bool takeinput = true;
	int done=0;
	//until a certain char has not been pressed
	while(1>0){
		//if exceeds or proceeds to exceed global max char limit
		if(done>=SSTRING_GLOBAL_MAX_CHAR_LIMIT-1){
			takeinput=false;
		}
		tmpchar = getch();
		//if user pressed enter
		if(tmpchar=='\r'||tmpchar=='\n'){
			//if we were taking input
			if(takeinput){break;} else {
				//if takeinput was false return error when user presses enter!
				_null._err = SSTRING_GMCL_ERR;
				return _null;
			}
		}
		//if takeinput is true
		if(takeinput){
			if(tmpchar=='\b'){
				if(strlen(_tmp)>0){
					_tmp[strlen(_tmp)-1] = '\0';
					for(size_t i=0;i<sstrlen(show);i++){
						printf("\b");
					}
					for(size_t i=0;i<sstrlen(show);i++){
						printf(" ");
					}
					for(size_t i=0;i<sstrlen(show);i++){
						printf("\b");
					}
				}
			}else{
				_tmp[strlen(_tmp)]=tmpchar;
				printf(show);
			done+=1;
			}
		//if its false, just print out the show and rub it but dont do anything with _tmp variable!
		//as we will return error when 'enter' is pressed
		}else{
			if(tmpchar=='\b'){
				if(strlen(_tmp)>0){
					for(size_t i=0;i<sstrlen(show);i++){
						printf("\b");
					}
					for(size_t i=0;i<sstrlen(show);i++){
						printf(" ");
					}
					for(size_t i=0;i<sstrlen(show);i++){
						printf("\b");
					}
				}
			}else{
				printf(show);
			}
		}
		
	}
	//print newline buffer
	printf("\n");
	
	sstrfunc _ret;
	//ret._str is array upto GLOBAL_MAX_CHAR_LIMIT
	//also tmp is array upto GLOBAL_MAX_CHAR_LIMIT
	//so its safe :) to use strcpy same as strncpy
	strcpy(_ret._str,_tmp);
	//no errors
	_ret._err = SSTRING_NO_ERR;
	return _ret;
}

sstrfunc ssetchar(sstring _str,ssize_t _pos,char _ch){
	sstrfunc _null;
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(isGMCLCorrupt()){
		_null._err = SSTRING_GMCL_CORRUPT;
		return _null;
	}

	sstrfunc _ret;
	if(sstrlen(_str)>=SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = SSTRING_GMCL_ERR;
		return _null;
	}
	if(_pos>=sstrlen(_str)||_pos<0){
		_null._err = SSTRING_INVALID_ARGS;
		return _null;
	}
	strcpy(_ret._str,_str);
	_ret._str[_pos] = _ch;
	_ret._err = SSTRING_NO_ERR;

	return _ret;
}

void showerr(Errtype _err){
	
	if(_err==SSTRING_GMCL_CORRUPT){
		printf("\nError: SSTRING_GMCL_CORRUPT, SSTRING_GLOBAL_MAX_CHAR_LIMIT #defined in file 'sstring.h' is corrupted!\n");
	}else if(_err==SSTRING_GMCL_ERR){
		printf("\nError: SSTRING_GMCL_ERR, provided variable or input comes close or exceeds SSTRING_GLOBAL_MAX_CHAR_LIMIT!\n");
	}else if(_err==SSTRING_EOF_ERR){
		printf("\nError: SSTRING_EOF_ERR, End Of File occured without inputting any charachter!\n");
	}else if(_err==SSTRING_INVALID_ARGS){
		printf("\nError: SSTRING_INVALID_ARGS, you provided invalid arguments to a function inside file 'sstring.c'!\n");
	}else{
		printf("\nError: Unknown Error, an unknown error occured! errcode: %d\n",_err);
	}
	
}


charfunc sgetchar(sstring _str,ssize_t _pos){
	charfunc _null;
	//is global max char limit corrupted??
	if(isGMCLCorrupt()){
		_null._err = SSTRING_GMCL_CORRUPT;
		return _null;
	}
	// condition checking which are likely make error after
	if(sstrlen(_str)>=SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = SSTRING_GMCL_ERR;
		return _null;
	}
	
	if(_pos>=sstrlen(_str)||_pos<0||sstrlen(_str)<0){
		_null._err = SSTRING_INVALID_ARGS;
		return _null;
	}	
	charfunc chr;
	chr._char = _str[_pos];
	chr._err = SSTRING_NO_ERR;
	return chr;
}

//if the length of string is in size_t
//and charachters in it can also be beyond int who knows!
//used ssize_t to support returning negative numbers, i.e -> -1 and errors

//init is the place to start finding
ssize_t sstrfind(size_t init,sstring _str,sstring _find){
	size_t _len1 = sstrlen(_str);
	size_t _len2 = sstrlen(_find);
	size_t matching = 0;
	
	//is global max char limit corrupted??
	if(isGMCLCorrupt()){
		return SSTRING_GMCL_CORRUPT;
	}
	
	if(sstrlen(_str)>=SSTRING_GLOBAL_MAX_CHAR_LIMIT||sstrlen(_find)>=SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		return SSTRING_GMCL_ERR;
	}
	
	//some weird conditions check [user, are u fooling the function ?]
	if(_len2>_len1||init<0||init>_len1-1){
		return SSTRING_INVALID_ARGS;
	}
	
	//security check
	if(_len1>=SSTRING_GLOBAL_MAX_CHAR_LIMIT||_len2>=SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		return SSTRING_GMCL_ERR;
	}
	
	if(_len1==0||_len2==0){
		//obviously it wont be found if the string itself is null or the tobefound string is null
		return -1;
	}
	
	//the main finder -by myself
	for(size_t i=init;i<_len1+1;i++){
		if(_str[i]==_find[0]){
			for(int z=0;z<_len2+1;z++){
				if(matching==_len2){
					return i;
				}
				else if(_str[i+z]==_find[z]){
					matching+=1;
				}
				else{
					matching=0;
					break;
				}
			}
		}
	}
	return -1;
}

sstrfunc sstrreplace(sstring _Str, sstring _find, sstring _repl)
{
	size_t lens = sstrlen(_Str);
	size_t lenf = sstrlen(_find);
	size_t lenr = sstrlen(_repl);
	
	sstrfunc _null,_ret;
	int tmp;
	
	nullify(_null._str,SSTRING_GLOBAL_MAX_CHAR_LIMIT+1);
	nullify(_ret._str,SSTRING_GLOBAL_MAX_CHAR_LIMIT+1);
	
	bool _rarecondition = false;
	
	//a rare condition where wierd thing happens - found by myself when length is perfectly divisible by 16
	//this fixes it by appending 1 char to it which is not the find string.
	//at last it removes 1 charachter from last as it is appended here
	if(lens%16==0){
		if(sstrlen(_Str)+1>=SSTRING_GLOBAL_MAX_CHAR_LIMIT){
			_null._err =  SSTRING_GMCL_ERR;
			return _null;
		}
		if(_find!=" "){
			_Str = sstrappend(_Str," ")._str;
		}else{
			_Str = sstrappend(_Str,"~")._str;
		}
		_rarecondition = true;
	}

	sstrfuncerr tmp_check;
	
	tmp_check = sstrappend(_Str,"");
	if(tmp_check._err!=SSTRING_NO_ERR){
		_null._err = tmp_check._err;
		return _null;
	}

	if(isGMCLCorrupt()){
		_null._err = SSTRING_GMCL_CORRUPT;
		return _null;
	}
	
	if(lens>=SSTRING_GLOBAL_MAX_CHAR_LIMIT||lenf>=SSTRING_GLOBAL_MAX_CHAR_LIMIT||lenr>=SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = SSTRING_GMCL_ERR;
		return _null;
	}
	
	if(lens<=0||lenf<=0){
		_null._err = SSTRING_INVALID_ARGS;
		return _null;
	}
	
	sstring _Str2 = tmp_check._str;
	sstring tmps1,tmps2,tmps3;
	size_t tmpint1,tmpint2=0;
	
	for(tmpint1=0;_Str2[tmpint1]!='\0';tmpint1++){
		if(strstr(&_Str2[tmpint1],_find)==&_Str2[tmpint1]){
			tmpint2++;
			tmpint1+=lenf-1;
		}
	}
	
	//check if after replacing of strings or between replacing
	//the length exceeds SSTRING_GLOBAL_MAX_CHAR_LIMIT or not!
	if(lens-(lenf*tmpint2)+(lenr*tmpint2)>=SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = SSTRING_GMCL_ERR;
		return _null;
	}
	
	//the below code has been blindly done because all errors are checked beforehand
	tmpint1 = 0;
	while(*_Str2){
		if(strstr(_Str2,_find)==_Str2){
			//except strncpy() is used to stop buffer overflow
			strncpy(_ret._str+tmpint1,_repl,SSTRING_GLOBAL_MAX_CHAR_LIMIT);
			tmpint1+=lenr;
			_Str2+=lenf;
		}else{
			_ret._str[tmpint1++] = *_Str2++;
		}
	}
	
	if(_rarecondition==true){
		_ret._str[tmpint1-1] = '\0';
	}
	_ret._str[tmpint1] = '\0';
	_ret._err = SSTRING_NO_ERR;
	return _ret;
}