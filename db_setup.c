#include <err.h>
#include <sqlite3.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {

    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("/cgi-bin/test.db", &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        puts("Status: 500 Internal Server Error\r");
        puts("Content-Type: text/html\r");
	puts("\r");
	puts("Error cannot open database\n");
	fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *sql =
                "PRAGMA key = 'crackmeraye';"
                "PRAGMA cipher = 'aes-256-cfb';"
                "PRAGMA kdf_iter = '1000';"

                "DROP TABLE IF EXISTS Cars;"
                "CREATE TABLE Cars(Id INT, Name TEXT);"
                "INSERT INTO Cars VALUES(1, 'make login form');"
                "INSERT INTO Cars VALUES(2, 'make backend');"

                "DROP TABLE IF EXISTS Users;"
                "BEGIN TRANSACTION;"
                "CREATE TABLE Users(Id INTEGER PRIMARY KEY NOT NULL , Username TEXT NOT NULL, Password TEXT NOT NULL);"
                "END TRANSACTION;"
                "INSERT INTO Users VALUES(1, 'admin', 'ray');";


    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
	    puts("Status: 500 Internal Server Error\r");
        puts("Content-Type: text/html\r");
	    puts("\r");
	    puts("SQLITE ! OK");
	    puts(err_msg);
        return 1;
    }

    sqlite3_close(db);
    puts("Status: 200 OK\r");
    puts("Content-Type: text/html\r");
    puts("\r");
    puts("Database test created and table Users and Todos created\n");
    return 0;
}
