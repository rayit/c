#include <err.h>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/* TODO add argv so we can pass password into */
int
main(int argc, char *argv[]) 
{
	char hash1[61];
	char *passwd;
	
	 switch( argc ) {
		case 2:
			passwd = argv[1];
			break;
		default:
			printf( "Use like: hash password" );
			return 1;
	}
	
	char *pref = "bcrypt,a";
	int pw = crypt_newhash(passwd, pref, hash1, sizeof(hash1));
	printf("\npw: %i", pw);
	printf("\n\nhash: %s", hash1);
	printf("\n\n\n");
	
	printf("-------- \n check pw \n ------");
	int ok = crypt_checkpass(passwd, hash1);
	if ( ok == 0 ) {
		printf("password is: OK");
	} else {
		printf("password is failse");
	}
	return 0;
}
