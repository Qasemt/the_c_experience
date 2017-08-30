

#include <stdio.h>

#include <windows.h>

#include "test_time.h"


INT64 addTime2(INT64 current_time,INT64 value,INT64 typeTime)
{
	if(value<0)
	{
		current_time -= (_abs64(value)*typeTime);
		current_time-=(current_time%typeTime);
	}
	else
	{
		current_time += (_abs64(value)*typeTime);
		current_time+=(current_time%typeTime);
	}
	return current_time;


}

INT64 addTime3(time_t current_time, int value, TypeTime typeTime)
{
	struct tm t;

	t= *localtime(&current_time);
	if (typeTime==TypeTime_Hour)
		t.tm_hour += value;
	if (typeTime == TypeTime_Minute) t.tm_min += value;
	else t.tm_sec += value;

	current_time = mktime(&t);
	return current_time;
}

INT64 setOnlyTime(time_t raw_time,int h,int m,int s)
{
	time_t raw_time_result;
	struct  tm loc;
	loc= *localtime(&raw_time);

	loc.tm_year=100; //year 2000 - 1900 = 100
	loc.tm_mon=1;
	loc.tm_mday=1;
	loc.tm_hour =h;
	loc.tm_min=m;
	loc.tm_sec=s;
	loc.tm_isdst=FALSE;
	raw_time_result =	mktime(&loc);
	return raw_time_result;
}
char buffer[26];
const char* timeString(time_t raw_time)
{
	struct tm * timeinfo;
	buffer[0]='\0';
	timeinfo = localtime(&raw_time);
	
	strftime(buffer, _countof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
	return  buffer;
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
	mint =addTime2(end_time,-27,_HOUR);
	hours_diff=diffTime(start_time,mint,_DAY);
}
