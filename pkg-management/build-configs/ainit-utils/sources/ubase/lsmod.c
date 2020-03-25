/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"
#include "util.h"

static void parse_modline(char *buf, char **name, char **size,
			  char **refcount, char **users);

static void
usage(void)
{
	eprintf("usage: %s\n", argv0);
}

int
main(int argc, char *argv[])
{
	const char *modfile = "/proc/modules";
	FILE *fp;
	char *buf = NULL;
	char *name, *size, *refcount, *users;
	size_t bufsize = 0;
	size_t len;

	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	if (argc > 0)
		usage();

	fp = fopen(modfile, "r");
	if (!fp)
		eprintf("fopen %s:", modfile);

	printf("%-23s Size  Used by\n", "Module");

	while (agetline(&buf, &bufsize, fp) != -1) {
		parse_modline(buf, &name, &size, &refcount, &users);
		if (!name || !size || !refcount || !users)
			eprintf("invalid format: %s\n", modfile);
		len = strlen(users) - 1;
		if (users[len] == ',' || users[len] == '-')
			users[len] = '\0';
		printf("%-20s%8s%3s %s\n", name, size, refcount,
		       users);
	}
	if (ferror(fp))
		eprintf("%s: read error:", modfile);
	free(buf);
	fclose(fp);
	return 0;
}

static void
parse_modline(char *buf, char **name, char **size,
	      char **refcount, char **users)
{
	*name = strtok(buf, " ");
	*size = strtok(NULL, " ");
	*refcount = strtok(NULL, " ");
	*users = strtok(NULL, " ");
}
