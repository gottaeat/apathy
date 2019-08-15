## msslinux pure64 1.2 "escapism"
mssLinux is a pure 64 bit gnu+linux distribution aiming to be minimalistic while not crippling the user's ability to smoothly do their computing. it is built from scratch by following the *linux from scratch 8.4* book as its base.

![yes](assets/fetch.png)

this is the third *release* of mssLinux, 1.0 being my first attempt to build an lfs system. it was fairly *bloated* as i didn't fine tune dependencies so i wanted to give it a second try, which gave birth to 1.1. 1.1 was supposed to be tidier, more minimalistic and also have multilib support for `steam` and `wine` but it got out of hand fairly quick due to me not being experienced enough with a multilib toolchain so that idea got scrapped, resulting in 1.2.

because it is intended to be the way i document my progress and keep everything in one place, this repository does not include a build script or an installer but if desired, following the lfs 8.4 book and then building the software listed under `pkg-management/packages.md` in the same order using the configs and patches under `pkg-management/build-configs` would result in an exact copy of this system.

#### overview
```
toolchain:
 * gcc 9.2.0 (c,c++,objc,obj-c++)
 * binutils-2.32, glibc-2.29
 * linux 5.0 headers (deblobbed)

core userland:
 * util-linux-2.33.1, coreutils 8.30
 * sysklogd 1.5.1, sysvinit 2.93
 * eudev 3.2.7

languages:
 * python 2.7.15/3.7.2
 * ruby 2.6.1p33
 * lua 5.3.5, luajit 2.0.5
 * perl-5.28.1
 * nodejs-10.15.1

video/audio:
 * xorg (x11r7), mesa 19.0.4
 * alsa 1.1.8

shells:
 * bash 5.0, zsh 5.7.1, yash 2.48
```

#### patches used in the mss1 kernel:
```
 * 5.2-deblob-gnu			(fsf-la)
 * 5.2-cc_optimize_harder		(zen-kernel)
 * 4.13-graysky2-gcc-9.1-cpu-opt	(graysky2)
 * 5.2-post-factum-fixes		(pf-kernel)
 * 5.2-zen-muqss			(con kolivas)
 * 5.2-zen-tune				(zen-kernel)
 * 5.2-aldgodev-bfq-mq			(algodev)
```

#### about proprietary software under mssLinux
mssLinux in its current state is all free software including the kernel and the firmware, except the listed software below *(bear in mind that this is all i've filtered off of `parabola gnu/linux`'s blacklist so there might be more.)*:
```
[semifree] sdl		: contains a source file that doesn't mention modification.
[semifree] unzip	: contains a source file that doesn't mention modification.
[nonfree ] intel-ucode	: no modification, use restrictions.
[nonfree ] unrar	: (possible replacement) gna-unrar.
```

#### current package count and total system size:
```
$ [master][mssLinux]: pkg

 * total partition size	: 2301.11mib
 * local package count	: 376
 * removed packages	: 49

```
