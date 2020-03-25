/* See LICENSE file for copyright and license details. */
#include <sys/syscall.h>

#include <stdio.h>
#include <unistd.h>

#include "reboot.h"
#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s -h | -s\n", argv0);
}

int
main(int argc, char *argv[])
{
	int hflag = 0, sflag = 0, cmd;

	ARGBEGIN {
	case 'h':
		hflag = 1;
		break;
	case 's':
		sflag = 1;
		break;
	default:
		usage();
	} ARGEND;

	if (argc || !(hflag ^ sflag))
		usage();

	cmd = hflag ? LINUX_REBOOT_CMD_CAD_ON : LINUX_REBOOT_CMD_CAD_OFF;

	if (syscall(__NR_reboot, LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2,
	            cmd, NULL) < 0)
		eprintf("reboot:");

	return 0;
}
