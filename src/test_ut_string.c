#include "test_ut_string.h"
#include "utstring.h"
#include <string.h>
#include <stdio.h>

void run_test_UTString(void)
{
	UT_string *s;
	char f[10];
	utstring_new(s);
	utstring_printf(s, "hello world!");
	printf("char : %s  length :%d \n", utstring_body(s),(int)strlen(utstring_body(s)));
	 f[9]='\0' ;
	strcpy(f, "salam");
	utstring_clear(s);
	utstring_bincpy(s, f,2);

	utstring_free(s);

}
