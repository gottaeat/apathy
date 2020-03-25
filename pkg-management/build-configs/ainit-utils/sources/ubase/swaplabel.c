/* See LICENSE file for copyright and license details. */
#include <sys/types.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

#define SWAP_MAGIC1 "SWAPSPACE2"
#define SWAP_MAGIC2 "SWAP-SPACE"
#define SWAP_MAGIC_LENGTH (10)
#define SWAP_MAGIC_OFFSET (sysconf(_SC_PAGESIZE) - SWAP_MAGIC_LENGTH)
#define SWAP_LABEL_LENGTH (16)
#define SWAP_LABEL_OFFSET (1024 + 4 + 4 + 4 + 16)

static void
usage(void)
{
	eprintf("usage: %s [-L label] device\n", argv0);
}

int
main(int argc, char *argv[])
{
	int setlabel = 0;
	int fd;
	char magic[SWAP_MAGIC_LENGTH];
	char *label;
	char *device;
	int i;

	ARGBEGIN {
	case 'L':
		setlabel = 1;
		label = EARGF(usage());
		break;
	default:
		usage();
	} ARGEND;

	if (argc < 1)
		usage();
	device = argv[0];

	fd = open(device, O_RDWR);
	if (fd < 0)
		eprintf("open %s:", device);

	if (lseek(fd, SWAP_MAGIC_OFFSET, SEEK_SET) != SWAP_MAGIC_OFFSET)
		eprintf("failed seeking to magic position:");
	if (read(fd, magic, SWAP_MAGIC_LENGTH) != SWAP_MAGIC_LENGTH)
		eprintf("reading magic failed:");
	if (memcmp(magic, SWAP_MAGIC1, 10) && memcmp(magic, SWAP_MAGIC2, 10))
		eprintf("%s: is not a swap partition\n", device);
	if (lseek(fd, SWAP_LABEL_OFFSET, SEEK_SET) != SWAP_LABEL_OFFSET)
		eprintf("failed seeking to label position:");

	if (!setlabel) {
		label = emalloc(SWAP_LABEL_LENGTH);
		if (read(fd, label, SWAP_LABEL_LENGTH) != SWAP_LABEL_LENGTH)
			eprintf("reading label failed:");
		for (i = 0; i < SWAP_LABEL_LENGTH && label[i] != '\0'; i++)
			if (i == (SWAP_LABEL_LENGTH - 1) && label[i] != '\0')
				eprintf("invalid label\n");
		printf("label: %s\n", label);
		free(label);
	} else {
		if (strlen(label) + 1 > SWAP_LABEL_LENGTH)
			eprintf("label too long\n");
		if (write(fd, label, strlen(label) + 1) != (ssize_t)strlen(label) + 1)
			eprintf("writing label failed:");
	}

	fsync(fd);
	close(fd);
	return 0;
}
