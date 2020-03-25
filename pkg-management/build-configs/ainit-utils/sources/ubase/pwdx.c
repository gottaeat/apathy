/* See LICENSE file for copyright and license details. */
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s pid...\n", argv0);
}

int
main(int argc, char *argv[])
{
	int ret = 0;
	char path[PATH_MAX];
	char target[PATH_MAX + sizeof(" (deleted)")];
	ssize_t n;

	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	if (argc == 0)
		usage();

	for (; argc > 0; argc--, argv++) {
		n = snprintf(path, sizeof(path), "/proc/%s/cwd", *argv);
		if (n < 0 || n >= sizeof(path)) {
			errno = ESRCH;
		} else {
			n = readlink(path, target, sizeof(target) - 1);
			if (n >= 0) {
				target[n] = '\0';
				printf("%s: %s\n", *argv, target);
				continue;
			}
		}
		if (errno == ENOENT)
			errno = ESRCH;
		weprintf("%s:", *argv);
		ret = 1;
	}

	return ret;
}
