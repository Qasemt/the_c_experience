#pragma once

#ifndef TEST_CJSON_H
#define TEST_CJSON_H
#include  "./uthash.h"
typedef  struct SessionProfile
{
	int id;
	char sessionId[20];
	int modules_access[20];
	UT_hash_handle hh;



}SessionProfile;
void tes_cjson_loadJson(char** json);
void tes_cjson_ReadFile(char *filename,char**buffer);





#endif