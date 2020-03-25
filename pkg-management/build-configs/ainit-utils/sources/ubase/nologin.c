/* See LICENSE file for copyright and license details. */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int
main(void)
{
	int fd;
	char buf[BUFSIZ];
	ssize_t n;

	fd = open("/etc/nologin.txt", O_RDONLY);
	if (fd >= 0) {
		while ((n = read(fd, buf, sizeof(buf))) > 0)
			write(STDOUT_FILENO, buf, n);
		close(fd);
	} else {
		printf("The account is currently unavailable.\n");
	}
	return 1;
}
