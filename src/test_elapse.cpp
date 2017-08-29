#include "test_elapse.h"
#include <time.h>
#include <Windows.h>


void run_elapse_()
{
	time_t start, end;
	struct tm * timeinfo;
	
	//______________________

	time(&start);
	Sleep(1000);
	time(&end);
	double dif = difftime(end, start);
	timeinfo = localtime(&start);
	Sleep(10);
//	printf("Elasped time is %.2lf seconds.", dif);
}
