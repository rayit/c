#include <err.h>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[]) 
{
	char *hash1;
	char hash[61];
	char *passwd;
	
	switch( argc ) {
		case 3:
			passwd = argv[1];
			hash1 = argv[2];
			strncpy(hash, hash1, 61);
			break;
		default:
			printf( "Use like: unhash2 paswd hash" );
			return 1;
	}
	
	printf("-------- \n chech pw \n ------");
	printf("\npw: %s", passwd);
	printf("\nhash1: %s", hash);
	int ok = crypt_checkpass(passwd, hash);
	if ( ok == 0 ) {
		printf("\n\npassword is: OK");
	} else {
		printf("\n\npassword is false");
	}
	return 0;
}
