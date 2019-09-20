#!/mss/bin/sh
. /mss/bin/apathy-funcs

aprint_nc
aprint_ret "running sed, install 64bit libs to /usr/lib."
 sed -e '/m64=/s/lib64/lib/' -i.orig gcc/config/i386/t-linux64
evalretkill

aprint_ret "making and changing to build directory."
 mkdir build && cd build
evalretkill

aprint_ret "configuring gcc."
../configure			\
    --prefix=/usr		\
    --disable-multilib		\
    --with-system-zlib		\
    --enable-languages=c,c++	\
    --enable-linker-build-id	>>/tmp/gcc-build.tmp 2>&1
evalretkill
aprint_nc
aprint "feel free to run make now."
aprint "cd to the build dir first."
aprint_nc
