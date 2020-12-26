#include <err.h>
#include <sqlite3.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/** 
 * Setup DB and put dummie data in
 * parameter DB name and path
 */
int main(int argc, char *argv[]) {
	
	sqlite3 *db;
    char *err_msg = 0;
    char *db_name = "test.db";
    
    if ( argc == 2 ) {
		printf( "arg %d: %s\n", 1, argv[1] );
		db_name = argv[1];
	}
    
    int rc = sqlite3_open(db_name, &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
		puts("Error cannot open database\n");
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *sql =
        "PRAGMA key = 'crackmeray';"
        "PRAGMA cipher = 'aes-256-cfb';"
        "PRAGMA kdf_iter = '1000';"

        "DROP TABLE IF EXISTS Todos;"
        "CREATE TABLE Todos(Id INT, Name TEXT);"
        "INSERT INTO Todos VALUES(1, 'Login system');"
        "INSERT INTO Todos VALUES(2, 'Security');"
        "INSERT INTO Todos VALUES(3, 'Volkswagen');"

        "DROP TABLE IF EXISTS Users;"

        "BEGIN TRANSACTION;"
        "CREATE TABLE Users(Id INTEGER PRIMARY KEY NOT NULL , Username TEXT "
        "NOT NULL, Password TEXT NOT NULL);"
        "END TRANSACTION;"
        "INSERT INTO Users VALUES(1, 'admin', 'ray');";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        puts("SQLITE ! OK");
        puts(err_msg);
        return 1;
    }

    sqlite3_close(db);
    puts("\r");
    puts("Database test created and table Users and Todos created\n");
    return 0;
}
