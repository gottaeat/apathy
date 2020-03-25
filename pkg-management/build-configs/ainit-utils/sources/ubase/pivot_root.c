/* See LICENSE file for copyright and license details. */
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s new-root put-old\n", argv0);
}

int
main(int argc, char *argv[])
{
	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	if (argc < 2)
		usage();

	if (syscall(SYS_pivot_root, argv[0], argv[1]) < 0)
		eprintf("pivot_root:");

	return 0;
}
