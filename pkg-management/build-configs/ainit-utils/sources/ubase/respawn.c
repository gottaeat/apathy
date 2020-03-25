/* See LICENSE file for copyright and license details. */
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

static void
sigterm(int sig)
{
	if (sig == SIGTERM) {
		kill(0, SIGTERM);
		_exit(0);
	}
}

static void
usage(void)
{
	eprintf("usage: %s [-l fifo] [-d N] cmd [args...]\n", argv0);
}

int
main(int argc, char *argv[])
{
	char *fifo = NULL;
	unsigned int delay = 0;
	pid_t pid;
	char buf[BUFSIZ];
	int savederrno;
	ssize_t n;
	struct pollfd pollset[1];
	int polln;

	ARGBEGIN {
	case 'd':
		delay = estrtol(EARGF(usage()), 0);
		break;
	case 'l':
		fifo = EARGF(usage());
		break;
	default:
		usage();
	} ARGEND;

	if (argc < 1)
		usage();

	if (fifo && delay > 0)
		usage();

	setsid();

	signal(SIGTERM, sigterm);

	if (fifo) {
		pollset->fd = open(fifo, O_RDONLY | O_NONBLOCK);
		if (pollset->fd < 0)
			eprintf("open %s:", fifo);
		pollset->events = POLLIN;
	}

	while (1) {
		if (fifo) {
			pollset->revents = 0;
			polln = poll(pollset, 1, -1);
			if (polln <= 0) {
				if (polln == 0 || errno == EAGAIN)
					continue;
				eprintf("poll:");
			}
			while ((n = read(pollset->fd, buf, sizeof(buf))) > 0)
				;
			if (n < 0)
				if (errno != EAGAIN)
					eprintf("read %s:", fifo);
			if (n == 0) {
				close(pollset->fd);
				pollset->fd = open(fifo, O_RDONLY | O_NONBLOCK);
				if (pollset->fd < 0)
					eprintf("open %s:", fifo);
				pollset->events = POLLIN;
			}
		}
		pid = fork();
		if (pid < 0)
			eprintf("fork:");
		switch (pid) {
		case 0:
			execvp(argv[0], argv);
			savederrno = errno;
			weprintf("execvp %s:", argv[0]);
			_exit(savederrno == ENOENT ? 127 : 126);
			break;
		default:
			waitpid(pid, NULL, 0);
			break;
		}
		if (!fifo)
			sleep(delay);
	}
	/* not reachable */
	return 0;
}
