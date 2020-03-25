/* See LICENSE file for copyright and license details. */
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

#define FIFREEZE	_IOWR('X', 119, int)	/* Freeze */
#define FITHAW		_IOWR('X', 120, int)	/* Thaw */

static void
usage(void)
{
	eprintf("usage: %s (-f | -u) mountpoint\n", argv0);
}

int
main(int argc, char *argv[])
{
	int fflag = 0;
	int uflag = 0;
	long p = 1;
	int fd;

	ARGBEGIN {
	case 'f':
		fflag = 1;
		break;
	case 'u':
		uflag = 1;
		break;
	default:
		usage();
	} ARGEND;

	if (argc != 1)
		usage();

	if ((fflag ^ uflag) == 0)
		usage();

	fd = open(argv[0], O_RDONLY);
	if (fd < 0)
		eprintf("open: %s:", argv[0]);
	if (ioctl(fd, fflag == 1 ? FIFREEZE : FITHAW, &p) < 0)
		eprintf("%s %s:", fflag == 1 ? "FIFREEZE" : "FITHAW", argv[0]);
	close(fd);
	return 0;
}
