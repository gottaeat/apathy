/* See LICENSE file for copyright and license details. */
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "rtc.h"
#include "util.h"

static void
readrtctm(struct tm *tm, int fd)
{
	struct rtc_time rt;

	memset(&rt, 0, sizeof(rt));
	if (ioctl(fd, RTC_RD_TIME, &rt) < 0)
		eprintf("RTC_RD_TIME:");
	tm->tm_sec = rt.tm_sec;
	tm->tm_min = rt.tm_min;
	tm->tm_hour = rt.tm_hour;
	tm->tm_mday = rt.tm_mday;
	tm->tm_mon = rt.tm_mon;
	tm->tm_year = rt.tm_year;
	tm->tm_wday = rt.tm_wday;
	tm->tm_yday = rt.tm_yday;
	tm->tm_isdst = rt.tm_isdst;
}

static void
writertctm(struct tm *tm, int fd)
{
	struct rtc_time rt;

	rt.tm_sec = tm->tm_sec;
	rt.tm_min = tm->tm_min;
	rt.tm_hour = tm->tm_hour;
	rt.tm_mday = tm->tm_mday;
	rt.tm_mon = tm->tm_mon;
	rt.tm_year = tm->tm_year;
	rt.tm_wday = tm->tm_wday;
	rt.tm_yday = tm->tm_yday;
	rt.tm_isdst = tm->tm_isdst;
	if (ioctl(fd, RTC_SET_TIME, &rt) < 0)
		eprintf("RTC_SET_TIME:");
}

static void
show(char *dev)
{
	struct tm tm;
	time_t t;
	int fd;

	fd = open(dev, O_RDONLY);
	if (fd < 0)
		eprintf("open %s:", dev);
	readrtctm(&tm, fd);
	t = mktime(&tm);
	printf("%s", asctime(localtime(&t)));
	close(fd);
}

static void
hctosys(char *dev)
{
	struct timeval tv;
	struct tm tm;
	int r;
	int fd;

	fd = open(dev, O_RDONLY);
	if (fd < 0)
		eprintf("open %s:", dev);
	readrtctm(&tm, fd);
	tv.tv_sec = mktime(&tm);
	tv.tv_usec = 0;
	r = settimeofday(&tv, NULL);
	if (r < 0)
		eprintf("settimeofday:");
	close(fd);
}

static void
systohc(char *dev)
{
	struct timeval tv;
	struct tm *tm;
	time_t t;
	int fd;

	fd = open(dev, O_WRONLY);
	if (fd < 0)
		eprintf("open %s:", dev);
	gettimeofday(&tv, NULL);
	t = tv.tv_sec;
	tm = gmtime(&t);
	weprintf("warning: assuming UTC for systohc\n");
	writertctm(tm, fd);
	close(fd);
}

static void
usage(void)
{
	eprintf("usage: %s [-rsw] [-u] [dev]\n", argv0);
}

int
main(int argc, char *argv[])
{
	char *dev = "/dev/rtc";
	int rflag = 0;
	int sflag = 0;
	int wflag = 0;

	ARGBEGIN {
	case 'r':
		rflag = 1;
		break;
	case 's':
		sflag = 1;
		break;
	case 'w':
		wflag = 1;
		break;
	case 'u':
		break;
	default:
		usage();
	} ARGEND;

	if (argc > 1)
		usage();
	else if (argc == 1)
		dev = argv[0];

	if ((rflag ^ sflag ^ wflag) == 0)
		eprintf("missing or incompatible function\n");

	/* Only UTC support at the moment */
	setenv("TZ", "UTC0", 1);
	tzset();

	if (rflag == 1)
		show(dev);
	else if (sflag == 1)
		hctosys(dev);
	else if (wflag == 1)
		systohc(dev);

	return 0;
}