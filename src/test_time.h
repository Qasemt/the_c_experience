#pragma once
#include <basetsd.h>
#include <time.h>
#define _SECOND ((__int64) 10000000)
#define _MINUTE (60  * _SECOND)
#define _HOUR   (60  * _MINUTE)
#define _DAY    (24  * _HOUR)
#define _MONTH  (31  * _DAY)
#define _YEAR   (365 * _DAY)

typedef enum  TypeTime
{
	TypeTime_Second, TypeTime_Minute, TypeTime_Hour

}TypeTime;
void run_test_Time(void);
INT64 addTime2(INT64 current_time, INT64 value, INT64 typeTime);
int addTime3(time_t current_time, int value, TypeTime typeTime);
INT64 diffTime2(INT64 time1, INT64 time2, INT64 typeTime);
int diffTime3(int time1, int time2, int typeTime);