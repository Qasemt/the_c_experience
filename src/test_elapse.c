#include "test_elapse.h"
#include <time.h>
#include <Windows.h>
#include "test_time.h"
#include <stdio.h>

void run_elapse_()
{
	time_t start, end;
	time_t t1;
	time_t t2;
	struct tm * timeinfo;
	//	double dif;
	//______________________

	time(&start);
	timeinfo = localtime(&start);
	printf ( "Current local time and date: %s \n\r", asctime (timeinfo) );
	end = addTime3(start, 1, TypeTime_Second);
	timeinfo = localtime(&end);
	//strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	printf ( "after [add] time : %s \n\r", asctime (timeinfo) );
	//___________________ Set only time from 1900___________
	time(&start);
	t1= setOnlyTime(start,10,20,1);

	printf ( "time 1 : %s \n\r",timeString(t1) );

	t2= setOnlyTime(start,10,20,2);
	printf ( "time 2 : %s \n\r",timeString(t2) );
}
