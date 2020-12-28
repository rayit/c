#include <sqlite3.h>
#include <stdio.h>

/*
 * Create database
 */
static int createDb(const char* dir)
{
	sqlite3 *DB;
	int rc = 0;
	rc = sqlite3_open(dir, &DB);
	if ( rc != SQLITE_OK) {
		sqlite3_close(DB);
		printf("Error creating DB %s\n", sqlite3_errmsg(DB)); 
		return 1;
	} 
	sqlite3_close(DB);
	return 0;
}

/*
 * doSQL
 */
static int doSQL(
			const char* dir,
			char* sql) 
{
	char *err_msg = 0;
	sqlite3 *DB;
	int rc = 0;
	rc = sqlite3_open(dir, &DB);
	if ( rc != SQLITE_OK) {
		sqlite3_close(DB);
		printf("Error in creating database table open %s\n", sqlite3_errmsg(DB));
		return 1;
	}	
	// Run exec
	rc = sqlite3_exec(DB, sql, 0, 0, &err_msg);
	if ( rc != SQLITE_OK ) {
		sqlite3_close(DB);
		printf("Error execute sql %s\n", sqlite3_errmsg(DB));
		return 1;
	}
	sqlite3_close(DB);
	return 0;
}

/*
 * main
 */
int main(int argc, char *argv[]) 
{
    
    char *dir = NULL;
    char *sql = NULL;
    switch( argc ) {
		case 2:
			dir = argv[1];
			break;
		case 3:
			dir = argv[1];
			sql = argv[2];
			break;
		default:
			printf( "Use like: db_setup /var/www/cgi-bin/Users.db" );
			break;
	}
	if ( dir ) {
		createDb(dir);
		printf("Created DB");
	}
	if ( sql) {
		doSQL(dir, sql);
		printf("Database created and doSQL\n");
	}
    return 0;
}
