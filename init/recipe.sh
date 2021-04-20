#!/mss/bin/sh -e
. /mss/files/funcs
. /mss/files/sourceme-build

repodir="/mss/repo"
initdir="/mss/init"

buildboi(){
         CFLAGS="${CFLAGS} -g0 -std=c99 -D_FILE_OFFSET_BITS=64"
 export  CFLAGS="${CFLAGS} -D_XOPEN_SOURCE=700 -D_GNU_SOURCE"
 export LDFLAGS="${LDFLAGS} -s"

 lutilsrc="agetcwd agetline apathmax concat ealloc eprintf estrtol     \
           estrtoul explicit_bzero passwd proc putword recurse strlcat \
           strlcpy strtonum tty" 
 ubasesrc="ctrlaltdel getty halt killall5 login respawn"

 aprint_nc
 aprint "${cb_grn}building${c_res}"

 aprint_ret "[1/6] ${cb_red}creating ${cb_blu}: ${cb_whi}build/ + out/${c_res}"
  mkdir -p build/libutil out/
 evalretkill

 aprint_ret "[2/6] ${cb_red}building ${cb_blu}: ${cb_whi}libutil objects${c_res}"
  for i in ${lutilsrc}; do
   ${CC} ${CFLAGS} -o build/libutil/${i}.o -c src/libutil/${i}.c
  done
 evalretkill

 aprint_ret "[3/6] ${cb_red}creating ${cb_blu}: ${cb_whi}libutil.a${c_res}"
  ${AR} qc  build/libutil.a build/libutil/*.o
  ${RANLIB} build/libutil.a
 evalretkill

 aprint_ret "[4/6] ${cb_red}building ${cb_blu}: ${cb_whi}ubase objects${c_res}"
  for i in ${ubasesrc}; do
   ${CC} ${CFLAGS} -o build/${i}.o -c src/${i}.c
  done
 evalretkill

 aprint_ret "[5/6] ${cb_red}linking  ${cb_blu}: ${cb_whi}ubase programs${c_res}"
  for i in ${ubasesrc}; do
   ${CC} ${LDFLAGS} -o out/${i} build/${i}.o build/libutil.a
  done
 evalretkill

 aprint_ret "[6/6] ${cb_red}building ${cb_blu}: ${cb_whi}init${c_res}"
  for i in init; do
   ${CC} ${CFLAGS}  -o build/${i}.o -c src/${i}.c &&
   ${CC} ${LDFLAGS} -o out/$i build/${i}.o
  done
 evalretkill

 aprint_nc
}

installboi(){
 aprint_nc
 if [ ! -f out/ctrlaltdel ] \
 || [ ! -f out/getty      ] \
 || [ ! -f out/halt       ] \
 || [ ! -f out/init       ] \
 || [ ! -f out/killall5   ] \
 || [ ! -f out/login      ] \
 || [ ! -f out/respawn    ]
  then
   aprint_ret "one or more binaries are missing in out/, run install() first."
    failprompt; aprint_nc; exit 1
  fi

 aprint "${cb_grn}creating directories${c_res}"
 if [ -d "${initdir}" ]; then
  aprint_ret "removing the ${cb_whi}old init${c_res}"
   rm -rf "${initdir}"
  evalret
 fi

 aprint_ret "creating ${cb_whi}${initdir}${c_res}"
  mkdir -p "${initdir}"
 evalret

 aprint_nc
 aprint "${cb_grn}installing the init${c_res}"
 aprint_ret "${cb_whi}init/bin${c_res}"
  cp -rf "${repodir}"/init/bin   "${initdir}"
 evalret

 aprint_ret "${cb_whi}init/files${c_res}"
  cp -rf "${repodir}"/init/files "${initdir}"
 evalret

 aprint_ret "${cb_whi}init/rc${c_res}"
  cp -rf "${repodir}"/init/rc    "${initdir}"
 evalret

 aprint_nc
 aprint "${cb_grn}installing binaries${c_res}"
 for i in out/*; do
  aprint_ret "${cb_whi}$(echo ${i} | sed 's/^.*\///')${c_res}"
   cp -f ${i} /mss/init/bin
  evalret
 done

 aprint_nc
}

cleanboi(){
 aprint_nc
 aprint "${cb_grn}cleaning${c_res}"
  for i in build/ out/; do
   aprint_ret "${cb_whi}${i}${c_res}"
    rm -rf "${i}"
   evalretkill
  done

 aprint_nc
}

case "${1}" in
 build)   buildboi                             ;;
 install) installboi                           ;;
 clean)   cleanboi                             ;;
 *)       aprint_usage "{build|install|clean}" ;;
esac
