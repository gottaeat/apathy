/* See LICENSE file for copyright and license details. */
#include <sys/swap.h>

#include <mntent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s -a | device\n", argv0);
}

int
main(int argc, char *argv[])
{
	int i;
	int ret = 0;
	int all = 0;
	struct mntent *me;
	FILE *fp;

	ARGBEGIN {
	case 'a':
		all = 1;
		break;
	default:
		usage();
	} ARGEND;

	if ((!all && argc < 1) || (all && argc > 0))
		usage();

	if (all) {
		fp = setmntent("/etc/fstab", "r");
		if (!fp)
			eprintf("setmntent %s:", "/etc/fstab");
		while ((me = getmntent(fp)) != NULL) {
			if (strcmp(me->mnt_type, MNTTYPE_SWAP) == 0) {
				if (swapoff(me->mnt_fsname) < 0) {
					weprintf("swapoff %s:", me->mnt_fsname);
					ret = 1;
				}
			}
		}
		endmntent(fp);
	} else {
		for (i = 0; i < argc; i++) {
			if (swapoff(argv[i]) < 0) {
				weprintf("swapoff %s:", argv[i]);
				ret = 1;
			}
		}
	}
	return ret;
}
