#include "test_hash_table.h"
#include <stdio.h>

example_user_t *users;
void init_Hash_Table(void)
{

	int i;
	example_user_t *user;

	/* create elements */
	for (i = 0; i < 500000; i++) {
		user = (example_user_t*)malloc(sizeof(example_user_t));

		if (user == NULL) {
			exit(-1);
		}

		user->id = i;
		user->cookie = i*i;

		HASH_ADD_INT(users, id, user);

		//HASH_ADD(alth, altusers, id, sizeof(int), user);
	}

}



struct example_user_t *find_user_Hash_Table(int user_id) {
	struct example_user_t *s;

	HASH_FIND_INT(users, &user_id, s);  /* s: output pointer */
	return s;
}

void delete_user_Hash_Table(struct example_user_t *user) {
	HASH_DEL(users, user);  /* user: pointer to deletee */
	free(user);
}

void delete_all_Hash_Table() {
	struct example_user_t *current_user, *tmp;

	HASH_ITER(hh, users, current_user, tmp) {
		HASH_DEL(users, current_user);  /* delete it (users advances to next) */
		free(current_user);             /* free it */
	}
	free(users);
	users = NULL;
}

void run_test_hash_table(){
	example_user_t *find;
	int findid=4;
	struct example_user_t *s, *tmp,*t;
	init_Hash_Table();

	//________________
	
	
	HASH_FIND_INT(users, &findid, s);  /* id already in the hash? */
	if (s!=NULL) {
		for(t=(example_user_t*)s->hh.next; s != NULL; t=(example_user_t*)t->hh.next) {
			printf("user id %d", t->id);
		}

	}



	//________________





	//	delete_all_Hash_Table();
	find = find_user_Hash_Table(500);
	if (find)
	{
		printf("user find %u", find->id);
	}
	delete_all_Hash_Table();
}