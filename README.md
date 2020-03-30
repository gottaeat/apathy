# apathy
apathy is a 64 bit libre linux distribution built from scratch for my own purposes using [apathy-mlfs](https://github.com/mssx86/apathy-mlfs) for its base; utilizing `musl` libc, `libressl`, partially `busybox` and `sinit` with [a home-brewed init structure](https://github.com/mssx86/apathy/tree/apathy-musl/ainit-initbits) written in posix shell.

<p align="center"><img src="https://raw.githubusercontent.com/mssx86/apathy/apathy-musl/assets/asset.png"></p>

## about
apathy (which at one point was called *mssLinux*) initially used *lfs-8.4* as its base and the rest was mostly built off of reading gentoo `ebuild`'s and arch/parabola `PKGBUILD`'s. i started writing the [apathy-utils](https://github.com/mssx86/apathy/tree/apathy-musl/apathy-utils) and [scripts](https://github.com/mssx86/apathy/tree/apathy-musl/directories/personal/home/mss/.config/scripts) alongside the first iteration of the init structure, which was named [ainit-sysv-mk-i](https://github.com/mssx86/apathy/tree/apathy-musl/misc/ainit-sysv/ainit-sysv-mk-i) when i was using this version. last state of the `apathy 1.3 pure64` can be found at the [apathy-glibc branch](https://github.com/mssx86/apathy/tree/apathy-glibc).

wanting to have a `musl` based system of my own, i have stumbled upon `mlfs`, written by [dslm4515](https://github.com/dslm4515). attempting to build a base using their work didn't work out so i contributed to their work to a degree where a functional base system could be built via doing testing/fixing/editorial work on their project. `apathy-musl 1.0` was what i called the system i built during this time, using `mlfs` as the base.

after getting used to living with `musl` and `libressl`, i forked `mlfs` and rewrote it from scratch using a cleaner documentation style, updated packages, a different init system *(`sysvinit` instead of `s6`)*, different shells and more different choices in software, which i named [apathy-mlfs](https://github.com/mssx86/apathy-mlfs). this is the book that i used to build the base of the system on my long-gone *g3258* and my current *t61*. though i've added/removed/updated certain packages/patches when building for the *t61* without updating the book.

shortly after i made my switch to the t61, i rewrote the init structure from scratch. instead of doing runlevel symlinking, i completely rewrote `rc` and managed the runlevels by using `case` statements. also rewrote and simplified the `init-functions`, which was a posixified version of *lfs 8.4*'s init functions. i refer to this state of the init structure [ainit-sysv-mk-ii](https://github.com/mssx86/apathy/tree/apathy-musl/misc/ainit-sysv/ainit-sysv-mk-ii).

having always used `sysvinit`, i wanted to make my switch to the suckless' `sinit-1.1` so i've modified/configured/built `sinit`, `sbase` and `ubase`, took the static binaries and man pages of the components i needed, made the required changes to the *already-almost-portable* `ainit-sysv-mk-ii`, removed the bits that were required for managing runlevels, made changes to the init scripts that required components from either `sysvinit` or `util-linux` and replaced them with the sucklessware equivalents. [ainit-initbits](https://github.com/mssx86/apathy/tree/apathy-musl/ainit-initbits) is the current init structure of apathy.

## building a similar system
building the base that *apathy musl 1.2* uses can be accomplished by following the documentation available at [apathy-mlfs](https://github.com/mssx86/apathy-mlfs) which also includes and already working toolchain for skipping the `cross-toolchain` and `toolchain` steps so jumping straigth into building the final system is possible.

once the base is done, progressing further can be accomplished by reading package recipes and gathering patches for building software with `musl` from [pkgs.alpinelinux.org](https://pkgs.alpinelinux.org/packages?name=&branch=edge&arch=x86_64) and [voidlinux.org/packages](https://voidlinux.org/packages/). patches for building via `libressl` can be obtained from [gentoo libressl testing overlay](https://github.com/gentoo/libressl). i serve patches that i used to build all the software listed at [packages.md](https://github.com/mssx86/apathy/blob/apathy-musl/pkg-management/packages.md) in [here](https://github.com/mssx86/apathy/tree/apathy-musl/pkg-management/patches).


## overview
#### major components:
```
toolchain:
 * gcc 9.3.1 20200321 (c,c++), argp-standalone 1.3
 * (ondemand) llvm-10.0.0, clang-10.0.0
 * (ondemand) rustc-1.42.0, cbindgen-0.13.2
 * (ondemand) go-1.14.1
 * mpfr 4.0.2, gmp 6.2.0, mpc 1.1.0
 * binutils 2.33.1, linux 5.2 headers
 * musl libc 1.2.0, musl-fts 1.2.7, musl-obstack 1.1
 * gcompat 0.4.0 + libucontext 0.1.3

core userland:
 * util-linux 2.35, coreutils 8.31
 * busybox 1.31.1 (statically linked, defconfig)
 * sysklogd 1.5.1, sinit-1.1-apathy
 * eudev 3.2.9, doas from openbsd 6.6.1
 * libressl-3.0.2

languages:
 * python 2.7.17, 3.8.1
 * lua 5.2.4
 * perl 5.30.1
 * (ondemand) node.js-13.9.0

video/audio:
 * xorg (x11r7), mesa 20.0.1
 * alsa 1.2.1.2

shells:
 * yash 2.49 (/bin/sh: busybox 1.31.1 ash)
```

#### current package count and partition size:
```
 $  ~: pkg

 > total partition size : 1439.93mib
 > local package count  : 326 (+5)
 > removed packages     : 21
```

## dotfiles
alongside all of the [system related configurations](https://github.com/mssx86/apathy/tree/apathy-musl/directories/system/etc), the [init structure](https://github.com/mssx86/apathy/tree/apathy-musl/init-scripts) to the [package build scripts and configurations](https://github.com/mssx86/apathy/tree/apathy-musl/pkg-management), i also serve my personal configurations [here](https://github.com/mssx86/apathy/tree/apathy-musl/directories/personal/home/mss).
