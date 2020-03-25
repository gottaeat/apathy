/* See LICENSE file for copyright and license details. */
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "text.h"
#include "util.h"

static void
replacestr(char *s, int a, int b)
{
	for (; *s; s++)
		if (*s == a)
			*s = b;
}

static int
getsysctl(char *variable, char **value)
{
	char path[PATH_MAX];
	char *p;
	char *buf, *tmp, c;
	int fd;
	ssize_t n;
	size_t sz, i;

	replacestr(variable, '.', '/');

	strlcpy(path, "/proc/sys/", sizeof(path));
	if (strlcat(path, variable, sizeof(path)) >= sizeof(path)) {
		replacestr(variable, '/', '.');
		return -1;
	}

	replacestr(variable, '/', '.');

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return -1;

	i = 0;
	sz = 1;
	buf = NULL;
	while (1) {
		n = read(fd, &c, 1);
		if (n < 0) {
			close(fd);
			free(buf);
			return -1;
		}
		if (n == 0)
			break;
		if (i == sz - 1) {
			sz *= 2;
			tmp = realloc(buf, sz);
			if (!tmp) {
				close(fd);
				free(buf);
				return -1;
			}
			buf = tmp;
		}
		buf[i++] = c;
	}
	buf[i] = '\0';

	p = strrchr(buf, '\n');
	if (p)
		*p = '\0';

	*value = buf;

	close(fd);

	return 0;
}

static int
setsysctl(char *variable, char *value)
{
	char path[PATH_MAX];
	int fd;
	ssize_t n;

	replacestr(variable, '.', '/');

	strlcpy(path, "/proc/sys/", sizeof(path));
	if (strlcat(path, variable, sizeof(path)) >= sizeof(path)) {
		replacestr(variable, '/', '.');
		return -1;
	}

	replacestr(variable, '/', '.');

	fd = open(path, O_WRONLY);
	if (fd < 0)
		return -1;

	n = write(fd, value, strlen(value));
	if ((size_t)n != strlen(value)) {
		close(fd);
		return -1;
	}

	close(fd);

	return 0;
}

static int
parsepair(char *pair)
{
	char *p;
	char *variable;
	char *value;

	for (p = pair; *p; p++) {
		if (p[0] == '.' && p[1] == '.') {
			weprintf("malformed input: %s\n", pair);
			return -1;
		}
	}
	p = strchr(pair, '=');
	if (p) {
		if (p[1] == '\0') {
			weprintf("malformed input: %s\n", pair);
			return -1;
		}
		*p = '\0';
		value = &p[1];
	} else {
		value = NULL;
	}
	variable = pair;
	if (value) {
		if (setsysctl(variable, value) < 0) {
			weprintf("failed to set sysctl for %s\n", variable);
			return -1;
		}
	} else {
		if (getsysctl(variable, &value) < 0) {
			weprintf("failed to get sysctl for %s\n", variable);
			return -1;
		}
		printf("%s = %s\n", variable, value);
		free(value);
	}

	return 0;
}

static void
usage(void)
{
	eprintf("usage: %s [-p file] variable[=value]...\n", argv0);
}

int
main(int argc, char *argv[])
{
	FILE *fp;
	char *buf = NULL, *p;
	char *file = NULL;
	size_t size = 0;
	int i;
	int r = 0;

	ARGBEGIN {
	case 'p':
		file = EARGF(usage());
		break;
	default:
		usage();
	} ARGEND;

	if (!file && argc < 1)
		usage();

	if (!file) {
		for (i = 0; i < argc; i++)
			if (parsepair(argv[i]) < 0)
				r = 1;
	} else {
		fp = fopen(file, "r");
		if (!fp)
			eprintf("fopen %s:", file);
		while (agetline(&buf, &size, fp) != -1) {
			p = buf;
			for (p = buf; *p == ' ' || *p == '\t'; p++)
				;
			if (*p == '#' || *p == '\n')
				continue;
			for (p = buf; *p; p++) {
				if (*p == '\n') {
					*p = '\0';
					break;
				}
			}
			p = buf;
			if (parsepair(p) < 0)
				r = 1;
		}
		if (ferror(fp))
			eprintf("%s: read error:", file);
		free(buf);
		fclose(fp);
	}

	return r;
}
