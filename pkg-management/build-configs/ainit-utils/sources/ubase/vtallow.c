/* See LICENSE file for copyright and license details. */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

#define CONSOLE "/dev/console"

#define VT_LOCKSWITCH   0x560B  /* disallow vt switching */
#define VT_UNLOCKSWITCH 0x560C  /* allow vt switching */

static void
usage(void)
{
	eprintf("usage: %s n | y\n", argv0);
}

int
main(int argc, char *argv[])
{
	int fd;
	int allow;

	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	if (argc != 1)
		usage();

	if (!strcmp(argv[0], "y"))
		allow = 1;
	else if (!strcmp(argv[0], "n"))
		allow = 0;
	else
		usage();

	if ((fd = open(CONSOLE, O_WRONLY)) < 0)
		eprintf("open %s:", CONSOLE);
	if (ioctl(fd, allow ? VT_UNLOCKSWITCH : VT_LOCKSWITCH) < 0)
		eprintf("cannot %s VT switch:",
			allow ? "unlock" : "lock");
	close(fd);
	return 0;
}
