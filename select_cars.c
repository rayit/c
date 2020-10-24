#include <err.h>
#include <sqlite3.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int callback(void* data, int argc, char** argv, char** azColName)
{

    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int main(void) {

    sqlite3 *db;
    sqlite3_stmt* stmt;
    char *err_msg = 0;

    int rc = sqlite3_open("/cgi-bin/test.db", &db);

    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        puts("Status: 500 Internal Server Error\r");
        puts("Content-Type: text/html\r");
        puts("\r");
        puts("Error cannot open database\n");
        puts(sqlite3_errmsg(db));
        return 1;
    }

    char *sql = "SELECT * FROM Cars;";

    puts("Status: 200 OK\r");
    puts("Content-Type: application/json\r");
    puts("\r");
    // rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

//     if (rc != SQLITE_OK ) {
//         puts("Status: 500 Internal Server Error\r");
//         puts("Content-Type: text/html\r");
//         puts("\r");
//         puts("SQLITE ! OK");
//         puts(err_msg);
//         return 1;
//     }
    
    sqlite3_prepare_v2(db, "SELECT * FROM Cars;", -1, &stmt, 0);
    int id;
    char* name; 
    int count = 0;
    puts("[");
    while(sqlite3_step(stmt) != SQLITE_DONE) {
        if(SQLITE_ROW && count > 0) {
                puts(",");
        }
        count++;
        id = sqlite3_column_int(stmt, 0);
        name = sqlite3_column_text(stmt, 1);
        // name = sqlite3_column_string(stmt, 1);
        puts("{");
        puts("\r");
        printf("\"id\" : %i", id);
        puts(",");
        printf("\"name\" : \"%s\"", name);
        puts("\r");
        puts("}");
    }
    puts("]");
    sqlite3_close(db);
    return 0;
}
