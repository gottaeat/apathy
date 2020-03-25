# sinit version
VERSION = 1.1-apathy

# paths
PREFIX = /sbin
MANPREFIX = /usr/share/man

CC = cc
LD = $(CC)
CPPFLAGS =
CFLAGS   = -Wextra -Wall -Os
LDFLAGS  = -s -static
