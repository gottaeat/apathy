/* See LICENSE file for copyright and license details. */
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "util.h"

enum {
	OPEN_TRAY = 0x5309,
	CLOSE_TRAY = 0x5319,
};

static int tflag = 0;
static int ret = 0;

static void
eject(const char *devname)
{
	int fd, out;

	if ((fd = open(devname, O_RDONLY | O_NONBLOCK)) < 0) {
		weprintf("open %s:", devname);
		ret = 1;
	} else if (tflag && ioctl(fd, CLOSE_TRAY, &out) < 0) {
		weprintf("ioctl %s:", devname);
		ret = 1;
	} else if (!tflag && ioctl(fd, OPEN_TRAY, &out) < 0) {
		weprintf("ioctl %s:", devname);
		ret = 1;
	}

	if (fd >= 0 && close(fd) < 0) {
		weprintf("close %s:", devname);
		ret = 1;
	}
}


static void
usage(void)
{
	eprintf("usage: %s [-t] [device ...]\n", argv0);
}

int
main(int argc, char *argv[])
{
	ARGBEGIN {
	case 't':
		tflag = 1;
		break;
	default:
		usage();
	} ARGEND;

	if (!argc) {
		eject("/dev/sr0");
	} else {
		for (; *argv; argc--, argv++)
			eject(*argv);
	}

	return ret;
}
