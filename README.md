# apathy
apathy is a 64 bit libre linux distribution built from scratch for my own purposes using [apathy-mlfs](https://github.com/mssx86/apathy-mlfs) for its base; utilizing `musl` libc, `libressl`, partially `busybox` and `sysvinit` with [a home-brewed init structure](https://github.com/mssx86/apathy/tree/apathy-musl/init-scripts) written in posix shell.

<p align="center"><img src="https://raw.githubusercontent.com/mssx86/apathy/apathy-musl/assets/fetch.png"></p>

## about
apathy (which at one point was called *mssLinux*) initially used lfs-8.4/9.0-rc1 as its base and the rest was mostly built off of reading gentoo `ebuild`'s and arch/parabola `PKGBUILD`'s. i wrote most of the [apathy-utils](https://github.com/mssx86/apathy/tree/apathy-musl/apathy-utils) and [scripts](https://github.com/mssx86/apathy/tree/apathy-musl/directories/personal/home/mss/.config/scripts) alongside the [init structure](https://github.com/mssx86/apathy/tree/apathy-musl/init-scripts) when i was using this version.

after wanting to have a `musl` based system of my own, i stumbled upon `mlfs`, written by [dslm4515](https://github.com/dslm4515). attempting to build a base using their work didn't work out so i contributed to their work to a degree where a functional base system could be built via doing testing/fixing/editorial work on their project. `apathy-musl 1.0` was what i called the system i built during this time, using `mlfs` as the base.

after getting used to living with `musl` and `libressl`, i forked `mlfs` and rewrote it from scratch using a cleaner documentation style, updated packages, a different init system, different shells and more different choices in software, which i named [apathy-mlfs](https://github.com/mssx86/apathy-mlfs). my current system is built on top of this book.

## building a similar system
building the base that *apathy musl 1.1* uses can be accomplished by following the documentation available at [apathy-mlfs](https://github.com/mssx86/apathy-mlfs) which also includes and already working toolchain for skipping the `cross-toolchain` and `toolchain` steps so jumping straigth into building the final system is possible.

once the base is done, progressing further can be accomplished by reading package recipes and gathering patches for building software with `musl` from [pkgs.alpinelinux.org](https://pkgs.alpinelinux.org/packages?name=&branch=edge&arch=x86_64) and [voidlinux.org/packages](https://voidlinux.org/packages/). patches for building via `libressl` can be obtained from [gentoo libressl testing overlay](https://github.com/gentoo/libressl). i serve patches that i used to build all the software listed at [packages.md](https://github.com/mssx86/apathy/blob/apathy-musl/pkg-management/packages.md) in [here](https://github.com/mssx86/apathy/tree/apathy-musl/pkg-management/patches).

<p align="center"><img src="https://raw.githubusercontent.com/mssx86/apathy/apathy-musl/assets/init.png"></p>



## overview
#### major components:
```
toolchain:
 * gcc 9.2.1 (20200104 snapshot) (c,c++), argp-standalone 1.3
 * mpfr 4.0.2, gmp 6.1.2, mpc 1.1.0
 * binutils 2.33.1, linux 5.2 headers
 * musl libc 1.1.24, musl-fts 1.2.7, musl-obstack 1.1
 * gcompat 0.4.0 + libucontext 0.1.3 + adelie shimmy

core userland:
 * util-linux 2.34, coreutils 8.31
 * busybox 1.31.1 (statically linked, defconfig)
 * sysklogd 1.5.1, sysvinit 2.96
 * eudev 3.2.9, doas from openbsd 6.5
 * libressl-3.0.2

languages:
 * python 2.7.16, 3.7.4
 * lua 5.2.4
 * perl 5.30

video/audio:
 * xorg (x11r7), mesa 19.1.7
 * alsa 1.1.9

shells:
 * yash 2.49 (/bin/sh: busybox 1.31.1 ash)
```

#### current package count and partition size:
```
 $  ~: pkg

 > total partition size : 1459.84mib
 > local package count  : 339
 > removed packages     : 19
```

## dotfiles
alongside all of the [system related configurations](https://github.com/mssx86/apathy/tree/apathy-musl/directories/system/etc), the [init structure](https://github.com/mssx86/apathy/tree/apathy-musl/init-scripts) to the [package build scripts and configurations](https://github.com/mssx86/apathy/tree/apathy-musl/pkg-management), i also serve my personal configurations [here](https://github.com/mssx86/apathy/tree/apathy-musl/directories/personal/home/mss).
