/* See LICENSE file for copyright and license details. */
#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s [-c] -s size file...\n", argv0);
}

int
main(int argc, char *argv[])
{
	int cflag = 0, sflag = 0;
	int fd, i, ret = 0;
	long size = 0;

	ARGBEGIN {
	case 's':
		sflag = 1;
		size = estrtol(EARGF(usage()), 10);
		break;
	case 'c':
		cflag = 1;
		break;
	default:
		usage();
	} ARGEND;

	if (argc < 1 || sflag == 0)
		usage();

	for (i = 0; i < argc; i++) {
		fd = open(argv[i], O_WRONLY | (cflag ? 0 : O_CREAT), 0644);
		if (fd < 0) {
			weprintf("open: cannot open `%s' for writing:", argv[i]);
			ret = 1;
			continue;
		}
		if (ftruncate(fd, size) < 0) {
			weprintf("ftruncate: cannot open `%s' for writing:", argv[i]);
			ret = 1;
		}
		close(fd);
	}
	return ret;
}
