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

#include "passwd.h"
#include "util.h"

#define ENV_SUPATH "/mss/init/bin"
#define ENV_PATH   "/mss/init/bin"
#define PW_CIPHER  "$6$"

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

	if (initgroups(user, gid) < 0)
		eprintf("initgroups:");
	if (setgid(gid) < 0)
		eprintf("setgid:");
	if (setuid(uid) < 0)
		eprintf("setuid:");

	return dologin(pw, pflag);
}
