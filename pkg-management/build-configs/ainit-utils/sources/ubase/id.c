/* See LICENSE file for copyright and license details. */
#include <sys/types.h>

#include <ctype.h>
#include <errno.h>
#include <grp.h>
#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

static void groupid(struct passwd *pw);
static void user(struct passwd *pw);
static void userid(uid_t id);
static void usernam(const char *nam);

static int gflag = 0;
static int uflag = 0;
static int Gflag = 0;
static int nflag = 0;

static void
groupid(struct passwd *pw)
{
	gid_t gid, groups[NGROUPS_MAX];
	struct group *gr;
	int ngroups;
	int i;

	ngroups = NGROUPS_MAX;
	getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups);
	for (i = 0; i < ngroups; i++) {
		gid = groups[i];
		if (nflag) {
			if (!(gr = getgrgid(gid)))
				eprintf("getgrgid:");
			printf("%s", gr->gr_name);
		} else
			printf("%u", gid);

		if (i < ngroups - 1)
			putchar(' ');
	}
	putchar('\n');
}

static void
user(struct passwd *pw)
{
	struct group *gr;
	gid_t gid, groups[NGROUPS_MAX];
	int ngroups;
	int i;

	if (uflag) {
		if (nflag)
			printf("%s\n", pw->pw_name);
		else
			printf("%u\n", pw->pw_uid);
		return;
	} else if (gflag) {
		if (nflag) {
			if (!(gr = getgrgid(pw->pw_gid)))
				eprintf("getgrgid:");
			printf("%s\n", gr->gr_name);
		} else
			printf("%u\n", pw->pw_gid);
		return;
	}

	printf("uid=%u(%s)", pw->pw_uid, pw->pw_name);
	printf(" gid=%u", pw->pw_gid);
	if (!(gr = getgrgid(pw->pw_gid)))
		eprintf("getgrgid:");
	printf("(%s)", gr->gr_name);

	ngroups = NGROUPS_MAX;
	getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups);
	for (i = 0; i < ngroups; i++) {
		gid = groups[i];
		printf("%s%u", !i ? " groups=" : ",", gid);
		if (!(gr = getgrgid(gid)))
			eprintf("getgrgid:");
		printf("(%s)", gr->gr_name);
	}
	putchar('\n');
}

static void
usernam(const char *nam)
{
	struct passwd *pw;

	errno = 0;
	pw = getpwnam(nam);
	if (!pw) {
		if (errno)
			eprintf("getpwnam %s:", nam);
		else
			eprintf("getpwnam %s: no such user\n", nam);
	}
	if (Gflag)
		groupid(pw);
	else
		user(pw);
}

static void
userid(uid_t id)
{
	struct passwd *pw;

	errno = 0;
	pw = getpwuid(id);
	if (!pw) {
		if (errno)
			eprintf("getpwuid %d:", id);
		else
			eprintf("getpwuid %d: no such user\n", id);
	}
	if (Gflag)
		groupid(pw);
	else
		user(pw);
}

static void
usage(void)
{
	eprintf("usage: %s [-n] [-g | -u | -G] [user | uid]\n", argv0);
}

int
main(int argc, char *argv[])
{
	ARGBEGIN {
	case 'g':
		gflag = 1;
		break;
	case 'u':
		uflag = 1;
		break;
	case 'G':
		Gflag = 1;
		break;
	case 'n':
		nflag = 1;
		break;
	default:
		usage();
	} ARGEND;

	/* ensure that only one of -g, -u, or -G was specified */
	if (gflag + uflag + Gflag > 1)
		usage();

	switch (argc) {
	case 0:
		userid(getuid());
		break;
	case 1:
		/* user names can't begin [0-9] */
		if (isdigit(argv[0][0]))
			userid(estrtol(argv[0], 0));
		else
			usernam(argv[0]);
		break;
	default:
		usage();
	}

	return 0;
}
