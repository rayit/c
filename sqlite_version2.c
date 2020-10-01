#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>


int main(void) 
{
	sqlite3 *db;
	sqlite3_stmt *res;
	int rc = sqlite3_open(":memory:", &db);
	if ( rc != SQLITE_OK) {
		puts("Status: 500 Internal Server Error\r");
		puts("Content-Type: text/html\r");
		puts("\r");
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	rc =  sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &res, 0);
	if ( rc != SQLITE_OK) {
		puts("Status: 500 Internal Server Error\r");
		puts("Content-Type: text/html\r");
		puts("\r");
		puts("Error executing SELECT SQLITE_VERSION()");
		sqlite3_close(db);
		return 1;
	}
	rc = sqlite3_step(res);
	if ( rc == SQLITE_ROW) {
		puts("Status: 200 OK\r");
		puts("Content-Type: text/html\r");
		puts("\r");
		puts("SQLite version: ");
		printf("%s\n", sqlite3_column_text(res, 0));
	}
	sqlite3_finalize(res);
	sqlite3_close(db);
	return 0;
}
