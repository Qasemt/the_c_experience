#include "common.h"
#include <stdio.h>
#include <time.h>


int * getRandom(void) {

	static int  r[10];
	int i;

	/* set the seed */
	srand((unsigned)time(NULL));

	for (i = 0; i < 10; ++i) {
		r[i] = rand();
		printf("%d\n", r[i]);
	}

	return r;
}
