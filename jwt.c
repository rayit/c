#include <string.h>
#include <stdio.h>
#include <jwt.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <libgen.h>

int main(void)
{
	char opt_key_name[200] = "private.pem";
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
	fprintf(stderr, "priv key loaded %s (%zu)!\n", opt_key_name, key_len);
	
	/* add grant */
	ret = jwt_add_grant_int(jwt, "iat", iat);
	fprintf(stderr, "Adding claim %s with valu %s\n", "test", "test");
	jwt_add_grant(jwt, "test", "test");

	ret = jwt_set_alg(jwt, opt_alg, key, key_len);
	if (ret < 0) {
		fprintf(stderr, "jwt incorrect algorithm\n");
		jwt_free(jwt);
		return 1;
	}

	jwt_dump_fp(jwt, stderr, 1);

	fprintf(stderr, "jwt algo %s!\n", jwt_alg_str(opt_alg));

	char *out = jwt_encode_str(jwt);
	printf("%s\n", out);

	jwt_free_str(out);
	jwt_free(jwt);

	return 0;
}
