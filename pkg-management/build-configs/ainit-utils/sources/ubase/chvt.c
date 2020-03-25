/* See LICENSE file for copyright and license details. */
#include <sys/ioctl.h>
#include <sys/types.h>

#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

#define KDGKBTYPE	0x4B33	/* get keyboard type */

#define VT_ACTIVATE	0x5606	/* make vt active */
#define VT_WAITACTIVE	0x5607	/* wait for vt active */

static char *vt[] = {
	"/proc/self/fd/0",
	"/dev/console",
	"/dev/tty",
	"/dev/tty0",
};

static void
usage(void)
{
	eprintf("usage: %s num\n", argv0);
}

int
main(int argc, char *argv[])
{
	unsigned int n, i;
	int fd;
	char c;

	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	if (argc != 1)
		usage();

	n = estrtonum(argv[0], 0, UINT_MAX);
	for (i = 0; i < LEN(vt); i++) {
		if ((fd = open(vt[i], O_RDONLY)) < 0)
			continue;
		c = 0;
		if (ioctl(fd, KDGKBTYPE, &c) == 0)
			goto found;
		if (close(fd) < 0)
			eprintf("close %s:", vt[i]);
	}
	eprintf("no console found\n");

found:
	if (ioctl(fd, VT_ACTIVATE, n) == -1)
		eprintf("VT_ACTIVATE %u:", n);
	if (ioctl(fd, VT_WAITACTIVE, n) == -1)
		eprintf("VT_WAITACTIVE %u:", n);
	if (close(fd) < 0)
		eprintf("close %s:", vt[i]);

	return 0;
}
