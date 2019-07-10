#!/bin/env bash
if [ -z $1 ]; then echo " ! no kernel source tarball selected, exiting."; exit 1; fi

kerdir=$PWD/"$(echo $1 | sed 's/\.tar\.xz//;s/\.tar\.bz2//;s/\.tgz//')"

echo " * unpacking kernel source."
tar xf $1	&&
cd "${kerdir}"	&&

echo " * applying clang patches." &&
patch -p1 < /mss/repo/pkg-management/build-configs/kernel/patches/clang-linux-x86.patch 2>&1 > /dev/null &&

echo " * applying gnu deblob patches." &&
patch -p1 < /mss/repo/pkg-management/build-configs/kernel/patches/5.2-deblob-gnu.patch 2>&1 > /dev/null &&

echo " * removing gnu extraversion entry." &&
sed 's/EXTRAVERSION = -gnu/EXTRAVERSION =/' -i Makefile &&

echo " * copying kernel config." &&
cp /boot/config .config &&

echo " * running menuconfig for manual config." &&
make CC=clang HOSTCC=clang menuconfig &&

echo " * ready to run make."
