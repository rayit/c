#include <err.h>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
 
#include <kcgi.h>
#include <kcgijson.h>
#include <kcgihtml.h>
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
	int rc = sqlite3_open("/tmp/_users.db", &DB);
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
		strcpy(hash1, src);
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

static void process_safe(struct kreq *r) {
	struct kpair *p;
	struct kpair *u;
	struct khtmlreq req;
	const char *username;
	const char *password;
	khtml_open(&req, r, 0);
	khtml_elem(&req, KELEM_P);
	khtml_puts(&req, "---");
	/* Check for password and username */
	if ((p = r->fieldmap[KEY_PASSWORD]) && (u = r->fieldmap[KEY_USERNAME])) {
		username = u->parsed.s;
		password = p->parsed.s;
		khtml_elem(&req, KELEM_I);
		khtml_puts(&req, "Username: ");
		khtml_puts(&req, username);
		khtml_elem(&req, KELEM_BR);
		khtml_puts(&req, "Password: ");
		khtml_puts(&req, password);
		/* TODO extra validation? */
		khtml_elem(&req, KELEM_BR);
		int ok = checkPassword(password, username);
		if ( ok == 0 ) {
			khtml_elem(&req, KELEM_I);
			khtml_puts(&req, "Password ok");
		} else {
			khtml_elem(&req, KELEM_I);
			khtml_puts(&req, "Password false");
		}
	} else if (r->fieldnmap[KEY_USERNAME] || r->fieldnmap[KEY_PASSWORD]) {
		khtml_elem(&req, KELEM_I);
		khtml_puts(&req, "failed parse");
	} else {
		khtml_elem(&req, KELEM_I);
		khtml_puts(&req, "not provided");
	}
	khtml_close(&req);
}

static enum khttp sanitise(const struct kreq *r) {
	if (r->page != PAGE_INDEX)
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
		khttp_head(&r, kresps[KRESP_STATUS],
			"%s", khttps[KHTTP_200]);
		khttp_head(&r, kresps[KRESP_CONTENT_TYPE],
			"%s", kmimetypes[r.mime]);
		khttp_body(&r);
		process_safe(&r);
	}
	khttp_free(&r);
	return 0;
}
