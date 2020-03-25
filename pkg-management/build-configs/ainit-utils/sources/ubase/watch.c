/* See LICENSE file for copyright and license details. */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s [-t] [-n interval] command\n", argv0);
}

int
main(int argc, char *argv[])
{
	char cmd[BUFSIZ];
	char *end;
	useconds_t interval = 2 * 1E6;
	float period;
	int i;

	ARGBEGIN {
	case 't':
		break;
	case 'n':
		period = strtof(EARGF(usage()), &end);
		if (*end != '\0' || errno != 0)
			eprintf("invalid interval\n");
		if (period < 0)
			period = 0.1f;
		interval = period * 1E6;
		break;
	default:
		usage();
	} ARGEND;

	if (argc < 1)
		usage();

	if (strlcpy(cmd, argv[0], sizeof(cmd)) >= sizeof(cmd))
		eprintf("command too long\n");
	for (i = 1; i < argc; i++) {
		if (strlcat(cmd, " ", sizeof(cmd)) >= sizeof(cmd))
			eprintf("command too long\n");
		if (strlcat(cmd, argv[i], sizeof(cmd)) >= sizeof(cmd))
			eprintf("command too long\n");
	}

	for (;;) {
		printf("\x1b[2J\x1b[H"); /* clear */
		fflush(NULL);
		system(cmd);
		usleep(interval);
	}
	return 0;
}
