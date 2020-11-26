//
// Created by rayit on 11/17/20.
//
#include "Db.h"

int Db::connect() {

    // sqlite3 open
    sqlite3 *db;
    int rc = sqlite3_open("/cgi-bin/test.db", &db);
    // Error
//    if (this->rc != SQLITE_OK) {
//        sqlite3_close(this->db);
//        puts("Status: 500 Internal Server Error\r");
//        puts("Content-Type: text/html\r");
//        puts("\r");
//        puts("Error cannot open database\n");
//        puts(sqlite3_errmsg(this->db));
//        return 1;
//    }
    return 0;
}

int Db::test() {
    return 0;
}

//int Db::start() {
//    this->connect();
//    return 0;
//}
