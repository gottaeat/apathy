#!/bin/env bash
echo " * applying patches:"
patch -p1 < ../patches/gtk+-3.22.20-libcloudproviders-automagic.patch && echo done && 
patch -p1 < ../patches/gtk+-atk-bridge-config.ac.patch && echo done && 
patch -p1 < ../patches/gtk+-atk-bridge-config.h.in.patch && echo done && 
patch -p1 < ../patches/gtk+-atk-bridge-gtkaccessibility.patch && echo done && 

echo " * applied patches succesfully." &&
echo " * manipulating ./configure." && autoreconf -fv && echo " * updated ./configure succesfully."
echo " * configuring:" &&

./configure --prefix=/usr             \
            --sysconfdir=/etc         \
            --enable-broadway-backend \
            --enable-x11-backend      \
            --without-atk-bridge      \
            --disable-cloudproviders  \
            --disable-mir-backend     \
            --disable-papi && echo done &&
echo " * configured successfully." &&
echo " * ready to run make."
