/* See LICENSE file for copyright and license details. */
#include <sys/types.h>

#include <dirent.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "proc.h"
#include "queue.h"
#include "util.h"

struct pidentry {
	pid_t pid;
	SLIST_ENTRY(pidentry) entry;
};

static SLIST_HEAD(, pidentry) omitpid_head;

static void
usage(void)
{
	eprintf("usage: %s [-o pid1,pid2,...pidN] [-s] [program...]\n", argv0);
}

int
main(int argc, char *argv[])
{
	DIR *dp;
	struct dirent *entry;
	pid_t pid;
	struct procstat ps;
	char cmdline[BUFSIZ], *cmd, *cmdbase = NULL, *p, *arg = NULL;
	int i, found = 0;
	int sflag = 0, oflag = 0;
	struct pidentry *pe;

	ARGBEGIN {
	case 's':
		sflag = 1;
		break;
	case 'o':
		oflag = 1;
		arg = EARGF(usage());
		break;
	default:
		usage();
	} ARGEND;

	if (!argc)
		return 1;

	SLIST_INIT(&omitpid_head);

	for (p = strtok(arg, ","); p; p = strtok(NULL, ",")) {
		pe = emalloc(sizeof(*pe));
		if (strcmp(p, "%PPID") == 0)
			pe->pid = getppid();
		else
			pe->pid = estrtol(p, 10);
		SLIST_INSERT_HEAD(&omitpid_head, pe, entry);
	}

	if (!(dp = opendir("/proc")))
		eprintf("opendir /proc:");

	while ((entry = readdir(dp))) {
		if (!pidfile(entry->d_name))
			continue;
		pid = estrtol(entry->d_name, 10);
		if (oflag) {
			SLIST_FOREACH(pe, &omitpid_head, entry)
				if (pe->pid == pid)
					break;
			if (pe)
				continue;
		}
		if (parsestat(pid, &ps) < 0)
			continue;
		if (parsecmdline(ps.pid, cmdline,
				 sizeof(cmdline)) < 0) {
			cmd = ps.comm;
			cmdbase = cmd;
		} else {
			if ((p = strchr(cmdline, ' ')))
				*p = '\0';
			cmd = cmdline;
			cmdbase = basename(cmdline);
		}
		/* Workaround for login shells */
		if (cmd[0] == '-')
			cmd++;
		for (i = 0; i < argc; i++) {
			if (strcmp(cmd, argv[i]) == 0 ||
			    strcmp(cmdbase, argv[i]) == 0) {
				putword(entry->d_name);
				found++;
				if (sflag)
					goto out;
			}
		}
	}

out:
	if (found)
		putchar('\n');

	closedir(dp);

	return 0;
}
