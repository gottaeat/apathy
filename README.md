## apathy gnu/linux 1.2
apathy *(formerly known as mssLinux)* is a pure 64 bit gnu+linux distribution aiming to be minimalistic while not crippling the user's ability to smoothly do their computing. it is built from scratch by following the *linux from scratch 8.4* book as its base.

![yes](assets/fetch.png)

this is the third *release* of apathy, 1.0 being my first attempt to build an lfs system. it was fairly *bloated* as i didn't fine tune dependencies so i wanted to give it a second try, which gave birth to 1.1. 1.1 was supposed to be tidier, more minimalistic and also have multilib support for `steam` and `wine` but it got out of hand fairly quick due to me not being experienced enough with a multilib toolchain so that idea got scrapped, resulting in 1.2.

next to writing init scripts using `start-stop-daemon` from debian, i also rewrote the init scripts provided by the lfs/blfs books. made some functional changes, changes in style and removed bashisms so apathy's init system is not bound to bash in order to work.

![yes](assets/init.png)

because it is intended to be the way i document my progress and keep everything in one place, this repository does not include a build script or an installer but if desired, following the lfs 8.4 book and then building the software listed under `pkg-management/packages.md` in the same order using the configs and patches under `pkg-management/build-configs` would result in an exact copy of this system.

#### overview
```
toolchain:
 * gcc 9.2.0 (c,c++,objc,obj-c++)
 * binutils-2.32, glibc-2.29
 * linux 5.0 headers (deblobbed)

core userland:
 * util-linux-2.33.1, coreutils 8.30
 * sysklogd 1.5.1, sysvinit 2.95
 * eudev 3.2.7

languages:
 * python 2.7.15/3.7.2
 * ruby 2.6.3p62-libre
 * lua 5.3.5, luajit 2.0.5
 * perl-5.28.1

video/audio:
 * xorg (x11r7), mesa 19.0.4
 * alsa 1.1.8

shells:
 * bash 5.0, yash 2.48
```

#### patches used in the apathy kernel:
```
 * 5.2-deblob-gnu			(fsf-la)
 * 5.2-cc_optimize_harder		(zen-kernel)
 * 4.13-graysky2-gcc-9.1-cpu-opt	(graysky2)
 * 5.2-zen-muqss			(con kolivas)
 * 5.2-zen-futex			(zen-kernel)
 * 5.2-zen-tune				(zen-kernel)
 * 5.2-aldgodev-bfq-mq			(algodev + pf-kernel)
 * 5.2-enable-link-security-by-default	(gentoo-sources)
```

#### about proprietary software under apathy
apathy in its current state is all free software including the kernel and the firmware, except the listed software below *(bear in mind that this is all i've filtered off of `parabola gnu/linux`'s blacklist so there might be more.)*:
```
[nonfree ] unrar	: (possible replacement) gna-unrar.
```

#### current package count and total system size:
```
~ > pkg

* total partition size	: 2032.81mib
* local package count	: 370
* removed packages	: 59

```
