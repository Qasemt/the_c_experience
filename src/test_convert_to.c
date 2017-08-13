
#include "test_convert_to.h"
#include <limits.h>
#include "stdio.h"
#include <stdint.h>
#include <stdlib.h>

void run_convert_to()
{

	//source convert :  http://www.convertdatatypes.com/Convert-char-Array-to-int64-in-C.html

	char number[40]={0};
	int32_t  num_int32 =INT_MAX;
	unsigned int num_uint32 = UINT_MAX;
	unsigned __int64  num_uint64 = UINT64_MAX;
	 __int64 num_int64 = INT64_MAX;


	sprintf_s(number,20,"%d",num_int32);
	num_int32= atoi("2");
	number[0]='\0';
	//---------------------+
	sprintf_s(number,20,"%u",num_uint32);
	 num_uint32=	strtoul(number,NULL,10);
	number[0]='\0';
	//---------------------+
	sprintf_s(number,20,"%I64d",num_int64);
	 num_int64=	_atoi64(number);
	number[0]='\0';
	//---------------------+
	sprintf_s(number,40,"%I64u",num_uint64);
	 num_uint64=	_strtoui64(number,NULL,10);
	number[0]='\0';
	//---------------------+





	



}
