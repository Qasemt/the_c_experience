#pragma once

#ifndef TEST_HASH_TABLE_H
#define TEST_HASH_TABLE_H
#include "common.h"

#include "uthash.h"

extern example_user_t *users ;

void init_Hash_Table(void);

struct example_user_t *find_user_Hash_Table(int user_id);

void delete_user_Hash_Table(struct example_user_t *user);

void delete_all_Hash_Table();

void run_test_hash_table();

#endif












