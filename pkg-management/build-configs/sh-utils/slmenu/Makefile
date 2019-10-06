# slmenu - single line menu
# See LICENSE file for copyright and license details.

include config.mk

SRC = slmenu.c
OBJ = ${SRC:.c=.o}

all: options slmenu

options:
	@echo slmenu build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC -c $<
	@${CC} -c $< ${CFLAGS}

${OBJ}: config.mk

slmenu: slmenu.o
	@echo CC -o $@
	@${CC} -o $@ slmenu.o ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f slmenu ${OBJ} slmenu-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p slmenu-${VERSION}
	@cp LICENSE Makefile README config.mk slmenu.1 ${SRC} slmenu-${VERSION}
	@tar -cf slmenu-${VERSION}.tar slmenu-${VERSION}
	@gzip slmenu-${VERSION}.tar
	@rm -rf slmenu-${VERSION}

install: all
	@echo installing executables to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f slmenu ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/slmenu
	@echo installing manual pages to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < slmenu.1 > ${DESTDIR}${MANPREFIX}/man1/slmenu.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/slmenu.1

uninstall:
	@echo removing executables from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/slmenu
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/slmenu.1

.PHONY: all options clean dist install uninstall
