### apathy-musl 1.1
*apathy musl* is a pure 64 bit linux distribution built from scratch, using the `musl libc` instead of the traditional `glibc`.

![yes](assets/fetch.png)

extensively detailed documentatiton about building the base system can be found at [apathy-mlfs](https://github.com/mssx86/apathy-mlfs) repo. once you're finished with the installation of the base system, the rest of the system can be built with the help of `void` and `alpine`/`adelie` repositories. also, there are toolchain tarballs if one wants to jump straight into building the base without going through the building steps of cross-toolchain and the toolchain.

this is the second release of apathy-musl. 1.0 being built by following documentation written by *dslm4515* which had old packages, sloppy/prone to fail writing and differences in choice of software. after writing my own build guide with [apathy-mlfs](https://github.com/mssx86/apathy-mlfs), i have continued building the system, resulting in this repo.

![yes](assets/init.png)

#### overview
```
toolchain:
 * gcc 9.2.0 (c,c++) + isl-0.19 + argp-standalone-1.3
 * binutils 2.32, linux 5.2 headers
 * musl libc 1.1.23, musl-fts-1.2.7, musl-obstack-1.1
 * gcompat-0.4.0 + libucontext-0.1.3 + adelie shimmy

core userland:
 * util-linux-2.34, coreutils 8.31
 * busybox-1.31.0, defconfig (static)
 * sysklogd 1.5.1, sysvinit 2.96
 * eudev 3.2.8, openbsd doas

languages:
 * python 2.7.16, 3.7.4
 * lua 5.3.5, 5.1.5
 * perl-5.30

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

 > total partition size	: 1657.14mib
 > local package count	: 345
 > removed packages	: 4
```
