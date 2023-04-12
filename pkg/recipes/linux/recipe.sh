#!/mss/bin/sh
# apathy musl 1.2 - mss@tutanota.de
# build script for 6.2 kernels, version 3, for all machines running apathy.

. /mss/files/funcs

# 1 > first stage checks
if [ -z "${1}" ]; then
 aprint_fail "specify a linux tarball with \$1."; exit 1
fi

# 2 > set script vars
  blddate="$(date "+%Y%m%d_%H%M%S")"
 storepkg="/mnt/mss/stuff/techy-bits/packaged-software/kernel/unified/"
  repodir="/mss/repo/pkg/recipes/linux"
 saucedir="/mss/work/sauces"
  workdir="/mss/work/table"
   logdir="/mss/work/logs"

   kerver="$(printf "${1}\n" | sed 's/\.tar\.[^.]*$//;s/^linux-//')"
  makedir="${workdir}/linux-${kerver}"
 patchdir="${repodir}/patches"
      rdr="${logdir}/${blddate}-linux-${kerver}.log"

  useconf="${repodir}/files/unified.config"
 localver="6.2$(awk '/LOCALVERSION=/{gsub(/CONFIG_LOCALVERSION=|\"/,"");\
                      print}' ${useconf})"
  bldsalt="$(awk    '/BUILD_SALT=/{gsub(/CONFIG_BUILD_SALT=|\"/,"");    \
                      print}' ${useconf})"

# 3 > set make vars
unset \
 CC CXX LD AR AS NM STRIP RANLIB OBJCOPY OBJDUMP \
 OBJSIZE READELF ADDR2LINE CFLAGS CXXFLAGS LDFLAGS

if [ -z "${MAKEFLAGS}" ];
 then MAKEFLAGS="-j$(nproc) V=0"
 else
  case "${MAKEFLAGS}" in
   *V=1*) export MAKEFLAGS="$(echo "${MAKEFLAGS}" | sed 's/V=1/V=0/g')" ;
  esac
fi

export LD_PRELOAD="/opt/mimalloc/lib/libmimalloc.so"

mymake(){ make LLVM=1 LLVM_IAS=1 "$@";}

# 4 > check if config exists
if [ ! -f "${useconf}" ]; then
 aprint_fail "specified config does not exist."; exit 1
elif [ ! -f "${saucedir}/${1}" ]; then
 aprint_fail "tarball does not exist."; exit 1
fi

# 5 > print details
clear; aprint_nc
lsdetail "release  " "${kerver}   "
lsdetail "machine  " "unified     "
lsdetail "localver " "${localver} "
lsdetail "details  " "${bldsalt}  "
lsdetail "makeflags" "${MAKEFLAGS}"

# 6 > unpack the kernel
aprint_nc
aprint_ret "unpacking the kernel sauce."
 tar xf ${saucedir}/${1} --directory="${workdir}" >> "${rdr}" 2>&1
evalretkill

# 7 > run mrproper
aprint_ret "running mrproper"
 cd "${makedir}"; mymake mrproper >> "${rdr}" 2>&1
evalretkill

# 8 > copy config
aprint_ret "copying the kernel config stated above."
 cp -v "${useconf}" "${makedir}"/.config >> "${rdr}" 2>&1
evalretkill

# 9 > apply patches
aprint_nc
aprint "applying ${cl_grn}patches${c_res}."
 for pp in "${patchdir}"/*.patch; do
  aprint_ret "${cb_blu}$(echo ${pp} | awk '{gsub(/^.*\//,""); print}')${c_res}"
   patch -p1 < "${pp}" >> "${rdr}" 2>&1
  evalretkill
 done

# 10 > run nconfig
aprint_nc
aprint_ask "run nconfig for manual config? (y/n): "
read answermenuconf

case "${answermenuconf}" in
 yes|Y|y) aprint "running nconfig.";     mymake nconfig ;;
 *)       aprint "not running nconfig."; aprint_nc      ;;
esac

# 11 > run make
aprint_ask "run make? (y/n): "
read answerbuildkern

case "${answerbuildkern}" in
 yes|Y|y)
  aprint "current date is ${cl_grn}$(date '+%a %d %I:%M:%S%P')${c_res}."
  aprint "redirecting output to ${cl_grn}${rdr}${c_res}."
  datebefore=$(date +%s)

  aprint_ret "running make."; mymake >> "${rdr}" 2>&1
  evalretkill

  dateafter=$(date +%s)
  timespent=$((${dateafter} - ${datebefore}))
  humantime=$(printf "%dd %dh %dm\n"                      \
              "$(echo "${timespent}/86400"        | bc)"  \
              "$(echo "(${timespent}%86400)/3600" | bc)"  \
              "$(echo "(${timespent}%3600)/60"    | bc)")

  aprint "build finished in ${cl_grn}${humantime}${c_res}."
 ;;
 *) aprint "not running make."; aprint_nc; exit 0 ;;
esac

# 12 > install kernel
aprint_nc
aprint_ask "install the built kernel? (y/n): "
read answerkinst

case "${answerkinst}" in
 yes|Y|y)
  aprint "calling ${cl_grn}kinst${c_res}."
  doas -- kinst y >/dev/null 2>&1
 ;;
 *) aprint "not installing the built kernel." ;;
esac

# 13 > package up the built kernel
aprint_nc
aprint_ask "package up the built kernel? (y/n): "
read answerpkgup

case "${answerpkgup}" in
 yes|Y|y)
  if [ ! -d "${storepkg}" ]; then
   aprint_ret "creating storepkg dir for the unified kernel builds."
    mkdir -pv "${storepkg}" >> "${rdr}" 2>&1
   evalret
  fi

  aprint_ret "packaging up the built kernel."
   pkglocalver="$(awk '/LOCALVERSION=/{gsub(/CONFIG_LOCALVERSION=|\"/,"");\
                       print}' ${makedir}/.config)"
   archivename="${blddate}-${kerver}${pkglocalver}.tar"

   cp -v "${makedir}/.config"               "${makedir}/config"  >> "${rdr}" 2>&1 &&
   cp -v "${makedir}/arch/x86/boot/bzImage" "${makedir}/vmlinuz" >> "${rdr}" 2>&1 &&

   tar cfvp "${archivename}" config System.map vmlinuz           >> "${rdr}" 2>&1 &&

   zstd --rm -v -19 "${archivename}" -o  "${archivename}".zst    >> "${rdr}" 2>&1 &&
   mv        -v     "${archivename}".zst "${storepkg}"/          >> "${rdr}" 2>&1
  
  evalret
 ;;
 *) aprint "not running pkgup." ;;
esac


# 14 > clean up the work directory.
aprint_nc
aprint_ask "clean up the work directory? (y/n): "
read answerclean

case "${answerclean}" in
 yes|Y|y) aprint_ret "cleaning up the workdir."; rm -rf "${makedir}"; evalret ;;
 *)       aprint "not cleaning up the workdir."; exit 0                       ;;
esac
