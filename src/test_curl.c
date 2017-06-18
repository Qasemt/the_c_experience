
#include "test_curl.h"

#include <curl/curl.h>
#include "cjson/cJSON.h"


void run_test_curl()
{
	//	curl_simple_http("curl.haxx.se");
	curl_http_post("http://127.0.0.1:9999/service/core/modulelist");
}

void curl_simple_http(char* my_url)
{
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, my_url);
		res = curl_easy_perform(curl);

		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
}
struct ResponseStruct {
	char *memory;
	size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct ResponseStruct *mem = (struct ResponseStruct *)userp;

	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	if(mem->memory == NULL) {
		/* out of memory! */ 
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}
void curl_http_post(char* my_url)
{
	CURL *curl;
	CURLcode res;
	cJSON *root = NULL, *item = NULL;
	char *json = NULL;

	struct curl_slist *headers = NULL;
	struct ResponseStruct chunk;
	chunk.memory = malloc(1);  /* will be grown as needed by realloc above */ 
	chunk.size = 0;    /* no data at this point */ 
	//------------------------------------------------
	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("teamyar"));
	cJSON_AddItemToObject(root, "format", item = cJSON_CreateObject());
	cJSON_AddStringToObject(item, "type", "air");
	/* Print to text */
	json = cJSON_Print(root);
	//________________________________________________
	/* In windows, this will init the winsock stuff */ 
	//curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */ 
	curl = curl_easy_init();
	if(curl) {
		/* First set the URL that is about to receive our POST. This URL can
		just as well be a https:// URL if that is what should receive the
		data. */ 
		curl_easy_setopt(curl, CURLOPT_URL, my_url);

		//headers = curl_slist_append(headers, "Expect:");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
	    // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		/* send all data to this function  */ 
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		/* we pass our 'chunk' struct to the callback function */ 
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);



		res = curl_easy_perform(curl);
		/* Check for errors */ 
		if(res != CURLE_OK)
		{	
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
			goto cleanup;
		}
		
		printf("%s\n",chunk.memory);


	cleanup:
		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
		cJSON_Delete(root);
		free(chunk.memory);
		free(json);
	}
	curl_global_cleanup();
}
