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
#### Error: Betwen ws2def.h and winsock.h
The Problem
```c++
ws2def.h(91): warning C4005: ‘AF_IPX’ : macro redefinition
winsock.h(460) : see previous definition of ‘AF_IPX’
ws2def.h(131): warning C4005: ‘AF_MAX’ : macro redefinition
winsock.h(479) : see previous definition of ‘AF_MAX’
```
The Solution
```c++
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
 
int main( int argc, char* argv[] )
{
  return 0;
}
```
soure : http://www.zachburlingame.com/2011/05/resolving-redefinition-errors-betwen-ws2def-h-and-winsock-h/
______
