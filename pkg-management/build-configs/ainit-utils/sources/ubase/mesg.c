/* See LICENSE file for copyright and license details. */
#include <sys/stat.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s [n|y]\n", argv0);
}

int
main(int argc, char *argv[])
{
	struct stat sb;
	mode_t mode;

	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	if (argc > 1)
		usage();

	if (isatty(2) == 0)
		eprintf("stderr: not a tty\n");

	if (fstat(2, &sb) < 0)
		eprintf("fstat stderr:");

	if (argc == 0) {
		puts(sb.st_mode & (S_IWGRP | S_IWOTH) ? "is y" : "is n");
		return 0;
	}

	if (argv[0][0] == 'y' && argv[0][1] == '\0')
		mode = sb.st_mode | S_IWGRP | S_IWOTH;
	else if (argv[0][0] == 'n' && argv[0][1] == '\0')
		mode = sb.st_mode & ~(S_IWGRP | S_IWOTH);
	else
		usage();

	if (fchmod(2, mode) < 0)
		eprintf("fchmod stderr:");

	return 0;
}
