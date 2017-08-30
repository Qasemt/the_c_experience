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
	int a1,a2,a3,a4,a7,base,tmp,a0;
	char sep[50];
	char a[100] = { 0 };
	strcpy_s(a,100, "templates\\views\\templates\\index.html");
	strcpy_s(sep ,50, basename(a));
	tmp = 0;
	a0 = 1 << 0;

	a1 = 2 << 1;
	a2 = 1 << 2;
	a3 = 1 << 3;
	a4 = 1 << 4;
	a7 = 1 << 9;
	base = a1 | a0;

	if ((base & a1) == a1)
	{
		int i = 0;

	}
}
