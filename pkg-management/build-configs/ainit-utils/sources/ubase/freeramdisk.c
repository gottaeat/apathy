/* See LICENSE file for copyright and license details. */
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <sys/types.h>

#include <fcntl.h>
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
	char *dev = "/dev/ram";
	int fd;

	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	if (argc != 0)
		usage();

	if ((fd = open(dev, O_RDWR)) < 0)
		eprintf("open: %s:", dev);
	if (ioctl(fd, BLKFLSBUF, dev) < 0)
		eprintf("BLKFLSBUF %s:", dev);
	close(fd);
	return 0;
}
