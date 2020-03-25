/* See LICENSE file for copyright and license details. */
#include <sys/types.h>

#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "passwd.h"
#include "util.h"

extern char **environ;

static int lflag = 0;
static int pflag = 0;

static int
dologin(struct passwd *pw)
{
	char *shell = pw->pw_shell[0] == '\0' ? "/bin/sh" : pw->pw_shell;
	char *term = getenv("TERM");
	clearenv();
	setenv("HOME", pw->pw_dir, 1);
	setenv("SHELL", shell, 1);
	setenv("USER", pw->pw_name, 1);
	setenv("LOGNAME", pw->pw_name, 1);
	setenv("TERM", term ? term : "linux", 1);
	if (strcmp(pw->pw_name, "root") == 0)
		setenv("PATH", ENV_SUPATH, 1);
	else
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
	eprintf("usage: %s [-lp] [username]\n", argv0);
}

int
main(int argc, char *argv[])
{
	char *usr = "root", *pass;
	char *shell;
	struct passwd *pw;
	char *newargv[2];
	uid_t uid;

	ARGBEGIN {
	case 'l':
		lflag = 1;
		break;
	case 'p':
		pflag = 1;
		break;
	default:
		usage();
	} ARGEND;

	if (argc < 1)
		;
	else if (argc == 1)
		usr = argv[0];
	else
		usage();

	errno = 0;
	pw = getpwnam(usr);
	if (!pw) {
		if (errno)
			eprintf("getpwnam: %s:", usr);
		else
			eprintf("who are you?\n");
	}

	uid = getuid();
	if (uid) {
		pass = getpass("Password: ");
		if (!pass)
			eprintf("getpass:");
		if (pw_check(pw, pass) <= 0)
			exit(1);
	}

	if (initgroups(usr, pw->pw_gid) < 0)
		eprintf("initgroups:");
	if (setgid(pw->pw_gid) < 0)
		eprintf("setgid:");
	if (setuid(pw->pw_uid) < 0)
		eprintf("setuid:");

	if (lflag) {
		return dologin(pw);
	} else {
		shell = pw->pw_shell[0] == '\0' ? "/bin/sh" : pw->pw_shell;
		newargv[0] = shell;
		newargv[1] = NULL;
		if (!pflag) {
			setenv("HOME", pw->pw_dir, 1);
			setenv("SHELL", shell, 1);
			if (strcmp(pw->pw_name, "root") != 0) {
				setenv("USER", pw->pw_name, 1);
				setenv("LOGNAME", pw->pw_name, 1);
			}
		}
		if (strcmp(pw->pw_name, "root") == 0)
			setenv("PATH", ENV_SUPATH, 1);
		else
			setenv("PATH", ENV_PATH, 1);
		execve(pflag ? getenv("SHELL") : shell,
		       newargv, environ);
		weprintf("execve %s:", shell);
		return (errno == ENOENT) ? 127 : 126;
	}
	return 0;
}