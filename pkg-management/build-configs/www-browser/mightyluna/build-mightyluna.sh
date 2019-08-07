#!/bin/env bash
# a >> check if a tarball is selected
if	[ -z $1 ];		then printf "\n ! no archive selected, exiting.\n\n";	exit 1
elif	[ ! -f "${PWD}/${1}" ];	then printf "\n ! tarball doesn't exist, exiting.\n\n";	exit 1
fi

# b >> check if $1 is a palemoon tarball
case $1 in
 *PM*)
  printf " * archive is a palemoon source tarball.\n\n" ;;
 *)
  printf " * ${1} is not a palemoon source tarball, exiting.\n"
  exit 1 ;;
esac

# c >> set build vars
arname=$(echo UXP-$(echo $1 | sed 's/.tar.gz//'))			&&
repodir="/mss/repo/pkg-management/build-configs/www-browser/mightyluna"	&&
srcdir=/mss/work/UXP							&&

# d >> action
# d0 >> die if patch fails
patch_faildie(){
printf "\n ! patching failed, exiting with 1.\n\n"			&&
exit 1
}

# d1 >> extract tarball
printf " * extracting ${1}."						&&
tar xf $1								&&
printf "\t--> done.\n"							&&

# d2 >> mv to /mss/work/UXP
printf " * renaming dirs."						&&
mv "${arname}" "/mss/work/UXP"						&&
printf "\t\t\t--> done.\n"						&&
cd "${srcdir}"								&&

# d3 >> apply mightyluna branding
printf " * applying mightyluna branding patch."				&&
patch -p1 < "${repodir}"/0001-mightyluna-branding-28.6.1.patch \
 &>> /tmp/mightyluna-build.log || patch_faildie				&&
printf "\t--> done.\n"							&&

# d4 >> copy mozconfig
printf " * copying mozconfig."						&&
cp "${repodir}"/mightyluna-mozconfig.config \
 "${srcdir}"/mozconfig							&&
printf "\t\t\t--> done.\n"						&&

# d5 >> run sed from arch
printf " * running sed."						&&
sed -i 's#xlocale#locale#' \
 "${srcdir}"/intl/icu/source/i18n/digitlst.cpp				&&
printf "\t\t\t\t--> done.\n"						&&

# d6 >> set mach vars
export pkgname="mightyluna (palemoon)"					&&
export pkgver=28.6.1							&&
export MOZBUILD_STATE_PATH="$srcdir/mozbuild"				&&
export MOZCONFIG="$srcdir/mozconfig"					&&
export CPPFLAGS="$CPPFLAGS -O2 -Wno-format-overflow"			&&	

# d6.1 >> print mach vars
printf "\n + pkgname\t: ${pkgname}\n + pkgver\t: ${pkgver}\n"		&&
printf " + srcdir\t: $srcdir\n + mozbuild\t: ${MOZBUILD_STATE_PATH}\n"	&&
printf " + mozconfig\t: ${MOZCONFIG}\n + cppflags\t: ${CPPFLAGS}\n"	&&

# d7 >> check everything and ask to run mach
printf "\n * ready to run mach, shall we continue? (y/n): "		&&
read answerbuild
 if [ "$answerbuild" != "${answerbuild#[Yy]}" ]
  then
   cd "${srcdir}"							&&
   vi mozconfig								&&
   printf " * running mach.\n"						&&
   printf " * tail -f /tmp/mightyluna-build.log to view progress.\n"	&&
   python2.7 mach build &>> /tmp/mightyluna-build.log
  else
   printf " * not running mach.\n"		&&
   exit 0
 fi

# d8 >> ask to install build
printf "\n * build complete, shall we run the installer? (y/n): "	&&
read answerinst
 if [ "$answerinst" != "${answerinst#[Yy]}" ]
  then
   printf " * installing.\n"						&&
   printf " * tail -f /tmp/mightyluna-build.log to view progress.\n"	&&
   su -c "python2.7 mach install &>> /tmp/mightyluna-build.log"		&&
   printf "\n * installation complete.\n"
  else
   printf "\n * not installing.\n"					&&
   exit 0
 fi
