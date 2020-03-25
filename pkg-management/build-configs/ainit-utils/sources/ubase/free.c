/* See LICENSE file for copyright and license details. */
#include <sys/sysinfo.h>

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

static unsigned int mem_unit = 1;
static unsigned int unit_shift;

static unsigned long long
scale(unsigned long long v)
{
	return (v * mem_unit) >> unit_shift;
}

static void
usage(void)
{
	eprintf("usage: %s [-bkmg]\n", argv0);
}

int
main(int argc, char *argv[])
{
	struct sysinfo info;

	if (sysinfo(&info) < 0)
		eprintf("sysinfo:");
	mem_unit = info.mem_unit ? info.mem_unit : 1;

	ARGBEGIN {
	case 'b':
		unit_shift = 0;
		break;
	case 'k':
		unit_shift = 10;
		break;
	case 'm':
		unit_shift = 20;
		break;
	case 'g':
		unit_shift = 30;
		break;
	default:
		usage();
	} ARGEND;

	printf("     %13s%13s%13s%13s%13s\n",
	       "total",
	       "used",
	       "free",
	       "shared", "buffers");
	printf("Mem: ");
	printf("%13llu%13llu%13llu%13llu%13llu\n",
	       scale(info.totalram),
	       scale(info.totalram - info.freeram),
	       scale(info.freeram),
	       scale(info.sharedram),
	       scale(info.bufferram));
	printf("-/+ buffers/cache:");
	printf("%13llu%13llu\n",
	       scale(info.totalram - info.freeram - info.bufferram),
	       scale(info.freeram + info.bufferram));
	printf("Swap:");
	printf("%13llu%13llu%13llu\n",
	       scale(info.totalswap),
	       scale(info.totalswap - info.freeswap),
	       scale(info.freeswap));
	return 0;
}
