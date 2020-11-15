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
        "PRAGMA key = 'crackmeray';"
        "PRAGMA cipher = 'aes-256-cfb';"
        "PRAGMA kdf_iter = '1000';"

        "DROP TABLE IF EXISTS Todos;"
        "CREATE TABLE Todos(Id INT, Name TEXT);"
        "INSERT INTO Todos VALUES(1, 'Audi');"
        "INSERT INTO Todos VALUES(2, 'Mercedes');"
        "INSERT INTO Todos VALUES(3, 'Skoda');"
        "INSERT INTO Todos VALUES(4, 'Volvo');"
        "INSERT INTO Todos VALUES(5, 'Bentley');"
        "INSERT INTO Todos VALUES(6, 'Citroen');"
        "INSERT INTO Todos VALUES(7, 'Hummer');"
        "INSERT INTO Todos VALUES(8, 'Volkswagen');"

        "DROP TABLE IF EXISTS Users;"

        "BEGIN TRANSACTION;"
        "CREATE TABLE Users(Id INTEGER PRIMARY KEY NOT NULL , Username TEXT "
        "NOT NULL, Password TEXT NOT NULL);"
        "END TRANSACTION;"
        "INSERT INTO Users VALUES(1, 'admin', 'ray');";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
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
