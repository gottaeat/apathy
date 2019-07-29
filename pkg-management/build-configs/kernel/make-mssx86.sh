#!/bin/env bash
if [ -z $1 ]
 then
  printf " ! no kernel source tarball selected, exiting.\n" &&
  exit 1
elif [ -z $2 ]
 then
  printf " ! no compiler selected, exiting.\n" &&
  exit 1
elif [ -z $3 ]
 then
  printf " ! deblobbing option not specified, exiting.\n" &&
  exit 1
fi

kerdir="$PWD/"$(echo $1 | sed 's/\.tar\.xz//;s/\.tar\.bz2//;s/\.tgz//')""
patchdir="/mss/repo/pkg-management/build-configs/kernel/patches"

printf " * unpacking kernel source.\n"
tar xf $1 &&
printf " + done.\n\n"
cd "${kerdir}"	&&

case $2 in
 clang)
  clang --version 2> /dev/null || printf " ! clang not found, exiting.\n" && exit 1
  memepiler="clang"							&&
  printf " * building with clang\n\n * applying clang patches.\n"	&&
  patch -p1 < "${patchdir}"/clang-linux-x86.patch 2>&1 > /dev/null	&&
  printf " + done.\n\n"
 ;;
 gcc)
  memepiler="gcc"
  printf " * building with gcc.\n\n"
 ;;
 *)
  printf " ! compiler option not recognized, exiting.\n"; exit 1
 ;;
esac

if [ "${3}" = "yes" ]
 then 
  printf " * applying gnu deblob patches.\n"				&&
  patch -p1 < "${patchdir}"/5.2-deblob-gnu.patch 2>&1 > /dev/null	&&
  printf " + done.\n\n"							&&
  printf " * removing gnu extraversion entry.\n"			&&
  sed 's/EXTRAVERSION = -gnu/EXTRAVERSION =/' -i Makefile		&&
  printf " + done.\n\n"							&&
  printf " * applying freedo logo.\n"					&&
  install -m644 -t "${kerdir}"/drivers/video/logo \
  "${patchdir}"/freedo-logo/logo_linux_{clut224.ppm,vga16.ppm,mono.pbm} &&
  printf " + done.\n\n"
 else
  printf " * not applying gnu deblob patch.\n\n"
fi &&

printf " * copying kernel config.\n"	&&
cp /boot/config "${kerdir}"/.config	&&
printf " + done.\n\n"			&&

printf " * run menuconfig for manual config? (y/n): " &&
read answer

if [ "$answer" != "${answer#[Yy]}" ]
then
 printf " * running menuconfig.\n"		&&
 if [ "${memepiler}" = "clang" ]
  then make CC=clang HOSTCC=clang menuconfig
  else make menuconfig
 fi						&&
 printf " + done.\n"
else
 printf " * not running menuconfig.\n"
fi &&

printf " * run make automatically? (y/n): "	&&
read answermake

if [ "$answermake" != "${answer#[Yy]}" ]
then
 printf " * running make.\n"			&&
 if [ "${memepiler}" = "clang" ]
  then make CC=clang HOSTCC=clang -j$(($(nproc)+1))
  else make -j$(($(nproc)+1))
 fi
fi &&

printf " * all is well and done.\n * run kinst to install the kernel? (y/n): "
read answerkinst

if [ "$answerkinst" != "${answer#[Yy]}" ]
 then /mss/bin/kinst
 else printf " * not installing the built kernel."
fi
