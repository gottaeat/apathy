/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s\n", argv0);
}

int
main(int argc, char *argv[])
{
	long pagesz;

	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	pagesz = sysconf(_SC_PAGESIZE);
	if (pagesz <= 0) {
		pagesz = sysconf(_SC_PAGE_SIZE);
		if (pagesz <= 0)
			eprintf("can't determine pagesize\n");
	}
	printf("%ld\n", pagesz);
	return 0;
}
