#include <err.h>
#include <sqlite3.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {

    sqlite3 *db;
    sqlite3_stmt* stmt;

    // sqlite3 open
    int rc = sqlite3_open("/cgi-bin/test.db", &db);
    // Error
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        puts("Status: 500 Internal Server Error\r");
        puts("Content-Type: text/html\r");
        puts("\r");
        puts("Error cannot open database\n");
        puts(sqlite3_errmsg(db));
        return 1;
    }
    // Output status 200
    puts("Status: 200 OK\r");
    puts("Content-Type: application/json\r");
    puts("\r");
    // sqlite prepare query
    sqlite3_prepare_v2(db, "SELECT * FROM Todos;", -1, &stmt, 0);
    int id;
    // int price;
    const unsigned char* name;
    int count = 0;
    // Loop and create json
    puts("[");
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        if (SQLITE_ROW && count > 0) {
            puts(",");
        }
        count++;
        id = sqlite3_column_int(stmt, 0);
        name = sqlite3_column_text(stmt, 1);
        // price = sqlite3_column_int(stmt, 2);
        puts("{");
        puts("\r");
        printf("\"id\" : %i", id);
        puts(",");
        printf("\"name\" : \"%s\"", name);
        // puts(",");
        // printf("\"price\" : %i", price);
        puts("\r");
        puts("}");
    }
    puts("]");
    // sqlite3 close
    sqlite3_close(db);
    return 0;
}
