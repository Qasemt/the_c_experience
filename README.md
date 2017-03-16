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
______
#### Error: LNK2005: DllMain already defined in dllmain.obj
##### solution : add this line to dllmain.cpp in top page 
```c++
link http://stackoverflow.com/questions/343368/error-lnk2005-dllmain12-already-defined-in-msvcrt-lib
extern "C" { int __afxForceUSRDLL; }
```
______
