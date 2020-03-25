/* See LICENSE file for copyright and license details. */
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/syscall.h>

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "passwd.h"
#include "text.h"
#include "util.h"

static FILE *
spw_get_file(const char *user)
{
	FILE *fp = NULL;
	char file[PATH_MAX];
	int r;

	r = snprintf(file, sizeof(file), "/etc/tcb/%s/shadow", user);
	if (r < 0 || (size_t)r >= sizeof(file))
		eprintf("snprintf:");
	fp = fopen(file, "r+");
	if (!fp)
		fp = fopen("/etc/shadow", "r+");
	return fp;
}

static int
spw_write_file(FILE *fp, const struct spwd *spw, char *pwhash)
{
	struct spwd *spwent;
	int r = -1, w = 0;
	FILE *tfp = NULL;

	/* write to temporary file. */
	tfp = tmpfile();
	if (!tfp) {
		weprintf("tmpfile:");
		goto cleanup;
	}
	while ((spwent = fgetspent(fp))) {
		/* update entry on name match */
		if (strcmp(spwent->sp_namp, spw->sp_namp) == 0) {
			spwent->sp_pwdp = pwhash;
			w++;
		}
		errno = 0;
		if (putspent(spwent, tfp) == -1) {
			weprintf("putspent:");
			goto cleanup;
		}
	}
	if (!w) {
		weprintf("shadow: no matching entry to write to\n");
		goto cleanup;
	}
	fflush(tfp);

	if (fseek(fp, 0, SEEK_SET) == -1 || fseek(tfp, 0, SEEK_SET) == -1) {
		weprintf("fseek:");
		goto cleanup;
	}

	/* write temporary file to (tcb) shadow file */
	concat(tfp, "tmpfile", fp, "shadow");
	ftruncate(fileno(fp), ftell(tfp));

	r = 0; /* success */
cleanup:
	if (tfp)
		fclose(tfp);
	return r;
}

static int
pw_write_file(FILE *fp, const struct passwd *pw, char *pwhash) {
	struct passwd *pwent;
	int r = -1, w = 0;
	FILE *tfp = NULL;

	/* write to temporary file. */
	tfp = tmpfile();
	if (!tfp) {
		weprintf("tmpfile:");
		goto cleanup;
	}
	while ((pwent = fgetpwent(fp))) {
		/* update entry on name match */
		if (strcmp(pwent->pw_name, pw->pw_name) == 0) {
			pwent->pw_passwd = pwhash;
			w++;
		}
		errno = 0;
		if (putpwent(pwent, tfp) == -1) {
			weprintf("putpwent:");
			goto cleanup;
		}
	}
	if (!w) {
		weprintf("passwd: no matching entry to write to\n");
		goto cleanup;
	}
	fflush(tfp);

	if (fseek(fp, 0, SEEK_SET) == -1 || fseek(tfp, 0, SEEK_SET) == -1) {
		weprintf("fseek:");
		goto cleanup;
	}

	/* write to passwd file. */
	concat(tfp, "tmpfile", fp, "passwd");
	ftruncate(fileno(fp), ftell(tfp));

	r = 0; /* success */
cleanup:
	if (tfp)
		fclose(tfp);
	return r;
}

/* generates a random base64-encoded salt string of length 16 */
static void
gensalt(char *s)
{
	static const char b64[] = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	uint8_t buf[12];
	uint32_t n;
	int i;

	if (syscall(SYS_getrandom, buf, sizeof(buf), 0) < 0)
		eprintf("getrandom:");
	for (i = 0; i < 12; i += 3) {
		n = buf[i] << 16 | buf[i+1] << 8 | buf[i+2];
		*s++ = b64[n%64]; n /= 64;
		*s++ = b64[n%64]; n /= 64;
		*s++ = b64[n%64]; n /= 64;
		*s++ = b64[n];
	}
	*s++ = '\0';
}

static void
usage(void)
{
	eprintf("usage: %s [username]\n", argv0);
}

int
main(int argc, char *argv[])
{
	char *cryptpass1 = NULL, *cryptpass2 = NULL, *cryptpass3 = NULL;
	char *inpass, *p, *prevhash = NULL, salt[sizeof(PW_CIPHER) + 16] = PW_CIPHER;
	struct passwd *pw;
	struct spwd *spw = NULL;
	FILE *fp = NULL;
	int r = -1, status = 1;

	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	pw_init();
	umask(077);

	errno = 0;
	if (argc == 0)
		pw = getpwuid(getuid());
	else
		pw = getpwnam(argv[0]);
	if (!pw) {
		if (errno)
			eprintf("getpwnam: %s:", argv[0]);
		else
			eprintf("who are you?\n");
	}

	/* is using shadow entry ? */
	if (pw->pw_passwd[0] == 'x' && pw->pw_passwd[1] == '\0') {
		errno = 0;
		spw = getspnam(pw->pw_name);
		if (!spw) {
			if (errno)
				eprintf("getspnam: %s:", pw->pw_name);
			else
				eprintf("who are you?\n");
		}
	}

	/* Flush pending input */
	ioctl(0, TCFLSH, (void *)0);

	if (getuid() == 0) {
		goto newpass;
	} else {
		if (pw->pw_passwd[0] == '!' ||
		    pw->pw_passwd[0] == '*')
			eprintf("denied\n");
		if (pw->pw_passwd[0] == '\0') {
			goto newpass;
		}
		if (pw->pw_passwd[0] == 'x' &&
		    pw->pw_passwd[1] == '\0')
			prevhash = spw->sp_pwdp;
		else
			prevhash = pw->pw_passwd;
	}

	printf("Changing password for %s\n", pw->pw_name);
	inpass = getpass("Old password: ");
	if (!inpass)
		eprintf("getpass:");
	if (inpass[0] == '\0')
		eprintf("no password supplied\n");
	p = crypt(inpass, prevhash);
	if (!p)
		eprintf("crypt:");
	cryptpass1 = estrdup(p);
	if (strcmp(cryptpass1, prevhash) != 0)
		eprintf("incorrect password\n");

newpass:
	inpass = getpass("Enter new password: ");
	if (!inpass)
		eprintf("getpass:");
	if (inpass[0] == '\0')
		eprintf("no password supplied\n");

	if(prevhash) {
		p = crypt(inpass, prevhash);
		if (!p)
			eprintf("crypt:");
		if (cryptpass1 && strcmp(cryptpass1, p) == 0)
			eprintf("password left unchanged\n");
	}
	gensalt(salt + strlen(salt));
	p = crypt(inpass, salt);
	if (!p)
		eprintf("crypt:");
	cryptpass2 = estrdup(p);

	/* Flush pending input */
	ioctl(0, TCFLSH, (void *)0);

	inpass = getpass("Retype new password: ");
	if (!inpass)
		eprintf("getpass:");
	if (inpass[0] == '\0')
		eprintf("no password supplied\n");
	p = crypt(inpass, salt);
	if (!p)
		eprintf("crypt:");
	cryptpass3 = estrdup(p);
	if (strcmp(cryptpass2, cryptpass3) != 0)
		eprintf("passwords don't match\n");

	fp = spw_get_file(pw->pw_name);
	if (fp) {
		r = spw_write_file(fp, spw, cryptpass3);
	} else {
		fp = fopen("/etc/passwd", "r+");
		if (fp)
			r = pw_write_file(fp, pw, cryptpass3);
		else
			weprintf("fopen:");
	}
	if (!r)
		status = 0;

	if (fp)
		fclose(fp);
	free(cryptpass3);
	free(cryptpass2);
	free(cryptpass1);

	return status;
}
