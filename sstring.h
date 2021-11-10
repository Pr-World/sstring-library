
#ifndef SSTRING_H_INCL
//stdbool for sstrnum typedef
#include<stdbool.h>
#include<stddef.h>
#define SSTRING_H_INCL

#define SSTRING_GLOBAL_MAX_CHAR_LIMIT 500

#define SSTRING_NO_ERR -80
#define SSTRING_GMCL_CORRUPT -81
#define SSTRING_INVALID_ARGS -82
#define SSTRING_GMCL_ERR -83
#define SSTRING_EOF_ERR -84

typedef int Errtype;

typedef struct{
	double _num;
	bool is_num;
	Errtype _err;
}sstrnum;

typedef char * sstring;

typedef struct{
	char _str[SSTRING_GLOBAL_MAX_CHAR_LIMIT];
	Errtype _err;
}sstrfunc;

typedef struct{
	char _char;
	Errtype _err;
}charfunc;

typedef sstrfunc sstrfuncerr;

bool isGMCLCorrupt(void);
sstrfunc sstrreplace(sstring _Str, sstring _find, sstring _repl);
Errtype nullify(char * _Buff,int _count);
sstrnum sstr2num(sstring _str);
sstrfunc cstr2sstr(char * _Buff);
Errtype sstr2cstr(sstring _sstr,char * _Cstr,size_t _upto);
sstrfunc sstrappend(sstring _var1,sstring _var2);
sstrfunc sstrinput(void);
ssize_t sstrfind(size_t init,sstring _str,sstring _find);
size_t sstrlen(sstring _str);
sstrfunc ssetchar(sstring _str,ssize_t _pos,char _ch);
sstrfunc ssubstr(sstring _str,int _pos,size_t _len);
charfunc sgetchar(sstring _str,ssize_t _pos);
sstrfunc sstrinputpass(sstring show);
void showerr(Errtype _err);

#endif