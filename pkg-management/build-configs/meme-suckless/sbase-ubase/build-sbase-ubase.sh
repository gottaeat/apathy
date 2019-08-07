#!/bin/env bash
git clone git://git.2f30.org/sbase.git			&&
git clone git://git.2f30.org/ubase.git			&&

printf " * building sbase.\n"				&&
cd sbase						&&
patch -p1 < ../0001-sbase-config.patch			&&
make -j3 2>&1 > /dev/null				&&
doas -- make install 2>&1 > /dev/null			&&
export yes_sbase=1

printf " * building ubase.\n"				&&
cd ../ubase						&&
patch -p1 < ../0001-ubase-config.patch			&&
patch -p1 < ../0002-ubase-glibc.patch			&&
make -j3 2>&1 > /dev/null				&&
doas -- make install 2>&1 > /dev/null			&&
export yes_ubase=1

printf " * sbase=$yes_sbase\n * ubase=$yes_ubase\n" 	&&
exit 0
