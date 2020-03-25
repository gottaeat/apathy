/* See LICENSE file for copyright and license details. */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "text.h"
#include "util.h"

static void
lsusb(const char *file)
{
	FILE *fp;
	char path[PATH_MAX];
	char *buf = NULL;
	size_t size = 0;
	unsigned int i = 0, busnum = 0, devnum = 0, pid = 0, vid = 0;

	if (strlcpy(path, file, sizeof(path)) >= sizeof(path))
		eprintf("path too long\n");
	if (strlcat(path, "/uevent", sizeof(path)) >= sizeof(path))
		eprintf("path too long\n");

	if (!(fp = fopen(path, "r")))
		return;
	while (agetline(&buf, &size, fp) != -1) {
		if (sscanf(buf, "BUSNUM=%u\n", &busnum) ||
		    sscanf(buf, "DEVNUM=%u\n", &devnum) ||
		    sscanf(buf, "PRODUCT=%x/%x/", &pid, &vid))
			i++;
		if (i == 3) {
			printf("Bus %03d Device %03d: ID %04x:%04x\n", busnum, devnum,
			       pid, vid);
			break;
		}
	}
	if (ferror(fp))
		eprintf("%s: read error:", path);
	free(buf);
	fclose(fp);
}

static void
usage(void)
{
	eprintf("usage: %s\n", argv0);
}

int
main(int argc, char *argv[])
{
	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	recurse("/sys/bus/usb/devices", lsusb);
	return 0;
}
