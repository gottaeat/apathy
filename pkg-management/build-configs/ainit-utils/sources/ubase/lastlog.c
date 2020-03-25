/* See LICENSE file for copyright and license details. */
#include <errno.h>
#include <paths.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <utmp.h>

#include "text.h"
#include "util.h"

#define PASSWD   "/etc/passwd"

static FILE *last;

static void
lastlog(char *user)
{
	struct passwd *pwd;
	struct lastlog ll;
	time_t lltime;

	errno = 0;
	if ((pwd = getpwnam(user)) == NULL) {
		if (errno)
			weprintf("getpwnam %s:", user);
		else
			weprintf("unknown user: %s\n", user);
		return;
	}

	fseek(last, pwd->pw_uid * sizeof(struct lastlog), 0);
	fread(&ll, sizeof(struct lastlog), 1, last);

	if (ferror(last))
		eprintf("%s: read error:", _PATH_LASTLOG);

	/* on glibc `ll_time' can be an int32_t with compat32
	 * avoid compiler warning when calling ctime() */
	lltime = ll.ll_time;
	printf("%-8.8s %-8.8s %-16.16s %s",
	       user, ll.ll_line, ll.ll_host, ctime(&lltime));
}

int
main(int argc, char **argv)
{
	FILE *fp;
	char *line = NULL, *p;
	size_t sz = 0;

	if ((last = fopen(_PATH_LASTLOG, "r")) == NULL)
		eprintf("fopen %s:", _PATH_LASTLOG);

	if (argc > 1) {
		while (*++argv)
			lastlog(*argv);
	} else {
		if ((fp = fopen(PASSWD, "r")) == NULL)
			eprintf("fopen %s:", PASSWD);
		while (agetline(&line, &sz, fp) != -1) {
			if ((p = strchr(line, ':')) == NULL)
				eprintf("invalid passwd entry\n");
			*p = '\0';
			lastlog(line);
		}
		if (fclose(fp))
			eprintf("fclose %s:", PASSWD);
		free(line);
	}

	if (fclose(last))
		eprintf("fclose %s:", _PATH_LASTLOG);

	return 0;
}
