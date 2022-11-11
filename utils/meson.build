project('utils',
 version: '24',
 license: 'GPL3',
 default_options: [
  'buildtype=plain',
  'prefix=/mss',
  'bindir=/mss/bin',
  'datadir=/mss/files',
 ]
)

# 1 > files
files_bin = [
 'bin/0x0',
 'bin/cb',
 'bin/cblist',
 'bin/chr',
 'bin/cleancmake',
 'bin/cleanup',
 'bin/colortest',
 'bin/compressthinelogs',
 'bin/configtomusl',
 'bin/dn',
 'bin/fetch',
 'bin/kinst',
 'bin/ldir',
 'bin/maimclip',
 'bin/maimcrop',
 'bin/maimscrot',
 'bin/monmode',
 'bin/ossl',
 'bin/pkg',
 'bin/pkgup',
 'bin/printprof',
 'bin/setbright',
 'bin/setgov',
 'bin/setmon',
 'bin/setrotate',
 'bin/stripper',
 'bin/suspendtodisk',
 'bin/switchcompositor',
 'bin/syncboi',
 'bin/trimall',
 'bin/ttygrab'
]

files_files = [
 'files/device.conf',
 'files/funcs',
 'files/init.conf',
 'files/sourceme',
 'files/sourceme-aliases',
 'files/sourceme-build'
]

install_data(files_bin,   install_dir: get_option('bindir'))
install_data(files_files, install_dir: get_option('datadir'))
