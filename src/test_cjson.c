#include "test_cjson.h"
#include <stdio.h>
#include <stdlib.h>

void tes_cjson_loadJson(char** json)
{
	tes_cjson_ReadFile("c:\\ff.txt",json);
	//(*json)= ty_read_to_text_file("c:\\ff.txt");
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
	read_size=	 fread (*buffer, sizeof(char), string_size, handler);

		// fread doesn't set it so put a \0 in the last position
		// and buffer is now officially a string
		(*buffer)[read_size] = '\0';

	
       // Always remember to close the file.
       fclose(handler);
    }

 
}
