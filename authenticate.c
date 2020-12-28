#include <err.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
 
#include <kcgi.h>
#include <kcgijson.h>
#include <sqlite3.h>

int
main(void)
{
	// struct kreq r;
	char hash1[61];
	char *passwd = "password";
	char *pref = "bcrypt,a";
	// char *hash = "secrethash";
	int pw = crypt_newhash(passwd, pref, hash1, sizeof(hash1));
	printf("\npw: %i", pw);
	printf("\nhash: %s", hash1);
	
	printf("//////////// chech pw\n\n\n");
	int ok = crypt_checkpass("password", hash1);
	printf("password is: %i", ok);
	return 0;
}
