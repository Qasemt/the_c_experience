### the c experience

#### use libs:
1. https://troydhanson.github.io/uthash/

#### Error:crt detected that the application wrote to memory after end of heap buffer
```c++
 SessionHelper::serializeSessions(char** json)
 {
 .
 .
 .
 	*json =(char*) malloc((len_out*sizeof(char)));
	strcpy((*json),sb.GetString());
 }
 ...
  char* js;
	sh.serializeSessions(&js);
	delete js;
```
##### solution : 
```c++
*json =(char*) malloc((len_out*sizeof(char))+1);
```
