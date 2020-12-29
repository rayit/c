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
main(void) 
{
	char hash1[61];
	char *passwd = "rayrayray";
	char *pref = "bcrypt,a";
	// char *hash = "secrethash";
	int pw = crypt_newhash(passwd, pref, hash1, sizeof(hash1));
	printf("\npw: %i", pw);
	printf("\nhash: %s", hash1);
	
	/*
	printf("//////////// chech pw\n\n\n");
	int ok = crypt_checkpass("password", hash1);
	if ( ok == 0 ) {
		printf("password is: OK");
	} else {
		printf("password is failse");
	}
	*/
	return 0;
}
