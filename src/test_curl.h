#pragma once
#ifdef __cplusplus
extern "C" {
#endif

void run_test_curl(void);
void curl_simple_http(char* my_url);

void curl_http_post(char* my_url);

#ifdef __cplusplus
}
#endif