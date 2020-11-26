//
// Created by rayit on 11/17/20.
//
#include <err.h>
#include <sqlite3.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef C_DB_H
#define C_DB_H

class Db
{

private:


    //sqlite3_stmt* stmt;
//    int start();
    int connect();
public:
    int test();
};

#endif //C_DB_H
