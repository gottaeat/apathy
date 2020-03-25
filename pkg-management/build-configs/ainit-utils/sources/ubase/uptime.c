/* See LICENSE file for copyright and license details. */
#include <sys/sysinfo.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <utmpx.h>

#include "config.h"
#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s\n", argv0);
}

int
main(int argc, char *argv[])
{
	struct utmpx utx;
	FILE *ufp;
	struct sysinfo info;
	time_t tmptime;
	struct tm *now;
	unsigned int days, hours, minutes;
	int nusers = 0;
	size_t n;

	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	if (sysinfo(&info) < 0)
		eprintf("sysinfo:");
	time(&tmptime);
	now = localtime(&tmptime);
	printf(" %02d:%02d:%02d up ", now->tm_hour, now->tm_min, now->tm_sec);
	info.uptime /= 60;
	minutes = info.uptime % 60;
	info.uptime /= 60;
	hours = info.uptime % 24;
	days = info.uptime / 24;
	if (days)
		printf("%d day%s, ", days, days != 1 ? "s" : "");
	if (hours)
		printf("%2d:%02d, ", hours, minutes);
	else
		printf("%d min, ", minutes);

	if ((ufp = fopen(UTMP_PATH, "r"))) {
		while ((n = fread(&utx, sizeof(utx), 1, ufp)) > 0) {
			if (!utx.ut_user[0])
				continue;
			if (utx.ut_type != USER_PROCESS)
				continue;
			nusers++;
		}
		if (ferror(ufp))
			eprintf("%s: read error:", UTMP_PATH);
		fclose(ufp);
		printf(" %d user%s, ", nusers, nusers != 1 ? "s" : "");
	}

	printf(" load average: %.02f, %.02f, %.02f\n",
	       info.loads[0] / 65536.0f,
	       info.loads[1] / 65536.0f,
	       info.loads[2] / 65536.0f);

	return 0;
}
