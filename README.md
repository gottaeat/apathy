### apathy-musl 1.1
*apathy musl* is a pure 64 bit linux distribution built from scratch, utilizing musl libc, aiming to be clutter free without crippling the user.

<p align="center"><img src="https://raw.githubusercontent.com/mssx86/apathy/apathy-musl/assets/fetch.png"></p>

this is the second release of apathy-musl, `1.0` being built by following the documentation written by [dslm4515](https://github.com/dslm4515). after contributing to their project, i forked their work and rewrote it from scratch using a cleaner documentation style, updated packages, a different init system and with a set of different choices in software, resulting in `1.1`.

if one wants to build the base that `apathy-musl` uses, documentation is readily available at [apathy-mlfs](https://github.com/mssx86/apathy-mlfs) repository. it includes an already working toolchain for people that wants to pass the building of the toolchain and the cross-toolchain steps and jump straight into building their system.

once the base is done, you can read `APKBUILDS` from alpine linux repositories for instructions and use this repository or void linux' package search function to find patches required for building software using `musl`. gentoo is fairly handy when it comes to finding `libressl` patches as well.

an existing irc channel on freenode can be found at `#apathy-linux` if one wants to interact with the maintainer/only user of the project.

<p align="center"><img src="https://raw.githubusercontent.com/mssx86/apathy/apathy-musl/assets/init.png"></p>

#### overview
```
toolchain:
 * gcc 9.2.1-20191005 (c,c++) + isl 0.21 + argp-standalone 1.3
 * mpfr 4.0.2, gmp 6.1.2, mpc 1.1.0
 * binutils 2.33.1, linux 5.2 headers
 * musl libc 1.1.23, musl-fts 1.2.7, musl-obstack 1.1
 * gcompat 0.4.0 + libucontext 0.1.3 + adelie shimmy

core userland:
 * util linux-2.34, coreutils 8.31
 * busybox 1.31.0 (statically linked, defconfig)
 * sysklogd 1.5.1, sysvinit 2.96
 * eudev 3.2.8, openbsd doas

languages:
 * python 2.7.16, 3.7.4
 * lua 5.3.5, 5.1.5
 * perl5.30

video/audio:
 * xorg (x11r7), mesa 19.1.7
 * alsa 1.1.9

shells:
 * yash 2.49 (/bin/sh: busybox 1.31.0 ash)
```

#### about proprietary software under apathy-musl
apathy-musl in its current state is completely free software, including the kernel and the firmware.

#### current package count and total system size
```
 ~ % pkg
 > total partition size	: 1596.13mib
 > local package count	: 346
 > removed packages	: 4
```
