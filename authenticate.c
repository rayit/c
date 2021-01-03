#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <jwt.h>
 
#include <kcgi.h>
#include <kcgijson.h>
#include <sqlite3.h>

enum key {
	KEY_USERNAME,
	KEY_PASSWORD,
	KEY__MAX
};

enum page {
  PAGE_INDEX,
  PAGE__MAX
};

int checkPassword(const char *p, const char *u) {
	sqlite3* DB;
	sqlite3_stmt* stmt;
	char hash1[61];
	int rc = sqlite3_open("/db/_users.db", &DB);
	if( rc != SQLITE_OK) {
		sqlite3_close(DB);
		return 1;
	}
	char sql[200];
	strcpy(sql, "SELECT hash FROM user WHERE username=");
	strcat(sql, "\"");
	strcat(sql, u);
	strcat(sql, "\"");
	sqlite3_prepare_v2(DB, sql, -1, &stmt, 0);
	while (sqlite3_step(stmt) != SQLITE_DONE) { 
		char *src = (char*)sqlite3_column_text(stmt, 0);
		strncpy(hash1, src, 61);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(DB);
	return crypt_checkpass(p, hash1);
}

const char *const pages[PAGE__MAX] = {
	"index", /* PAGE_INDEX */
};

static const struct kvalid keys[KEY__MAX] = {
	{ kvalid_stringne, "username" }, /* KEY_STRING */
	{ kvalid_stringne, "password" },
};

const char *createJwt(const char *username) {
	char opt_key_name[200] = "/private.pem";
	jwt_alg_t opt_alg = JWT_ALG_RS256;
	int ret = 0;
	jwt_t *jwt;
	time_t iat = time(NULL);
	unsigned char key[10240];
	size_t key_len = 0;
	FILE *fp_priv_key;
	
	ret = jwt_new(&jwt);
	
	/* Load key pem from file */
	/* TODO check file present */
	fp_priv_key = fopen(opt_key_name, "r");
	key_len = fread(key, 1, sizeof(key), fp_priv_key);
	fclose(fp_priv_key);
	key[key_len] = '\0';
	
	/* add grant */
	ret = jwt_add_grant_int(jwt, "iat", iat);
	jwt_add_grant(jwt, "username", username);
	// jwt_add_grant(jwt, "admin", "1");
	ret = jwt_set_alg(jwt, opt_alg, key, key_len);
	if (ret < 0) {
		jwt_free(jwt);
		return "ERROR";
	}
	jwt_dump_fp(jwt, stderr, 1);
	char *out = jwt_encode_str(jwt);
	// jwt_free_str(out);
	jwt_free(jwt);
	return out;
}

static void process_safe(struct kreq r) {
	struct kpair *p;
	struct kpair *u;
	struct kjsonreq req;
	const char *username;
	const char *password;

	/* Check for password and username */
	if ((p = r.fieldmap[KEY_PASSWORD]) && (u = r.fieldmap[KEY_USERNAME])) {
		username = u->parsed.s;
		password = p->parsed.s;
		/* TODO extra validation? */
		/* JSON */
		int ok = checkPassword(password, username);
		if ( ok == 0 ) {
			khttp_head(&r, kresps[KRESP_STATUS], 
				"%s", khttps[KHTTP_200]);
			khttp_head(&r, kresps[KRESP_CONTENT_TYPE], 
				"%s", kmimetypes[r.mime]);
			khttp_body(&r);
			kjson_open(&req, &r);
			kjson_obj_open(&req);
			/* Return jwt and json */
			const char *jwt = createJwt(username);
			kjson_obj_open(&req);
			// kjson_putintp(&req, "id", id);
			kjson_putstringp(&req, "username", username);
			kjson_putstringp(&req, "jwt", jwt);
			kjson_obj_close(&req);
			kjson_close(&req);
		} else {
			khttp_head(&r, kresps[KRESP_STATUS], 
				"%s", khttps[KHTTP_403]);
			khttp_head(&r, kresps[KRESP_CONTENT_TYPE], 
				"%s", kmimetypes[r.mime]);
			khttp_body(&r);
			kjson_open(&req, &r);
			kjson_obj_open(&req);
			kjson_putstringp(&req, "error", "Password false");
			kjson_obj_close(&req);
			kjson_close(&req);
		}
	} else if (r.fieldnmap[KEY_USERNAME] || r.fieldnmap[KEY_PASSWORD]) {
		khttp_head(&r, kresps[KRESP_STATUS], 
			"%s", khttps[KHTTP_500]);
		khttp_head(&r, kresps[KRESP_CONTENT_TYPE], 
			"%s", kmimetypes[r.mime]);
		khttp_body(&r);
		kjson_open(&req, &r);
		kjson_obj_open(&req);
		kjson_putstringp(&req, "error", "failed parse");
		kjson_obj_close(&req);
		kjson_close(&req);
	} else {
		khttp_head(&r, kresps[KRESP_STATUS], 
			"%s", khttps[KHTTP_400]);
		khttp_head(&r, kresps[KRESP_CONTENT_TYPE], 
			"%s", kmimetypes[r.mime]);
		khttp_body(&r);
		kjson_open(&req, &r);
		kjson_obj_open(&req);
		kjson_putstringp(&req, "error", "missing values");
		kjson_obj_close(&req);
		kjson_close(&req);
	}

}

static enum khttp sanitise(const struct kreq *r) {
	//if ( r->method == KMETHOD_OPTIONS )
	//	return KHTTP_200;
	//else
	if (r->method == KMETHOD_POST ) 
		return KHTTP_200;
	else if (r->page != PAGE_INDEX)
		return KHTTP_404;
	else if (*r->path != '\0') /* no index/xxxx */
		return KHTTP_404;
	else if (r->mime != KMIME_TEXT_HTML)
		return KHTTP_404;
	else if (r->method != KMETHOD_GET)
		return KHTTP_405;
  return KHTTP_200;
}

int
main(void)
{
	struct kreq r;
	enum khttp er;
	if (khttp_parse(&r, keys, KEY__MAX,
	  pages, PAGE__MAX, PAGE_INDEX) != KCGI_OK)
		return 0;
	if ((er = sanitise(&r)) != KHTTP_200) {
		khttp_head(&r, kresps[KRESP_STATUS],
			"%s", khttps[er]);
		khttp_head(&r, kresps[KRESP_CONTENT_TYPE],
			"%s", kmimetypes[KMIME_TEXT_PLAIN]);
		khttp_body(&r);
		if (KMIME_TEXT_HTML == r.mime)
			khttp_puts(&r, "Could not service request.");
	} else {
		process_safe(r);
	}
	khttp_free(&r);
	return 0;
}
