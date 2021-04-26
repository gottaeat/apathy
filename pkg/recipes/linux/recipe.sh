#!/mss/bin/sh
# apathy musl 1.2 - mss@tutanota.de
# build script for 5.12 kernels, version 1, for thinkpad x220 and t61.

. /mss/files/funcs

# 1 > check if variables are set
if [ -z "${1}" ]
 then aprint_fail "specify a linux tarball with \$1."; exit 1
fi

case "${2}" in
 t61)  confname="t61"  ;;
 x220) confname="x220" ;;
 *)    aprint_fail "specify either t61 or x220 as \$2."; exit 1
esac

# 2 > set script vars
  blddate="$(date "+%Y%m%d_%H%M%S")"
 storepkg="/mnt/mss/stuff/techy-bits/packaged-software/kernel/${confname}"
  repodir="/mss/repo/pkg/recipes/linux"
 saucedir="/mss/work/sauces"
  workdir="/mss/work/table"
   logdir="/mss/work/logs"

   kerver="$(printf "${1}\n" | sed 's/\.tar\.[^.]*$//;s/^linux-//')"
  makedir="${workdir}/linux-${kerver}"
 patchdir="${repodir}/patches"
      rdr="${logdir}/${blddate}-linux-${kerver}.log"

  useconf="${repodir}/files/${confname}.config"
 localver="5.12$(awk '/LOCALVERSION=/{gsub(/CONFIG_LOCALVERSION=|\"/,"");\
                      print}' ${useconf})"
  bldsalt="$(awk     '/BUILD_SALT=/{gsub(/CONFIG_BUILD_SALT=|\"/,"");    \
                      print}' ${useconf})"

# 3 > check if config exists
if [ ! -f "${useconf}" ]
 then aprint_fail "specified config does not exist."; exit 1
fi

# 4 > set make vars
unset \
 CC CXX LD AR AS NM STRIP RANLIB OBJCOPY OBJDUMP \
 OBJSIZE READELF ADDR2LINE CFLAGS CXXFLAGS LDFLAGS

mymake(){ make CC=x86_64-apathy-linux-musl-gcc -j$(($(nproc)+1)) "$@";}

# 5 > print details
clear; aprint_nc
lsdetail "release " "${kerver}  "
lsdetail "machine " "${confname}"
lsdetail "localver" "${localver}"
lsdetail "details " "${bldsalt} "

# 6 > unpack the kernel
if [ ! -f "${saucedir}/${1}" ]
 then aprint_fail "tarball does not exist."; exit 1
 else
  aprint_nc; aprint_ret "unpacking the kernel sauce."
   tar xf ${saucedir}/${1} --directory="${workdir}" >> "${rdr}" 2>&1
  evalretkill
fi

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
  aprint_ret "${cb_blu}$(echo $pp | awk '{gsub(/^.*\//,""); print}')${c_res}"
   patch -p1 < "${pp}" >> "${rdr}" 2>&1
  evalretkill
 done

# 10 > run menuconfig
aprint_nc; aprint_ask "run menuconfig for manual config? (y/n): "
read answermenuconf

case "$answermenuconf" in
 yes|Y|y) aprint "running menuconfig.";     mymake menuconfig ;;
 *)       aprint "not running menuconfig."; aprint_nc         ;;
esac

# 11 > run make
aprint_ask "run make? (y/n): "
read answerbuildkern

case "$answerbuildkern" in
 yes|Y|y)
  aprint "current date is ${cl_grn}$(date '+%a %d %I:%M:%S%P')${c_res}."
  aprint "redirecting output to ${cl_grn}${rdr}${c_res}."
  datebefore=$(date +%s)

  aprint_ret "running make."; mymake >> "${rdr}" 2>&1
  evalretkill

  dateafter=$(date +%s)
  timespent=$(($dateafter - $datebefore))
  humantime=$(printf "%dd %dh %dm\n"                      \
              "$(echo "${timespent}/86400"        | bc)"  \
              "$(echo "(${timespent}%86400)/3600" | bc)"  \
              "$(echo "(${timespent}%3600)/60"    | bc)")
  
  aprint "build finished in ${cl_grn}${humantime}${c_res}."
 ;;
 *) aprint "not running make."; aprint_nc; exit 0 ;;
esac

# 12 > install kernel
aprint_nc; aprint_ask "install the built kernel? (y/n): "
read answerkinst

case "${answerkinst}" in
 yes|Y|y)
  aprint "installing the built kernel."
   doas cp -v arch/x86/boot/bzImage /boot/vmlinuz    >> "${rdr}" 2>&1 &&
   doas cp -v System.map            /boot/System.map >> "${rdr}" 2>&1 &&
   doas cp -v .config               /boot/config     >> "${rdr}" 2>&1

  aprint_ret "running ${cl_grn}lilo${c_res}."
   doas -- lilo >> "${rdr}" 2>&1
  evalret
 ;;
 *) aprint "not installing the built kernel." ;;
esac

# 13 > package up the built kernel
aprint_nc; aprint_ask "package up the built kernel? (y/n): "
read answerpkgup

case "${answerpkgup}" in
 yes|Y|y)
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
aprint_nc; aprint_ask "clean up the work directory? (y/n): "
read answerclean

case "${answerclean}" in
 yes|Y|y) aprint_ret "cleaning up the workdir."; rm -rf ${makedir}; evalret ;;
 *)       aprint "not cleaning up the workdir."; exit 0                     ;;
esac
