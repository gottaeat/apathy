#!/mss/bin/sh
# apathy-musl 1.1 - mss@waifu.club
# build script for gcc9 snapshots, version 2.

. /mss/bin/apathy-funcs

# a >> check if variables are set
if	[ -z $1 ]; then aprint_fail "no gcc version specified, exiting."; exit 1;
elif	[ -z $2 ]; then aprint_fail "no isl version specified, exiting."; exit 1;
fi

# b1 >> set script vars
saucedir="/mss/work/sauces"
patchdir="/mss/repo/pkg-management/build-configs/sys-toolchain/gcc/patches"
export CFLAGS="${CFLAGS} -march=native -mtune=native"
export CXXFLAGS="${CXXFLAGS} -march=native -mtune=native"

_gccver="${1}"
_islver="${2}"
_build="x86_64-apathy-linux-musl"

# b2 >> set the configuring func
_configure(){
libat_cv_have_ifunc=no                             \
../configure                                       \
 --prefix=/usr                                     \
 --build=${_build}                                 \
 --with-bugurl="https://github.com/mssx86/apathy"  \
 --with-pkgversion="apathy"                        \
 --with-isl                                        \
 --with-system-zlib                                \
 --disable-multilib                                \
 --disable-nls                                     \
 --disable-symvers                                 \
 --disable-libmpx                                  \
 --disable-libmudflap                              \
 --disable-libsanitizer                            \
 --disable-werror                                  \
 --disable-fixed-point                             \
 --disable-libstdcxx-pch                           \
 --enable-linker-build-id                          \
 --enable-checking=release                         \
 --enable-languages=c,c++                          \
 --enable-__cxa_atexit                             \
 --enable-default-pie                              \
 --enable-default-ssp                              \
 --enable-shared                                   \
 --enable-threads                                  \
 --enable-tls                                      \
 --mandir=/usr/share/man                           \
 --infodir=/usr/share/info                         \
  >>/tmp/gcc-build.log 2>&1
}

# c1 >> print versions
aprint_nc
lsdetail "gcc version" "${_gccver}"
lsdetail "isl version" "${_islver}"
lsdetail "build"       "${_build}"
aprint_nc
lsdetail "cflags"      "${CFLAGS}"
lsdetail "cxxflags"    "${CXXFLAGS}"
aprint_nc

# c2.1 >> extract gcc sauce
if [ ! -f "${saucedir}/${_gccver}.tar.xz" ]
 then
  aprint_fail "gcc tarball does not exist in saucedir, exiting."; exit 1
 else
  aprint_ret "${c_blue}extracting${c_reset}\t: the ${c_lcyan}gcc source${c_reset} to current directory."
   tar xf "${saucedir}"/"${_gccver}".tar.xz >/tmp/gcc-build.log 2>&1
  evalretkill
  
  cd ${_gccver}
fi

# c2.2 >> extract isl sauce
if [ ! -f "${saucedir}/${_islver}.tar.xz" ]
 then
  aprint_fail "isl tarball does not exist in saucedir, exiting."; exit 1
 else
  aprint_ret "${c_blue}extracting${c_reset}\t: the ${c_lcyan}isl source${c_reset} to current directory."
  tar xf "${saucedir}"/"${_islver}".tar.xz >>/tmp/gcc-build.log 2>&1
  evalretkill

  mv -v "${_islver}" "isl" >>/tmp/gcc-build.log 2>&1
fi 

# d1 >> change the default libdir to /lib from /lib64
aprint_nc
aprint_ret "running sed to change the default libdir to ${c_lcyan}/lib${c_reset}."
 sed -i '/m64=/s/lib64/lib/' gcc/config/i386/t-linux64
 sed -i 's/lib64/lib/'       gcc/config/i386/linux64.h
evalretkill

# d2 >> _FORTIFY_SOURCE needs an optimization level.
aprint_ret "${c_lcyan}_FORTIFY_SOURCE${c_reset} needs an optimization level."
 sed -i "/ac_cpp=/s/\$CPPFLAGS/\$CPPFLAGS -O2/" gcc/configure libiberty/configure
evalretkill

# e >> create build dir
aprint_nc
aprint_ret "creating the ${c_lcyan}build${c_reset} directory."
 mkdir -v build >>/tmp/gcc-build.log 2>&1
 cd build
evalretkill

# f >> running the configure 
aprint_ret "running the ${c_lcyan}configure${c_reset} script."
 _configure
evalretkill

# g >> run make
aprint_nc
aprint_ask "run make? (y/n): "
read answerbuildgcc

if [ "$answerbuildgcc" != "${answerbuildgcc#[Yy]}" ]
 then
  aprint_ret "running make, tail -f /tmp/gcc-build.log to view."
   make -j$(($(nproc)+1)) >>/tmp/gcc-build.log 2>&1
  evalretkill

  aprint_nc
  aprint "build complete."
 else
  aprint "not running make."
  aprint_nc
  exit 0
fi
