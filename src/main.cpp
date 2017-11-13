// testc.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include <tchar.h>
#include <conio.h>
#include "string.h"
#include "common.h"
#include "test_hash_table.h"
#include "utstring.h"
#include "test_ut_string.h"
#include "test_cjson.h"
#include "test_ip.h"
#include  "test_curl.h"
#include "test_any.h"
#include "test_convert_to.h"
//#include <winbase.h>
#include  "test_time.h"
#include "test_elapse.h"


int _tmain(int argc, _TCHAR* argv[])
{
    /*INT64 f1=_I64_MAX;
	UINT64 f2=_I64_MAX;
	InterlockedIncrement64(&f1);
	f2=f1;*/

	//run_elapse_();

	//run_test_Time();
	//__________________________________________
	//	run_convert_to();
	 	//	run_convert_to();
	//__________________________________________
	//run_test_any();
	//__________________________________________
		run_test_curl();
	//__________________________________________
	//	run_test_ip();
	//__________________________________________
	//run_test_hash_table();
	//__________________________________________
	//run_test_UTString();

	//__________________________________________
	//char* jsonstr;
	//tes_cjson_loadJson(&jsonstr);


	getchar();



	return 0;
}

