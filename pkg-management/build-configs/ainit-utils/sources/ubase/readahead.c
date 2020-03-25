/* See LICENSE file for copyright and license details. */
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s file...\n", argv0);
}

int
main(int argc, char *argv[])
{
	FILE *fp;

	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	if (argc == 0)
		usage();

	for (; argc > 0; argc--, argv++) {
		if (!(fp = fopen(argv[0], "r"))) {
			weprintf("fopen %s:", argv[0]);
			continue;
		}
		if (readahead(fileno(fp), 0, -1) < 0)
			weprintf("readahead %s:", argv[0]);
		fclose(fp);
	}
	return 0;
}
