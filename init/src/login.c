/* See LICENSE file for copyright and license details. */
#include <sys/ioctl.h>
#include <sys/types.h>

#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <utmp.h>

#include "config.h"
#include "passwd.h"
#include "util.h"

/* Write utmp entry */
static void
writeutmp(const char *user, const char *tty)
{
	struct utmp usr;
	FILE *fp;

	memset(&usr, 0, sizeof(usr));

	usr.ut_type = USER_PROCESS;
	usr.ut_pid = getpid();
	strlcpy(usr.ut_user, user, sizeof(usr.ut_user));
	strlcpy(usr.ut_line, tty, sizeof(usr.ut_line));
	usr.ut_tv.tv_sec = time(NULL);

	fp = fopen(UTMP_PATH, "a");
	if (fp) {
		if (fwrite(&usr, sizeof(usr), 1, fp) != 1)
			if (ferror(fp))
				weprintf("%s: write error:", UTMP_PATH);
		fclose(fp);
	} else {
		weprintf("fopen %s:", UTMP_PATH);
	}
}

static int
dologin(struct passwd *pw, int preserve)
{
	char *shell = pw->pw_shell[0] == '\0' ? "/bin/sh" : pw->pw_shell;

	if (preserve == 0)
		clearenv();
	setenv("HOME", pw->pw_dir, 1);
	setenv("SHELL", shell, 1);
	setenv("USER", pw->pw_name, 1);
	setenv("LOGNAME", pw->pw_name, 1);
	setenv("PATH", ENV_PATH, 1);
	if (chdir(pw->pw_dir) < 0)
		eprintf("chdir %s:", pw->pw_dir);
	execlp(shell, shell, "-l", NULL);
	weprintf("execlp %s:", shell);
	return (errno == ENOENT) ? 127 : 126;
}

static void
usage(void)
{
	eprintf("usage: %s [-p] username\n", argv0);
}

int
main(int argc, char *argv[])
{
	struct passwd *pw;
	char *pass, *user;
	char *tty;
	uid_t uid;
	gid_t gid;
	int pflag = 0;

	ARGBEGIN {
	case 'p':
		pflag = 1;
		break;
	default:
		usage();
	} ARGEND;

	if (argc < 1)
		usage();

	if (isatty(0) == 0 || isatty(1) == 0 || isatty(2) == 0)
		eprintf("no tty");

	user = argv[0];
	errno = 0;
	pw = getpwnam(user);
	if (!pw) {
		if (errno)
			eprintf("getpwnam %s:", user);
		else
			eprintf("who are you?\n");
	}

	uid = pw->pw_uid;
	gid = pw->pw_gid;

	/* Flush pending input */
	ioctl(0, TCFLSH, (void *)0);

	pass = getpass("Password: ");
	if (!pass)
		eprintf("getpass:");
	if (pw_check(pw, pass) <= 0)
		exit(1);

	tty = ttyname(0);
	if (!tty)
		eprintf("ttyname:");

	writeutmp(user, tty);

	if (initgroups(user, gid) < 0)
		eprintf("initgroups:");
	if (setgid(gid) < 0)
		eprintf("setgid:");
	if (setuid(uid) < 0)
		eprintf("setuid:");

	return dologin(pw, pflag);
}
