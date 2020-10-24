#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    if (-1 == pledge("stdio", NULL))
        		err(EXIT_FAILURE, NULL);
    puts("Status: 200 OK\r");
    puts("Content-Type: text/html\r");
    puts("\r");
    puts("Hello, world!");
    return(EXIT_SUCCESS);
}
