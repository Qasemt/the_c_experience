#include "test_elapse.h"
#include <time.h>
#include <Windows.h>
#include "test_time.h"


void run_elapse_()
{
	time_t start, end;
	struct tm * timeinfo;
	
	//______________________

	time(&start);
	end = addTime3(start, 1, TypeTime_Second);
	
	double dif = difftime(end, start);
	timeinfo = localtime(&start);
	Sleep(10);
//	printf("Elasped time is %.2lf seconds.", dif);
}
