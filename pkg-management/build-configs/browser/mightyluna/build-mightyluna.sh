#!/bin/env bash
if [ -z $1 ]; then echo " ! no archive selected."; exit 1; fi

arname=$(echo UXP-$(echo $1 | sed 's/.tar.gz//'))			&&
repodir="/mss/repo/pkg-management/build-configs/browser/mightyluna"	&&
srcdir=/mss/work/UXP							&&

printf "\n * extracting ${1}.\n"
tar xf $1								&&

printf "\n * renaming dirs.\n"						&&
mv -v "${arname}" "/mss/work/UXP"					&&

cd "${srcdir}"								&&

printf "\n * applying mightyluna branding patch.\n"			&&
patch -p1 < "${repodir}"/0001-mightyluna-branding-28.6.1.patch		&&

printf "\n * applying gcc9.1 patch.\n"					&&
patch -p1 < "${repodir}"/0002-palemoon-gcc9.1.patch			&&

printf "\n * copying mozconfig.\n"
cp -v "${repodir}"/mightyluna-mozconfig-syslibs.config \
 "${srcdir}"/mozconfig							&&

export pkgname=palemoon							&&
export pkgver=28.6.1							&&
export MOZBUILD_STATE_PATH="$srcdir/mozbuild"				&&
export MOZCONFIG="$srcdir/mozconfig"					&&
export CPPFLAGS="$CPPFLAGS -O2"						&&

printf "\npkgname\t\t: ${pkgname}\npkgver\t\t: ${pkgver}\n"		&&
printf "srcdir\t\t: $srcdir\nmozbuild\t: ${MOZBUILD_STATE_PATH}\n"	&&
printf "mozconfig\t: ${MOZCONFIG}\ncppflags\t: ${CPPFLAGS}\n"		&&

printf "\n * ready to run mach, shall we continue? (y/n):"
read answer
 if [ "$answer" != "${answer#[Yy]}" ]
  then
   cd "${srcdir}"	&&
   vi mozconfig		&&
   python2.7 mach build  &&
   printf " * run mach install via su.\n"
 elif [ "$answer" != "${answer#[Nn]}" ];
   then exit 0
 else " ! input Yy or Nn."; exit 1
 fi
