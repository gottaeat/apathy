include config.mk

.SUFFIXES:
.SUFFIXES: .o .c

HDR = \
	arg.h        \
	config.h     \
	passwd.h     \
	proc.h       \
	queue.h      \
	reboot.h     \
	rtc.h        \
	text.h       \
	util.h

LIBUTIL = libutil.a
LIBUTILSRC = \
	libutil/agetcwd.c        \
	libutil/agetline.c       \
	libutil/apathmax.c       \
	libutil/concat.c         \
	libutil/ealloc.c         \
	libutil/eprintf.c        \
	libutil/estrtol.c        \
	libutil/estrtoul.c       \
	libutil/explicit_bzero.c \
	libutil/passwd.c         \
	libutil/proc.c           \
	libutil/putword.c        \
	libutil/recurse.c        \
	libutil/strlcat.c        \
	libutil/strlcpy.c        \
	libutil/strtonum.c       \
	libutil/tty.c

LIB = $(LIBUTIL)

BIN = \
	blkdiscard        \
	chvt              \
	clear             \
	ctrlaltdel        \
	dd                \
	df                \
	dmesg             \
	eject             \
	fallocate         \
	free              \
	freeramdisk       \
	fsfreeze          \
	getty             \
	halt              \
	hwclock           \
	id                \
	insmod            \
	killall5          \
	last              \
	lastlog           \
	login             \
	lsmod             \
	lsusb             \
	mesg              \
	mknod             \
	mkswap            \
	mount             \
	mountpoint        \
	nologin           \
	pagesize          \
	passwd            \
	pidof             \
	pivot_root        \
	ps                \
	pwdx              \
	readahead         \
	respawn           \
	rmmod             \
	stat              \
	su                \
	swaplabel         \
	swapoff           \
	swapon            \
	switch_root       \
	sysctl            \
	truncate          \
	umount            \
	unshare           \
	uptime            \
	vtallow           \
	watch             \
	who

MAN1 = \
	chvt.1              \
	clear.1             \
	dd.1                \
	df.1                \
	dmesg.1             \
	eject.1             \
	fallocate.1         \
	free.1              \
	id.1                \
	login.1             \
	mesg.1              \
	mknod.1             \
	mountpoint.1        \
	pagesize.1          \
	passwd.1            \
	pidof.1             \
	ps.1                \
	pwdx.1              \
	respawn.1           \
	stat.1              \
	su.1                \
	truncate.1          \
	unshare.1           \
	uptime.1            \
	vtallow.1           \
	watch.1             \
	who.1

MAN8 = \
	ctrlaltdel.8        \
	freeramdisk.8       \
	fsfreeze.8          \
	getty.8             \
	halt.8              \
	hwclock.8           \
	insmod.8            \
	killall5.8          \
	lastlog.8           \
	lsmod.8             \
	lsusb.8             \
	mkswap.8            \
	mount.8             \
	nologin.8           \
	pivot_root.8        \
	readahead.8         \
	rmmod.8             \
	swaplabel.8         \
	swapoff.8           \
	swapon.8            \
	switch_root.8       \
	sysctl.8            \
	umount.8

LIBUTILOBJ = $(LIBUTILSRC:.c=.o)
OBJ = $(BIN:=.o) $(LIBUTILOBJ)
SRC = $(BIN:=.c)

all: $(BIN)

$(BIN): $(LIB)

$(OBJ): $(HDR) config.mk

config.h:
	cp config.def.h $@

.o:
	$(CC) $(LDFLAGS) -o $@ $< $(LIB) $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(LIBUTIL): $(LIBUTILOBJ)
	$(AR) rc $@ $?
	$(RANLIB) $@

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f $(BIN) $(DESTDIR)$(PREFIX)/bin
	cd $(DESTDIR)$(PREFIX)/bin && chmod 755 $(BIN)
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	for m in $(MAN1); do sed "s/^\.Os ubase/.Os ubase $(VERSION)/g" < "$$m" > $(DESTDIR)$(MANPREFIX)/man1/"$$m"; done
	mkdir -p $(DESTDIR)$(MANPREFIX)/man8
	for m in $(MAN8); do sed "s/^\.Os ubase/.Os ubase $(VERSION)/g" < "$$m" > $(DESTDIR)$(MANPREFIX)/man8/"$$m"; done
	cd $(DESTDIR)$(MANPREFIX)/man1 && chmod 644 $(MAN1)
	cd $(DESTDIR)$(MANPREFIX)/man8 && chmod 644 $(MAN8)

uninstall:
	cd $(DESTDIR)$(PREFIX)/bin && rm -f $(BIN)
	cd $(DESTDIR)$(MANPREFIX)/man1 && rm -f $(MAN1)
	cd $(DESTDIR)$(MANPREFIX)/man8 && rm -f $(MAN8)

dist: clean
	mkdir -p ubase-$(VERSION)
	cp -r LICENSE Makefile README TODO config.mk $(SRC) $(MAN1) $(MAN8) libutil $(HDR) config.def.h ubase-$(VERSION)
	tar -cf ubase-$(VERSION).tar ubase-$(VERSION)
	gzip ubase-$(VERSION).tar
	rm -rf ubase-$(VERSION)

ubase-box: $(LIB) $(SRC)
	mkdir -p build
	cp $(HDR) build
	cp config.h build
	for f in $(SRC); do sed "s/^main(/`basename $$f .c`_&/" < $$f > build/$$f; done
	echo '#include <libgen.h>'  > build/$@.c
	echo '#include <stdio.h>'  >> build/$@.c
	echo '#include <stdlib.h>' >> build/$@.c
	echo '#include <string.h>' >> build/$@.c
	echo '#include "util.h"'   >> build/$@.c
	for f in $(SRC); do echo "int `basename $$f .c`_main(int, char **);" >> build/$@.c; done
	echo 'int main(int argc, char *argv[]) { char *s = basename(argv[0]); if(!strcmp(s,"ubase-box")) { argc--; argv++; s = basename(argv[0]); } if(0) ;' >> build/$@.c
	for f in $(SRC); do echo "else if(!strcmp(s, \"`basename $$f .c`\")) return `basename $$f .c`_main(argc, argv);" >> build/$@.c; done
	echo 'else {' >> build/$@.c
	for f in $(SRC); do echo "printf(\"`basename $$f .c`\"); putchar(' ');" >> build/$@.c; done
	echo "putchar(0xa); }; return 0; }" >> build/$@.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ build/*.c $(LIB) $(LDLIBS)
	rm -r build

ubase-box-install: ubase-box
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f ubase-box $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/ubase-box
	for f in $(BIN); do ln -sf ubase-box $(DESTDIR)$(PREFIX)/bin/"$$f"; done
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	for m in $(MAN1); do sed "s/^\.Os ubase/.Os ubase $(VERSION)/g" < "$$m" > $(DESTDIR)$(MANPREFIX)/man1/"$$m"; done
	mkdir -p $(DESTDIR)$(MANPREFIX)/man8
	for m in $(MAN8); do sed "s/^\.Os ubase/.Os ubase $(VERSION)/g" < "$$m" > $(DESTDIR)$(MANPREFIX)/man8/"$$m"; done
	cd $(DESTDIR)$(MANPREFIX)/man1 && chmod 644 $(MAN1)
	cd $(DESTDIR)$(MANPREFIX)/man8 && chmod 644 $(MAN8)

clean:
	rm -f $(BIN) $(OBJ) $(LIB) ubase-box ubase-$(VERSION).tar.gz

.PHONY:
	all install uninstall dist ubase-box ubase-box-install clean
