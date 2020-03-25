/* See LICENSE file for copyright and license details. */
#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

#define SWAP_UUID_LENGTH 16
#define SWAP_LABEL_LENGTH 16
#define SWAP_MIN_PAGES 10

struct swap_hdr {
	char	      bootbits[1024];
	unsigned int  version;
	unsigned int  last_page;
	unsigned int  nr_badpages;
	unsigned char uuid[SWAP_UUID_LENGTH];
	char	      volume_name[SWAP_LABEL_LENGTH];
	unsigned int  padding[117];
	unsigned int  badpages[1];
};

static void
usage(void)
{
	eprintf("usage: %s device\n", argv0);
}

int
main(int argc, char *argv[])
{
	int fd;
	unsigned int pages;
	long pagesize;
	struct stat sb;
	char *buf;
	struct swap_hdr *hdr;

	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	if (argc < 1)
		usage();

	pagesize = sysconf(_SC_PAGESIZE);
	if (pagesize <= 0) {
		pagesize = sysconf(_SC_PAGE_SIZE);
		if (pagesize <= 0)
			eprintf("can't determine pagesize\n");
	}

	fd = open(argv[0], O_RDWR);
	if (fd < 0)
		eprintf("open %s:", argv[0]);
	if (fstat(fd, &sb) < 0)
		eprintf("stat %s:", argv[0]);

	buf = ecalloc(1, pagesize);

	pages = sb.st_size / pagesize;
	if (pages < SWAP_MIN_PAGES)
		eprintf("swap space needs to be at least %ldKiB\n",
			SWAP_MIN_PAGES * pagesize / 1024);

	/* Fill up the swap header */
	hdr = (struct swap_hdr *)buf;
	hdr->version = 1;
	hdr->last_page = pages - 1;
	strncpy(buf + pagesize - 10, "SWAPSPACE2", 10);

	printf("Setting up swapspace version 1, size = %luKiB\n",
	       (pages - 1) * pagesize / 1024);

	/* Write out the signature page */
	if (write(fd, buf, pagesize) != pagesize)
		eprintf("unable to write signature page\n");

	fsync(fd);
	close(fd);
	free(buf);

	return 0;
}
