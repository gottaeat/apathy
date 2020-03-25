/* See LICENSE file for copyright and license details. */
struct procstat {
	int pid;
	char comm[PATH_MAX + 2]; /* + 2 for '(' and ')' */
	unsigned char state;
	int ppid;
	int pgrp;
	int sid;
	int tty_nr;
	int tpgid;
	unsigned flags;
	unsigned long minflt;
	unsigned long cminflt;
	unsigned long majflt;
	unsigned long cmajflt;
	unsigned long utime;
	unsigned long stime;
	long cutime;
	long cstime;
	long priority;
	long nice;
	long num_threads;
	long itrealvalue;
	unsigned long long starttime;
	unsigned long vsize;
	long rss;
	long rsslim;
};

struct procstatus {
	uid_t uid;
	uid_t euid;
	gid_t gid;
	gid_t egid;
};

int parsecmdline(pid_t pid, char *buf, size_t siz);
int parsestat(pid_t pid, struct procstat *ps);
int parsestatus(pid_t pid, struct procstatus *pstatus);
int proceuid(pid_t pid, uid_t *euid);
int procuid(pid_t pid, uid_t *euid);
int pidfile(const char *file);
