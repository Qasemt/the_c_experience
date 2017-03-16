#include "test_cjson.h"
#include <stdio.h>
#include <stdlib.h>
#include "cjson/cJSON.h"
#include "test_hash_table.h"
void parse_Per_Item(cJSON *item,SessionProfile** outSessionList,int* length);
void tes_cjson_loadJson(char** json)
{
	cJSON * root ;
	cJSON *sessions_arr ;
	//cJSON *arr ;
//	int ff;
	int length_arr;
	SessionProfile* lst;


	tes_cjson_ReadFile("c:\\ff.txt",json);
	root = cJSON_Parse(*json);
	sessions_arr = cJSON_GetObjectItem(root,"sessions");
	parse_Per_Item(sessions_arr,&lst,&length_arr);

	free(lst);


}
//SessionProfile* list;
void parse_Per_Item(cJSON *item,SessionProfile** outSessionList,int* length)
{
	int i,j;
	SessionProfile* list;
	SessionProfile *session;
	*outSessionList=NULL;

	(*length)= cJSON_GetArraySize(item);

	if(length<=0)
		return;

	list= (SessionProfile*)malloc((*length)*sizeof(struct SessionProfile)+1);

	for (i = 0; i < cJSON_GetArraySize(item); i++)
	{
		cJSON *subitem ;
		cJSON *modules_access_item_arr ;
		session = (SessionProfile*)malloc(sizeof(SessionProfile));
		subitem = cJSON_GetArrayItem(item, i);
		session->id = cJSON_GetObjectItem(subitem,"id")->valueint;
		strcpy(session->sessionId , cJSON_GetObjectItem(subitem,"sessionId")->valuestring);
		//----------- array module access------------
		modules_access_item_arr =cJSON_GetObjectItem(subitem,"modules_access");

		for (j = 0; j < cJSON_GetArraySize(modules_access_item_arr); ++j)
		{
			//	cJSON *subitem_1 ;

			session->modules_access[j] = cJSON_GetArrayItem(modules_access_item_arr,j)->valueint;

		}
		memcpy(	&list[i], session, sizeof(SessionProfile));
		//	HASH_ADD_INT(list, id, session);
		//	free(session);

	}
	*outSessionList=list;
}

void tes_cjson_ReadFile(char *filename,char**buffer)
{

	int string_size, read_size;
	FILE *handler = fopen(filename, "r");
	*buffer=NULL;
	if (handler)
	{
		// Seek the last byte of the file
		fseek(handler, 0, SEEK_END);
		// Offset from the first to the last byte, or in other words, filesize
		string_size = ftell(handler);
		// go back to the start of the file
		rewind(handler);

		// Allocate a string that can hold it all
		*buffer = (char*)malloc ((string_size+1)*sizeof(char));

		// Read it all in one operation
		read_size=	 (int)fread (*buffer, sizeof(char), string_size, handler);

		// fread doesn't set it so put a \0 in the last position
		// and buffer is now officially a string
		(*buffer)[read_size] = '\0';


		// Always remember to close the file.
		fclose(handler);
	}


}
