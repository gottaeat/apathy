#!/bin/env bash

patch -Np1 -b -z .orig < ../windowmaker-0.95.8-imagemagick7.patch &&

for file in WindowMaker/*menu* util/wmgenmenu.c; do
 if [[ -r $file ]] ; then
  sed -i -e "s:/usr/local/GNUstep/Applications/WPrefs.app:/usr/bin/:g;" "$file"
  sed -i -e "s:/usr/local/share/WindowMaker:/usr/share/WindowMaker:g;" "$file"
  sed -i -e "s:/opt/share/WindowMaker:/usr/share/WindowMaker:g;" "$file"
 fi;
done &&

autoreconf -fi &&

LINGUAS="" \
./configure \
 --prefix=/usr                           \
 --sysconfdir=/etc                       \
 --enable-xinerama                       \
 --localedir=/usr/share/locale           \
 --with-gnustepdir=/usr/lib/GNUstep      \
 --enable-usermenu                       \
 --enable-modelock                       \
 --enable-randr                          \
 --enable-pango &&

printf "\nready to run make."
