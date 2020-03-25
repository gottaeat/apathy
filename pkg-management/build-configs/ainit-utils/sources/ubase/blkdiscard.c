/* See LICENSE file for copyright and license details. */
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

#include "util.h"

#define OFFSET_IDX	0
#define LENGTH_IDX	1

#define BLKDISCARD	_IO(0x12, 119)

static void
usage(void)
{
	eprintf("usage: %s device\n", argv0);
}

int
main(int argc, char *argv[])
{
	uint64_t range[2];
	int fd;

	ARGBEGIN {
	default:
		usage();
	} ARGEND

	if (argc != 1)
		usage();

	fd = open(argv[0], O_RDWR);
	if (fd < 0)
		eprintf("open: %s:", argv[0]);
	range[OFFSET_IDX] = 0;
	if (ioctl(fd, BLKGETSIZE64, &range[LENGTH_IDX]) < 0)
		eprintf("BLKGETSIZE64: %s:", argv[0]);
	if (ioctl(fd, BLKDISCARD, range) < 0)
		eprintf("BLKDISCARD: %s:", argv[0]);
	close(fd);
	return 0;
}
