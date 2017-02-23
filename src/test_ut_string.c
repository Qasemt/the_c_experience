#include "test_ut_string.h"
#include "utstring.h"


void run_test_UTString(void)
{
	UT_string *s;

	utstring_new(s);
	utstring_printf(s, "hello world!");
	printf("char : %s  length :%d \n", utstring_body(s),strlen(utstring_body(s)));
	char f[10] = { '\0' };
	strcpy(f, "salam");
	utstring_clear(s);
	utstring_bincpy(s, f,2);

	utstring_free(s);

}