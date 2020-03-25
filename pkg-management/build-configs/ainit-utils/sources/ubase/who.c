/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <utmp.h>

#include "config.h"
#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s [-ml]\n", argv0);
}

int
main(int argc, char *argv[])
{
	struct utmp usr;
	FILE *ufp;
	char timebuf[sizeof "yyyy-mm-dd hh:mm"];
	char *tty, *ttmp;
	int mflag = 0, lflag = 0;
	time_t t;

	ARGBEGIN {
	case 'm':
		mflag = 1;
		tty = ttyname(0);
		if (!tty)
			eprintf("ttyname: stdin:");
		if ((ttmp = strrchr(tty, '/')))
			tty = ttmp+1;
		break;
	case 'l':
		lflag = 1;
		break;
	default:
		usage();
	} ARGEND;

	if (argc > 0)
		usage();

	if (!(ufp = fopen(UTMP_PATH, "r")))
		eprintf("fopen: %s:", UTMP_PATH);

	while (fread(&usr, sizeof(usr), 1, ufp) == 1) {
		if (!*usr.ut_name || !*usr.ut_line ||
		    usr.ut_line[0] == '~')
			continue;
		if (mflag != 0 && strcmp(usr.ut_line, tty) != 0)
			continue;
		if (!!strcmp(usr.ut_name, "LOGIN") == lflag)
			continue;
		t = usr.ut_time;
		strftime(timebuf, sizeof timebuf, "%Y-%m-%d %H:%M", localtime(&t));
		printf("%-8s %-12s %-16s\n", usr.ut_name, usr.ut_line, timebuf);
	}
	fclose(ufp);
	return 0;
}
