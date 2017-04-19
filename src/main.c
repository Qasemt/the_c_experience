// testc.cpp : Defines the entry point for the console application.
//

#include <stdlib.h> 
#include "string.h"
#include "common.h"
#include "test_hash_table.h"
#include "utstring.h"
#include "test_ut_string.h"
#include "test_cjson.h"
#include "test_ip.h"


int main(int argc, char* argv[])
{

	//__________________________________________
		run_test_ip();
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

