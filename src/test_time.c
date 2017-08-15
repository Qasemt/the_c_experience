
#include "test_time.h"
#include <stdio.h>
#include <time.h>
#include <windows.h>

#define _SECOND ((__int64) 10000000)
#define _MINUTE (60  * _SECOND)
#define _HOUR   (60  * _MINUTE)
#define _DAY    (24  * _HOUR)
#define _MONTH  (31  * _DAY)
#define _YEAR   (365 * _DAY)

INT64 addTime(INT64 current_time,INT64 value,INT64 typeTime)
{
	if(value<0)
	{
		current_time-=(_abs64(value)*typeTime);
		current_time-=(current_time%typeTime);
	}
	else
	{
		current_time+=(_abs64(value)*typeTime);
		current_time+=(current_time%typeTime);
	}
	return current_time;


}
INT64 diffTime(INT64 time1,INT64 time2,INT64 typeTime)
{
	return  (time1-time2)/typeTime;

}


void run_test_Time(void)
{

	INT64 start_time;
	INT64 end_time;
	INT64 secs_diff;
	INT64 hours_diff;
	INT64 mint;
	//C++
	/*SYSTEMTIME s_time;
	SYSTEMTIME stNow;
	FILETIME ftNow;
	FILETIME ftNow1;
	GetSystemTime(&stNow);
	INT64 res=0;
	SystemTimeToFileTime(&stNow,((FILETIME*)&res));
	char time[200]={0};*/
	//-----------------------------------------------
	GetSystemTimeAsFileTime((FILETIME*)&start_time);

	GetSystemTimeAsFileTime((FILETIME*)& end_time);
	//---------------------
	secs_diff = (end_time-start_time)/_SECOND;
	//---------------------
	mint =addTime(end_time,-27,_HOUR);
	hours_diff=diffTime(start_time,mint,_DAY);
}
