/* See LICENSE file for copyright and license details. */
#include <sys/resource.h>
#include <sys/time.h>

#include <errno.h>
#include <pwd.h>
#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../passwd.h"
#include "../text.h"
#include "../util.h"

/* Returns -1 on error, 0 for incorrect password
 * and 1 if all went OK */
int
pw_check(const struct passwd *pw, const char *pass)
{
	char *cryptpass, *p;
	struct spwd *spw;

	p = pw->pw_passwd;
	if (p[0] == '!' || p[0] == '*') {
		weprintf("denied\n");
		return -1;
	}

	if (pw->pw_passwd[0] == '\0') {
		if (pass[0] == '\0')
			return 1;
		weprintf("incorrect password\n");
		return 0;
	}

	if (pw->pw_passwd[0] == 'x' && pw->pw_passwd[1] == '\0') {
		errno = 0;
		spw = getspnam(pw->pw_name);
		if (!spw) {
			if (errno)
				weprintf("getspnam: %s:", pw->pw_name);
			else
				weprintf("who are you?\n");
			return -1;
		}
		p = spw->sp_pwdp;
		if (p[0] == '!' || p[0] == '*') {
			weprintf("denied\n");
			return -1;
		}
	}

	cryptpass = crypt(pass, p);
	if (!cryptpass) {
		weprintf("crypt:");
		return -1;
	}
	if (strcmp(cryptpass, p) != 0) {
		weprintf("incorrect password\n");
		return 0;
	}
	return 1;
}

int
pw_init(void)
{
	struct rlimit rlim;

	rlim.rlim_cur = 0;
	rlim.rlim_max = 0;
	if (setrlimit(RLIMIT_CORE, &rlim) < 0)
		eprintf("setrlimit:");
	return 0;
}
