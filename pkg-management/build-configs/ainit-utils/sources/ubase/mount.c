/* See LICENSE file for copyright and license details. */
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>
#include <limits.h>
#include <mntent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "text.h"
#include "util.h"

#define FSOPTS_MAXLEN 512

struct {
	const char *opt;
	const char *notopt;
	unsigned long v;
} optnames[] = {
	{ "defaults",   NULL,           0              },
	{ "remount",    NULL,           MS_REMOUNT     },
	{ "ro",         "rw",           MS_RDONLY      },
	{ "sync",       "async",        MS_SYNCHRONOUS },
	{ "dirsync",    NULL,           MS_DIRSYNC     },
	{ "nodev",      "dev",          MS_NODEV       },
	{ "noatime",    "atime",        MS_NOATIME     },
	{ "noauto",     "auto",         0              },
	{ "nodiratime", "diratime",     MS_NODIRATIME  },
	{ "noexec",     "exec",         MS_NOEXEC      },
	{ "nosuid",     "suid",         MS_NOSUID      },
	{ "mand",       "nomand",       MS_MANDLOCK    },
	{ "relatime",   "norelatime",   MS_RELATIME    },
	{ "bind",       NULL,           MS_BIND        },
	{ NULL,         NULL,           0              }
};

static unsigned long argflags = 0;
static char fsopts[FSOPTS_MAXLEN] = "";

static char *
findtype(const char *types, const char *t)
{
	const char *p;
	size_t len;

	for (len = strlen(t); (p = strstr(types, t)); types = p + len) {
		if (!strncmp(p, t, len) && (p[len] == '\0' || p[len] == ','))
			return (char *)p;
	}
	return NULL;
}

static void
parseopts(const char *popts, unsigned long *flags, char *data, size_t datasiz)
{
	unsigned int i, validopt;
	size_t optlen, dlen = 0;
	const char *name, *e;

	name = popts;
	data[0] = '\0';
	do {
		if ((e = strstr(name, ",")))
			optlen = e - name;
		else
			optlen = strlen(name);

		validopt = 0;
		for (i = 0; optnames[i].opt; i++) {
			if (optnames[i].opt &&
			    !strncmp(name, optnames[i].opt, optlen)) {
				*flags |= optnames[i].v;
				validopt = 1;
				break;
			}
			if (optnames[i].notopt &&
			    !strncmp(name, optnames[i].notopt, optlen)) {
				*flags &= ~optnames[i].v;
				validopt = 1;
				break;
			}
		}

		if (!validopt && optlen > 0) {
			/* unknown option, pass as data option to mount() */
			if (dlen + optlen + 2 >= datasiz)
				return; /* prevent overflow */
			if (dlen)
				data[dlen++] = ',';
			memcpy(&data[dlen], name, optlen);
			dlen += optlen;
			data[dlen] = '\0';
		}
		name = e + 1;
	} while (e);
}

static int
mounthelper(const char *fsname, const char *dir, const char *fstype)
{
	pid_t pid;
	char eprog[PATH_MAX];
	char const *eargv[10];
	int status, i;

	pid = fork();
	switch(pid) {
	case -1:
		break;
	case 0:
		snprintf(eprog, sizeof(eprog), "mount.%s", fstype);

		i = 0;
		eargv[i++] = eprog;
		if (argflags & MS_BIND)
			eargv[i++] = "-B";
		if (argflags & MS_MOVE)
			eargv[i++] = "-M";
		if (argflags & MS_REC)
			eargv[i++] = "-R";

		if (fsopts[0]) {
			eargv[i++] = "-o";
			eargv[i++] = fsopts;
		}
		eargv[i++] = fsname;
		eargv[i++] = dir;
		eargv[i] = NULL;

		execvp(eprog, (char * const *)eargv);
		if (errno == ENOENT)
			_exit(1);
		weprintf("execvp:");
		_exit(1);
		break;
	default:
		if (waitpid(pid, &status, 0) < 0) {
			weprintf("waitpid:");
			return -1;
		}
		if (WIFEXITED(status))
			return WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			return 1;
		break;
	}
	return 0;
}

static int
mounted(const char *dir)
{
	FILE *fp;
	struct mntent *me, mebuf;
	struct stat st1, st2;
	char linebuf[256];

	if (stat(dir, &st1) < 0) {
		weprintf("stat %s:", dir);
		return 0;
	}
	if (!(fp = setmntent("/proc/mounts", "r")))
		eprintf("setmntent %s:", "/proc/mounts");

	while ((me = getmntent_r(fp, &mebuf, linebuf, sizeof(linebuf)))) {
		if (stat(me->mnt_dir, &st2) < 0) {
			weprintf("stat %s:", me->mnt_dir);
			continue;
		}
		if (st1.st_dev == st2.st_dev &&
		    st1.st_ino == st2.st_ino)
			return 1;
	}
	endmntent(fp);

	return 0;
}

static void
usage(void)
{
	eprintf("usage: %s [-BMRan] [-t fstype] [-o options] [source] [target]\n",
	        argv0);
}

int
main(int argc, char *argv[])
{
	char *types = NULL, data[FSOPTS_MAXLEN] = "", *resolvpath = NULL;
	char *files[] = { "/proc/mounts", "/etc/fstab", NULL };
	const char *source, *target;
	struct mntent *me = NULL;
	int aflag = 0, status = 0, i, r;
	unsigned long flags = 0;
	FILE *fp;

	ARGBEGIN {
	case 'B':
		argflags |= MS_BIND;
		break;
	case 'M':
		argflags |= MS_MOVE;
		break;
	case 'R':
		argflags |= MS_REC;
		break;
	case 'a':
		aflag = 1;
		break;
	case 'o':
		estrlcat(fsopts, EARGF(usage()), sizeof(fsopts));
		parseopts(fsopts, &flags, data, sizeof(data));
		break;
	case 't':
		types = EARGF(usage());
		break;
	case 'n':
		break;
	default:
		usage();
	} ARGEND;

	if (argc < 1 && aflag == 0) {
		if (!(fp = fopen(files[0], "r")))
			eprintf("fopen %s:", files[0]);
		concat(fp, files[0], stdout, "<stdout>");
		fclose(fp);
		return 0;
	}

	if (aflag == 1)
		goto mountall;

	source = argv[0];
	target = argv[1];

	if (!target) {
		target = argv[0];
		source = NULL;
		if (strcmp(target, "/") != 0) {
			if (!(resolvpath = realpath(target, NULL)))
				eprintf("realpath %s:", target);
			target = resolvpath;
		}
	}

	for (i = 0; files[i]; i++) {
		if (!(fp = setmntent(files[i], "r"))) {
			if (strcmp(files[i], "/proc/mounts") != 0)
				weprintf("setmntent %s:", files[i]);
			continue;
		}
		while ((me = getmntent(fp))) {
			if (strcmp(me->mnt_dir, target) == 0 ||
			   strcmp(me->mnt_fsname, target) == 0 ||
			   (source && strcmp(me->mnt_dir, source) == 0) ||
			   (source && strcmp(me->mnt_fsname, source) == 0)) {
				if (!source) {
					target = me->mnt_dir;
					source = me->mnt_fsname;
				}
				if (!fsopts[0])
					estrlcat(fsopts, me->mnt_opts, sizeof(fsopts));
					parseopts(fsopts, &flags, data, sizeof(data));
				if (!types)
					types = me->mnt_type;
				goto mountsingle;
			}
		}
		endmntent(fp);
		fp = NULL;
	}
	if (!source)
		eprintf("can't find %s in /etc/fstab\n", target);

mountsingle:
	r = mounthelper(source, target, types);
	if (r == -1)
		status = 1;
	if (r > 0 && mount(source, target, types, argflags | flags, data) < 0) {
		weprintf("mount: %s:", source);
		status = 1;
	}
	if (fp)
		endmntent(fp);
	free(resolvpath);
	return status;

mountall:
	if (!(fp = setmntent("/etc/fstab", "r")))
		eprintf("setmntent %s:", "/etc/fstab");
	while ((me = getmntent(fp))) {
		/* has "noauto" option or already mounted: skip */
		if (hasmntopt(me, MNTOPT_NOAUTO) || mounted(me->mnt_dir))
			continue;
		flags = 0;
		fsopts[0] = '\0';
		if (strlcat(fsopts, me->mnt_opts, sizeof(fsopts)) >= sizeof(fsopts)) {
			weprintf("%s: option string too long\n", me->mnt_dir);
			status = 1;
			continue;
		}
		parseopts(fsopts, &flags, data, sizeof(data));
		/* if -t types specified:
		 * if non-match, skip
		 * if match and prefixed with "no", skip */
		if (types &&
		    ((types[0] == 'n' && types[1] == 'o' &&
		     findtype(types + 2, me->mnt_type)) ||
		     (!findtype(types, me->mnt_type))))
			continue;

		r = mounthelper(me->mnt_fsname, me->mnt_dir, me->mnt_type);
		if (r > 0 && mount(me->mnt_fsname, me->mnt_dir, me->mnt_type,
		                   argflags | flags, data) < 0) {
			weprintf("mount: %s:", me->mnt_fsname);
			status = 1;
		}
	}
	endmntent(fp);

	return status;
}
