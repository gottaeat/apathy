/* See LICENSE file for copyright and license details. */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sysmacros.h>

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "util.h"

static void
show_stat_terse(const char *file, struct stat *st)
{
	printf("%s ", file);
	printf("%lu %lu ", (unsigned long)st->st_size,
	       (unsigned long)st->st_blocks);
	printf("%04o %u %u ", st->st_mode & 0777, st->st_uid, st->st_gid);
	printf("%llx ", (unsigned long long)st->st_dev);
	printf("%lu %lu ", (unsigned long)st->st_ino, (unsigned long)st->st_nlink);
	printf("%d %d ", major(st->st_rdev), minor(st->st_rdev));
	printf("%ld %ld %ld ", st->st_atime, st->st_mtime, st->st_ctime);
	printf("%lu\n", (unsigned long)st->st_blksize);
}

static void
show_stat(const char *file, struct stat *st)
{
	char buf[100];

	printf("  File: ‘%s’\n", file);
	printf("  Size: %lu\tBlocks: %lu\tIO Block: %lu\n", (unsigned long)st->st_size,
	       (unsigned long)st->st_blocks, (unsigned long)st->st_blksize);
	printf("Device: %xh/%ud\tInode: %lu\tLinks %lu\n", major(st->st_dev),
	       minor(st->st_dev), (unsigned long)st->st_ino, (unsigned long)st->st_nlink);
	printf("Access: %04o\tUid: %u\tGid: %u\n", st->st_mode & 0777, st->st_uid, st->st_gid);
	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&st->st_atime));
	printf("Access: %s\n", buf);
	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&st->st_mtime));
	printf("Modify: %s\n", buf);
	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&st->st_ctime));
	printf("Change: %s\n", buf);
}

static void
usage(void)
{
	eprintf("usage: %s [-L] [-t] [file...]\n", argv0);
}

int
main(int argc, char *argv[])
{
	struct stat st;
	int i, ret = 0;
	int (*fn)(const char *, struct stat *) = lstat;
	char *fnname = "lstat";
	void (*showstat)(const char *, struct stat *) = show_stat;

	ARGBEGIN {
	case 'L':
		fn = stat;
		fnname = "stat";
		break;
	case 't':
		showstat = show_stat_terse;
		break;
	default:
		usage();
	} ARGEND;

	if (argc == 0) {
		if (fstat(0, &st) < 0)
			eprintf("stat <stdin>:");
		show_stat("<stdin>", &st);
	}

	for (i = 0; i < argc; i++) {
		if (fn(argv[i], &st) == -1) {
			weprintf("%s %s:", fnname, argv[i]);
			ret = 1;
			continue;
		}
		showstat(argv[i], &st);
	}

	return ret;
}
