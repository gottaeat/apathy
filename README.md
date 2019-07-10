## msslinux pure64 1.2 "escapism"

mssLinux is a pure 64bit linux distribution built by following the  *linux from scratch 8.4* and *beyond linux from scratch 8.4* books. besides the official books, i've used `PKGBUILD`'s from arch official repositories and aur to get build instructions and fine-tune them to my liking. there also have been times where i've read gentoo `ebuild`'s for checking dependencies regarding the components i want in software. 

![yes](assets/fetch.png)

this is the third *release* of mssLinux, 1.0 being my first experience with lfs. my first attempt was really bloated as i didn't fine tune dependencies so i wanted to give it another go but also with 32bit libraries, that got out of hand real quick so i gave up on the idea of a multilib system. 

instead of having a multilib toolchain and 32bit libraries, i install a binary distribution inside of a `chroot` jail and strip it down from most of its components. i use that chroot when i need software that requires 32bit libraries, such as `steam` and `wine`. this approach doesn't pollute the host system and the distribution inside the jail can be easily replaced.

complete list of software installed can be found in `raw-packages.txt` or `packages.md`, under the `pkg-management` directory. the configuration files used to set up or compile software is under the `pkg-management/build-configs` directory.

![indeed](assets/tism.png)

#### current package count and total system size:
```
[15:31] mss mssLinux [master]: pkg
 * total partition size	: 3058.51m
 * local package count	: 378
 * removed packages	: 37
```
