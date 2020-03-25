/* See LICENSE file for copyright and license details. */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>

#include <fcntl.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../util.h"

void
devtotty(int dev, int *tty_maj, int *tty_min)
{
	*tty_maj = (dev >> 8) & 0xfff;
	*tty_min = (dev & 0xff) | ((dev >> 12) & 0xfff00);
}

int
ttytostr(int tty_maj, int tty_min, char *str, size_t n)
{
	struct stat sb;
	struct dirent *dp;
	DIR *dirp;
	char path[PATH_MAX];
	int fd;
	int r = 0;

	switch (tty_maj) {
	case 136:
		snprintf(str, n, "pts/%d", tty_min);
		return 0;
	case 4:
		snprintf(str, n, "tty%d", tty_min);
		return 0;
	default:
		str[0] = '?';
		str[1] = '\0';
		break;
	}

	dirp = opendir("/dev");
	if (!dirp) {
		weprintf("opendir /dev:");
		return -1;
	}

	while ((dp = readdir(dirp))) {
		if (!strcmp(dp->d_name, ".") ||
		    !strcmp(dp->d_name, ".."))
			continue;

		if (strlcpy(path, "/dev/", sizeof(path)) >= sizeof(path)) {
			weprintf("path too long\n");
			r = -1;
			goto err0;
		}
		if (strlcat(path, dp->d_name, sizeof(path)) >= sizeof(path)) {
			weprintf("path too long\n");
			r = -1;
			goto err0;
		}

		if (stat(path, &sb) < 0) {
			weprintf("stat %s:", path);
			r = -1;
			goto err0;
		}

		if ((int)major(sb.st_rdev) == tty_maj &&
		    (int)minor(sb.st_rdev) == tty_min) {
			fd = open(path, O_RDONLY | O_NONBLOCK);
			if (fd < 0)
				continue;
			if (isatty(fd)) {
				strlcpy(str, dp->d_name, n);
				close(fd);
				break;
			} else {
				close(fd);
				r = -1;
				goto err0;
			}
		}
	}

err0:
	if (closedir(dirp) < 0) {
		weprintf("closedir /dev:");
		r = -1;
	}

	return r;
}
