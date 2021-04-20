/* See LICENSE file for copyright and license details. */
#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../proc.h"
#include "../util.h"

int
parsecmdline(pid_t pid, char *buf, size_t siz)
{
	int fd;
	char path[PATH_MAX];
	ssize_t n, i;

	snprintf(path, sizeof(path), "/proc/%ld/cmdline", (long)pid);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return -1;
	n = read(fd, buf, siz > 0 ? siz - 1 : 0);
	if (n < 0) {
		weprintf("read %s:", path);
		close(fd);
		return -1;
	}
	if (!n) {
		close(fd);
		return -1;
	}
	buf[n] = '\0';
	for (i = 0; i < n; i++)
		if (buf[i] == '\0')
			buf[i] = ' ';
	close(fd);
	return 0;
}

int
parsestat(pid_t pid, struct procstat *ps)
{
	char path[PATH_MAX];
	FILE *fp;
	size_t len;

	snprintf(path, sizeof(path), "/proc/%d/stat", pid);
	if (!(fp = fopen(path, "r")))
		return -1;
	fscanf(fp, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu",
	       &ps->pid, ps->comm,
	       &ps->state, &ps->ppid, &ps->pgrp,
	       &ps->sid, &ps->tty_nr, &ps->tpgid, &ps->flags,
	       &ps->minflt, &ps->cminflt, &ps->majflt, &ps->cmajflt,
	       &ps->utime, &ps->stime);
	fscanf(fp, "%ld %ld %ld %ld %ld %ld %llu %lu %ld %ld",
	       &ps->cutime, &ps->cstime, &ps->priority, &ps->nice,
	       &ps->num_threads, &ps->itrealvalue, &ps->starttime,
	       &ps->vsize, &ps->rss, &ps->rsslim);
	/* Filter out '(' and ')' from comm */
	if ((len = strlen(ps->comm)) > 0)
		len--;
	ps->comm[len] = '\0';
	memmove(ps->comm, ps->comm + 1, len);
	fclose(fp);
	return 0;
}

int
parsestatus(pid_t pid, struct procstatus *pstatus)
{
	char path[PATH_MAX];
	char buf[BUFSIZ], *off;
	int fd;
	ssize_t n;

	snprintf(path, sizeof(path), "/proc/%d/status", pid);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return -1;
	n = read(fd, buf, sizeof(buf) - 1);
	if (n < 0)
		eprintf("%s: read error:", path);
	if (!n) {
		close(fd);
		return -1;
	}
	buf[n] = '\0';
	close(fd);
	off = strstr(buf, "Uid:");
	if (!off)
		return -1;
	sscanf(off, "Uid: %u %u", &pstatus->uid, &pstatus->euid);
	off = strstr(buf, "Gid:");
	if (!off)
		return -1;
	sscanf(off, "Gid: %u %u", &pstatus->gid, &pstatus->egid);
	return 0;
}

int
pidfile(const char *file)
{
	char *end;

	errno = 0;
	strtol(file, &end, 10);
	if (*end != '\0')
		return 0;
	if (errno != 0)
		return 0;
	return 1;
}
