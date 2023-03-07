project('init', 'c',
 version: '46',
 license: 'MIT',
 default_options: [
  'buildtype=plain',
  'prefix=/mss/init',
  'bindir=/mss/init/bin',
  'datadir=/mss/init/files',
  'c_std=c99'
 ]
)

add_global_arguments(
 [
  '--target=x86_64-apathy-linux-musl',
  '-fno-builtin',
  '-D_FILE_OFFSET_BITS=64',
  '-D_GNU_SOURCE',
  '-D_XOPEN_SOURCE=700'
 ],
  language : 'c'
)

# 1 > sources
libutil_src = [
 'src/libutil/agetcwd.c',
 'src/libutil/agetline.c',
 'src/libutil/apathmax.c',
 'src/libutil/concat.c',
 'src/libutil/ealloc.c',
 'src/libutil/eprintf.c',
 'src/libutil/estrtol.c',
 'src/libutil/estrtoul.c',
 'src/libutil/explicit_bzero.c',
 'src/libutil/passwd.c',
 'src/libutil/proc.c',
 'src/libutil/putword.c',
 'src/libutil/recurse.c',
 'src/libutil/strlcat.c',
 'src/libutil/strlcpy.c',
 'src/libutil/strtonum.c',
 'src/libutil/tty.c'
]

# 2 > targets
libutil = static_library('util', libutil_src, install: false)

executable('ctrlaltdel', 'src/ctrlaltdel.c', link_with: libutil, install: true)
executable('getty',      'src/getty.c',      link_with: libutil, install: true)
executable('halt',       'src/halt.c',       link_with: libutil, install: true)
executable('killall5',   'src/killall5.c',   link_with: libutil, install: true)
executable('login',      'src/login.c',      link_with: libutil, install: true)
executable('respawn',    'src/respawn.c',    link_with: libutil, install: true)

# 3 > files
files_bin = [
 'files/init',
 'files/ainitmgr',
 'files/setapathy'
]

files_files = [
 'files/acpi.script',
 'files/funcs',
 'files/iptables.script',
 'files/services',
 'files/udhcpc.script',
 'files/udhcpd.conf'
]

files_files_acpi = [
 'files/events'
]

install_data(files_bin,        install_dir: get_option('bindir'))
install_data(files_files,      install_dir: get_option('datadir'))
install_data(files_files_acpi, install_dir: join_paths(get_option('datadir'), 'acpi'))
