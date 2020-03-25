/* See LICENSE file for copyright and license details. */
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s [-muinpU] cmd [args...]\n", argv0);
}

int
main(int argc, char *argv[])
{
	int flags = 0;

	ARGBEGIN {
	case 'm':
		flags |= CLONE_NEWNS;
		break;
	case 'u':
		flags |= CLONE_NEWUTS;
		break;
	case 'i':
		flags |= CLONE_NEWIPC;
		break;
	case 'n':
		flags |= CLONE_NEWNET;
		break;
	case 'p':
		flags |= CLONE_NEWPID;
		break;
	case 'U':
		flags |= CLONE_NEWUSER;
		break;
	default:
		usage();
	} ARGEND;

	if (argc < 1)
		usage();

	if (unshare(flags) < 0)
		eprintf("unshare:");

	if (execvp(argv[0], argv) < 0)
		eprintf("execvp:");

	return 0;
}
