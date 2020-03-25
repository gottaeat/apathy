/* See LICENSE file for copyright and license details. */
#include <sys/stat.h>

#include <fcntl.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s [-o num] -l num file ...\n", argv0);
}

int
main(int argc, char *argv[])
{
	int fd, ret = 0;
	off_t size = 0, offset = 0;

	ARGBEGIN {
	case 'l':
		size = estrtonum(EARGF(usage()), 1, MIN(LLONG_MAX, SIZE_MAX));
		break;
	case 'o':
		offset = estrtonum(EARGF(usage()), 0, MIN(LLONG_MAX, SIZE_MAX));
		break;
	default:
		usage();
	} ARGEND;

	if (!argc || !size)
		usage();

	for (; *argv; argc--, argv++) {
		if ((fd = open(*argv, O_RDWR | O_CREAT, 0644)) < 0) {
			weprintf("open %s:", *argv);
			ret = 1;
		} else if (posix_fallocate(fd, offset, size) < 0) {
			weprintf("posix_fallocate %s:", *argv);
			ret = 1;
		}

		if (fd >= 0 && close(fd) < 0) {
			weprintf("close %s:", *argv);
			ret = 1;
		}
	}

	return ret;
}
