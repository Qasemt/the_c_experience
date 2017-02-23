/*
common
*/


#ifndef COMMON_H
#define COMMON_H

#include "uthash.h"


typedef struct  ST
{
	int id;
	char* name;
} ST;

/* function to generate and retrun random numbers. */
int * getRandom(void);


typedef struct example_user_t {
	int id;
	int cookie;
	UT_hash_handle hh;
	UT_hash_handle alth;
} example_user_t;


#endif