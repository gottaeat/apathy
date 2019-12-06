#!/mss/bin/sh
# apathy-musl 1.1 - mss@waifu.club
# build script for stable gcc-9.2.0.

. /mss/bin/apathy-funcs

# a >> check if variables are set
if	[ -z $1 ]; then aprint_fail "no gcc version specified, exiting."; exit 1;
elif	[ -z $2 ]; then aprint_fail "no isl version specified, exiting."; exit 1;
fi

# b1 >> set script vars
saucedir="/mss/work/sauces"
patchdir="/mss/repo/pkg-management/build-configs/sys-toolchain/gcc/patches"

_gccver="${1}"
_islver="${2}"

_build="x86_64-apathy-linux-musl"
_host="x86_64-apathy-linux-musl"
_target="x86_64-apathy-linux-musl"

# b2.1 >> set the patch applying func
apply_patches(){
 _patches_Np1="libgnarl-musl.patch"
 _patches_Np0="
  0010-ldbl128-config.patch
  ada-shared.patch
  darn.patch
  fix-cxxflags-passing.patch
  fix-musl-execinfo.patch
  gccgo-musl.patch
  invalid_tls_model.patch
  libffi_gnulinux.patch
  libgcc-musl-ldbl128-config.patch
  musl-ada.patch
  no-stack_chk_fail_local.patch
  omp.patch
  ppc64-pure64.patch"

 for pp in $_patches_Np0
  do
   aprint_ret "${c_blue}applying${c_reset}\t:${c_lcyan} ${pp}${c_reset}."
   patch -Np0 -i "${patchdir}"/9.2.0/"${pp}" >>/tmp/gcc-build.log 2>&1
   evalretkill
  done

 for pp in $_patches_Np1
  do
   aprint_ret "${c_blue}applying\t${c_reset}:${c_lcyan} ${pp}${c_reset}."
   patch -Np1 -i "${patchdir}"/9.2.0/"${pp}" >>/tmp/gcc-build.log 2>&1
   evalretkill
  done
}

# b2.2 >> set the configuring func
_configure(){
CFLAGS=" -pipe" \
CXXFLAGS=" -pipe" \
SED=sed \
libat_cv_have_ifunc=no \
../configure \
 --prefix=/usr \
 --build=${_build} \
 --host=${_host} \
 --target=${_target} \
 --with-pkgversion="apathy-musl 1.1" \
 --with-bugurl="https://mss.neocities.org/apathy/" \
 --with-system-zlib \
 --with-isl \
 --with-linker-hash-style=gnu \
 --enable-languages=c,c++ \
 --enable-threads=posix \
 --enable-clocale=generic \
 --enable-tls \
 --enable-libstdcxx-time \
 --enable-fully-dynamic-string \
 --enable-default-pie \
 --enable-default-ssp \
 --enable-vtable-verify \
 --enable-linker-build-id \
 --enable-fast-character \
 --disable-libstdcxx-pch \
 --disable-nls \
 --disable-multilib \
 --disable-symvers \
 --disable-libsanitizer \
 --disable-target-libiberty \
 --disable-libunwind-exceptions \
 --enable-checking=release \
  >>/tmp/gcc-build.log 2>&1
}

# c1 >> print versions
aprint_nc
aprint "${c_blue}gcc${c_reset}\t\t: ${c_lcyan}${_gccver}${c_reset}."
aprint "${c_blue}isl${c_reset}\t\t: ${c_lcyan}${_islver}${c_reset}."
aprint_nc
aprint "${c_blue}host${c_reset}\t\t: ${c_lcyan}${_host}${c_reset}."
aprint "${c_blue}build${c_reset}\t: ${c_lcyan}${_build}${c_reset}."
aprint "${c_blue}target${c_reset}\t: ${c_lcyan}${_target}${c_reset}."
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

# d1 >> apply the patches
aprint_nc
aprint "applying the patches."
apply_patches

# d2.1 >> change the default libdir to /lib from /lib64
aprint_nc
aprint_ret "running sed to change the default libdir to ${c_lcyan}/lib${c_reset}."
 sed -e '/m64=/s/lib64/lib/' -i.orig gcc/config/i386/t-linux64
evalretkill

# d.2 >> _FORTIFY_SOURCE needs an optimization level.
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

  make -j$(($(nproc)+1)) \
   CFLAGS=" -pipe" CXXFLAGS=" -pipe" >>/tmp/gcc-build.log 2>&1
  evalretkill

  aprint_nc
  aprint "build complete."
 else
  aprint "not running make."
  aprint_nc
  exit 0
fi
