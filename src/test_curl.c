
#include "test_curl.h"

#include <curl/curl.h>
#include "cjson/cJSON.h"

#define serverip "127.0.0.1"
#define serverport 3031
#define ssl FALSE
struct ResponseStruct {
	char *memory;
	size_t size;
};
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct ResponseStruct *mem = (struct ResponseStruct *)userp;

	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL) {
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}
//________________________________________________________________
void run_test_curl()
{
	//	curl_simple_http("curl.haxx.se");
	//curl_http_post("http://127.0.0.1:9999/service/core/modulelist");
	request_GET("/api/deviceinfo");
}
//__________________READ RESPONSE GET_____________________________

void request_GET(char* url_req)
{
	char url_full[MAX_PATH]={0};
	CURL *curl_handle;
	CURLcode res;

	struct ResponseStruct chunk;

	chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
	chunk.size = 0;    /* no data at this point */

	curl_global_init(CURL_GLOBAL_ALL);

	
	curl_handle = curl_easy_init();
	
	sprintf(url_full, "%s%s:%d%s",(ssl==FALSE?"http://":"https://"),serverip, serverport, url_req);

	curl_easy_setopt(curl_handle, CURLOPT_URL, url_full);

	/* send all data to this function  */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	/* we pass our 'chunk' struct to the callback function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "GET");
	/* some servers don't like requests that are made without a user-agent
	field, so we provide one */
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:38.0) Jet API Http Client");

	/* get it! */
	res = curl_easy_perform(curl_handle);

	/* check for errors */
	if (res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
	}
	else {
		/*
		* Now, our chunk.memory points to a memory block that is chunk.size
		* bytes big and contains the remote file.
		*
		* Do something nice with it!
		*/

		printf("%lu bytes retrieved\n", (long)chunk.size);
	}

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);

	if (chunk.memory)
		free(chunk.memory);

	/* we're done with libcurl, so clean it up */
	curl_global_cleanup();

}
//________________________________________________________________
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
