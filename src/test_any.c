#include "test_any.h"
#include "string.h"
char *basename(char const *path)
{
	char *s = strrchr(path, '\\');
	if (s == NULL) {
		return _strdup(path);
	}
	else {
		return _strdup(s + 1);

	}
}
void run_test_any()
{
	char a[100] = { 0 };
	strcpy_s(a,100, "templates\\views\\templates\\index.html");
	const char *sep = basename(a);
	int tmp = 0;
	int a0 = 1 << 0;
	
	int a1 = 2 << 1;
	int a2 = 1 << 2;
	int a3 = 1 << 3;
	int a4 = 1 << 4;
	int a7 = 1 << 9;
	int base = a1 | a0;

	if ((base & a1) == a1)
	{
		int i = 0;

	}



}
