#include <err.h>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sqlite3.h>

/* TODO add argv so we can pass password into */
int
main(void) 
{
	char *passwd = "password";
	sqlite3* DB;
	sqlite3_stmt* stmt;
	char hash1[61]; 
	int rc = sqlite3_open("/var/www/db/_users.db", &DB);
	if( rc != SQLITE_OK) {
		printf("Error open DB %s\n", sqlite3_errmsg(DB)); 
		sqlite3_close(DB);
		return 1;
	}
	char sql[200];
	strcpy(sql, "SELECT hash FROM user WHERE username=");
	strcat(sql, "\"");
	strcat(sql, "username");
	strcat(sql, "\"");
	rc = sqlite3_prepare_v2(DB, sql, -1, &stmt, 0);
	if( rc != SQLITE_OK) {
		printf("Error open DB %s\n", sqlite3_errmsg(DB)); 
		sqlite3_close(DB);
		return 1;
	}
	while (sqlite3_step(stmt) != SQLITE_DONE) { 
		char *src = (char*)sqlite3_column_text(stmt, 0);
		strncpy(hash1, src, 61);
	}
	printf("\nhash: %s", hash1);
	printf("\n--------\n check pw\n\n\n");
	int ok = crypt_checkpass(passwd, hash1);
	if ( ok == 0 ) {
		printf("password is: OK");
	} else {
		printf("password is false");
	}
	sqlite3_finalize(stmt);
	sqlite3_close(DB);
	return 0;
}

