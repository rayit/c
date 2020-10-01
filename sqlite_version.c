#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

int
main(void)
{
	puts("Status: 200 OK\r");
	puts("Content-Type: text/html\r");
	puts("\r");
	puts("Hello, world!");
 	printf("%s\n", sqlite3_libversion());	
	return(EXIT_SUCCESS);
}
