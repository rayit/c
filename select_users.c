#include <err.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
 
#include <kcgi.h>
#include <kcgijson.h>
#include <sqlite3.h>
 
int
main(void)
{
	struct kreq r;
	struct kjsonreq req;
	const char *page = "index";
   
	// DB
	sqlite3 *DB;
	sqlite3_stmt* stmt;
 
	if (khttp_parse(&r, NULL, 0, &page, 1, 0) != KCGI_OK)
		return EXIT_FAILURE;
 
	// TODO look into, now giving 500 error..
	//if (pledge("stdio", NULL) == -1) 
	//  err(EXIT_FAILURE, "pledge");
   
	// Sqlite3 open
	int rc = sqlite3_open("/tmp/_users.db", &DB);
	if( rc != SQLITE_OK) {
		printf("Error open DB %s\n", sqlite3_errmsg(DB)); 
		sqlite3_close(DB);
		return 1;
	}
	sqlite3_prepare_v2(DB, "SELECT * FROM user;", -1, &stmt, 0);
	int id;
	const unsigned char* description;
      
	khttp_head(&r, kresps[KRESP_STATUS], 
		"%s", khttps[KHTTP_200]);
	khttp_head(&r, kresps[KRESP_CONTENT_TYPE], 
		"%s", kmimetypes[r.mime]);
	khttp_body(&r);
	kjson_open(&req, &r);
	kjson_array_open(&req);
	while (sqlite3_step(stmt) != SQLITE_DONE) {
		id = sqlite3_column_int(stmt, 0);
		description = sqlite3_column_text(stmt, 1);
		
		kjson_obj_open(&req);
		kjson_putintp(&req, "id", id);
		kjson_putstringp(&req, "description", description);
		kjson_obj_close(&req);
		
   }
   kjson_array_close(&req);
   kjson_close(&req);
   khttp_free(&r);
   
   sqlite3_close(DB);
   return EXIT_SUCCESS;
}
