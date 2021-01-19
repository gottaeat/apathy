### basic explanation of the format used here:
```
[ ] text	> package-version		(notes)
 │  │
 │  └─────────────> source of the build recipe.
 │
 ├─> d: done ─────> currently installed to the local system.
 ├─> b: busybox ──> symlinked to busybox.
 ├─> r: removed ──> simply removed. 
 └─> o: ondemand ─> this package got built and archived. only unarchived
                    when it is needed.
```
```
[d] self	> opendoas-6.8
[r] bmlfs	> ca-certificates-20190110
[d] self	> iptables-1.8.4
[d] alpine	> lsof-4.93.2

[d] alpine	> lm_sensors-3.6.0
[d] alpine	>> sysfsutils-2.1.0

[d] alpine	> sysstat-12.2.0
[d] self	> curl-7.74.0

[d] self	> git-2.29.2
[d] alpine	>> pcre2-10.34
[d] alpine	>>> libedit-20191231.3.1

[d] self	> openssh-8.4_p1
[d] self	> libssh2-1.9.0

[d] self	> cmake-3.17.1
[d] alpine	>> libuv-1.34.1
[d] self	>> libarchive-3.4.1

[d] alpine	> usbutils-012
[d] alpine	>> libusb-1.0.23		(without --disable-udev)

[d] arch	> lua-5.2.4
[d] alpine	> gpm-1.20.7
[d] alpine	> tree-1.8.0

[d] alpine	> rsync-3.1.3
[d] alpine	>> popt-1.16

[d] alpine	> tmux-3.0a
[d] self	>> libevent-2.1.11

[d] self	> htop-3.0.2
[d] alpine	> strace-5.4
[d] alpine	> libnl-1.1.4

[d] alpine	> iftop-0.17
[d] alpine	>> libpcap-1.9.1		(without ipv6 support)

[d] alpine	> libidn-1.35

[r] blfs	> nss-3.49.1
[r] alpine	>> nspr-4.24
[d] alpine	>> sqlite-3.30.1

[d] self	> python-2.7.17

[d] alpine	> gnupg-2.2.19
[d] alpine	>> npth-1.6
[d] alpine	>> libgpg-error-1.36
[d] alpine	>> libassuan-2.5.3
[d] alpine	>> libgcrypt-1.8.5
[d] alpine	>> libksba-1.3.5
[d] alpine	>> pinentry-1.1.0		(tty only)
[d] self	>> gnutls-3.6.15
[d] alpine	>>> libtasn1-4.15
[d] alpine	>>> libunistring-0.9.10
[d] alpine	>>> nettle-3.5.1		(without --disable-openssl)
[d] alpine	>>> p11-kit-0.23.18.1

[d] self	> openvpn-2.4.9
[d] alpine	>> lzo-2.10

[d] self	> jq-1.6
[d] devbin	> dnscrypt-proxy-2.0.44
[r] self	> start-stop-daemon		(from github.com/daleobrien/start-stop-daemon)
```
```
### xorg stack
[d] bmlfs	> util-macros-1.19.2
[d] bmlfs	> xorgproto-2019.2
[d] bmlfs	> libxau-1.0.9 
[d] bmlfs	> libxdmcp-1.1.3
[d] bmlfs	> xcb-proto-1.13
[d] bmlfs	> libxcb-1.13.1

# xml
[r] bmlfs	> libxslt-1.1.33
[r] bmlfs	>> docbook-xml-4.5
[r] bmlfs	>>> sgml-common-0.6.3
[r] bmlfs	>> docbook-xsl-1.79.2
# xml end

[d] self	> libxml2-2.9.10

# warn: freetype -> harfbuzz -> freetype -> fontconfig -> cairo
[d] self	> fontconfig-2.13.93
[d] self	>> freetype-2.10.4
[d] bmlfs	>>> libpng-1.6.37
[d] self	>>> harfbuzz-2.7.3
[d] self	>>>> glib-2.64.2
[d] bmlfs	>>>>> pcre-8.43
[r] bmlfs	>>>> icu-65.1
[r] bmlfs	>>>> gobject-introspection-1.60.2
[r] bmlfs	>>>> shared-mime-info-1.12
[r] bmlfs	>>>> desktop-file-utils-0.24

[d] self	> cairo-1.17.2+f93fc72c03e
[d] bmlfs	>> pixman-0.40.0
# warn end

# xorg libs
# alias fm='./configure $XORG_CONFIG && make && doas -- make install && \
#           echo done && cd .. && rm -rf * && ls -lahw1'
[d] self	> xtrans-1.4.0
[d] self	> libX11-1.7.0
[d] self	> libXext-1.3.4
[d] self	> libICE-1.0.10
[d] self	> libSM-1.2.3
[d] self	> libXt-1.2.0
[d] self	> libXmu-1.1.3
[d] self	> libXpm-3.5.13
[d] self	> libXaw-1.0.13
[d] self	> libXfixes-5.0.3
[d] self	> libXcomposite-0.4.5
[d] self	> libXrender-0.9.10
[d] self	> libXcursor-1.2.0
[d] self	> libXdamage-1.1.5
[d] self	> libfontenc-1.1.4
[d] self	> libXfont2-2.0.4
[d] self	> libXft-2.3.3
[d] self	> libXi-1.7.10
[d] self	> libXinerama-1.1.4
[d] self	> libXrandr-1.5.2
[d] self	> libXres-1.2.0
[d] self	> libXtst-1.2.3
[d] self	> libXv-1.0.11
[d] self	> libXvMC-1.0.12
[d] self	> libXxf86dga-1.1.5
[d] self	> libXxf86vm-1.1.4
[d] self	> libdmx-1.1.4
[d] self	> libpciaccess-0.16
[d] self	> libxkbfile-1.1.0
[d] self	> libxshmfence-1.3
[d] self	> libXScrnSaver-1.2.3
# xorg libs end

[d] self	> xcb-util-0.4.0
[d] self	> xcb-util-image-0.4.0
[d] self	> xcb-util-keysyms-0.4.0
[d] self	> xcb-util-renderutil-0.3.9
[d] self	> xcb-util-wm-0.4.1
[d] self	> xcb-util-cursor-0.1.3

[d] self	> mesa-20.2.6
[d] alp+bmlfs	>> libdrm-2.4.100		(patch from alpine, recipe from bmlfs)
[r] bmlfs	>> libvdpau-1.2
[d] bmlfs	>> mako-1.1.1
[d] bmlfs	>>> markupsafe-1.1.1

# xorg apps
[d] self	> xbitmaps-1.1.2
[d] self	> iceauth-1.0.8
[d] self	> luit-1.1.1
[d] self	> mkfontscale-1.2.1
[d] self	> sessreg-1.1.2
[d] self	> setxkbmap-1.3.2
[d] self	> xauth-1.1
[d] self	> xbacklight-1.2.3
[d] self	> xcmsdb-1.0.5
[d] self	> xdpyinfo-1.3.2
[d] self	> xdriinfo-1.0.6
[d] self	> xev-1.2.3
[d] self	> xhost-1.0.8
[d] self	> xinput-1.6.3
[d] self	> xkbcomp-1.4.2
[d] self	> xkbevd-1.1.4
[d] self	> xkbutils-1.0.4
[d] self	> xkill-1.0.5
[d] self	> xmessage-1.0.5
[d] self	> xmodmap-1.0.10
[d] self	> xpr-1.0.5
[d] self	> xprop-1.2.4
[d] self	> xrandr-1.5.1
[d] self	> xrdb-1.2.0
[d] self	> xrefresh-1.0.6
[d] self	> xset-1.2.4
[d] self	> xsetroot-1.1.2
[d] self	> xvinfo-1.1.4
[d] self	> xwd-1.0.7
[d] self	> xwininfo-1.1.5
[d] self	> xwud-1.0.5
# xorg apps end

# xorg font
[d] self	> font-util-1.3.2
[d] self	> encodings-1.0.5
# xorg font end

[d] self	> xkeyboard-config-2.28

[d] self	> xorg-server-1.20.10
[r] bmlfs	>> libunwind-1.3.1
[d] bmlfs	>> libepoxy-1.5.3

# xorg drivers
[d] bmlfs	> xf86-input-evdev-2.10.6
[d] bmlfs	>> libevdev-1.8.0
[d] bmlfs	>> mtdev-1.1.5

[d] bmlfs	> xf86-input-libinput-0.29.0
[d] bmlfs	>> libinput-1.15.0

[d] bmlfs	> xf86-input-synaptics-1.9.1
[d] bmlfs	> libva-2.10.0
[d] bmlfs	> intel-vaapi-driver-2.4.0
[r] self	> xf86-video-intel-846b53
# xorg drivers end

[d] alpine	> xinit-1.4.1

### xorg stack end
```
```
### gui
[d] self	> atk-2.36.0
[d] bmlfs	> atkmm-2.28.0
[d] bmlfs	>> glibmm-2.60.0
[d] bmlfs	>>> libsigc++-2.10.2

[d] bmlfs	> freeglut-3.2.1
[d] bmlfs	>> glu-9.0.1

[d] self	> gdk-pixbuf-2.40.0
[d] self	>> libjpeg-turbo-2.0.5
[d] bmlfs	>>> nasm-2.14.02
[r] bmlfs	>> libcroco-0.6.13
[d] self	>> pango-1.42.4
[d] bmlfs	>>> fribidi-1.0.8
[r] bmlfs	>> vala-0.46.5
[d] bmlfs	>> tiff-4.1.0

[r] self	> gtk+-2.24.32
[d] bmlfs	> libxkbcommon-0.8.4

[d] bmlfs	> imlib2-1.6.1
[d] alpine 	>> giflib-5.2.1
[d] alpine	>>> xmlto-0.0.28 
[d] alpine	>> libid3tag-0.15.1b
### gui end
```
```
[d] bmlfs	> autoconf-2.13
[d] bmlfs	> libwebp-1.0.3
[d] self	> yasm-1.3.0
```
```
### audio libs
[d] self	> alsa-lib-1.2.3.1

[d] alpine	> libvorbis-1.3.6
[d] alpine	>> libogg-1.3.4

[d] self	> alsa-plugins-1.2.2
[d] alpine	>> libsamplerate-0.1.9

[d] self	> alsa-utils-1.2.3
[r] bmlfs	>> fftw-3.3.8

[d] alpine	> audiofile-0.3.6 
[d] bmlfs	>> flac-1.3.3

[d] alpine	> faad2-2.9.1
[d] alpine	> id3lib-3.8.3
[d] alpine	> libass-0.14.0
[d] alpine	> libmad-0.15.1b
[d] alpine	> libmpeg2-0.5.1
[d] bmlfs	> libvpx-1.8.2
[d] bmlfs	> opus-1.3.1
[d] bmlfs	> taglib-1.11.1
[d] self	> x264-20191119-2245
[d] self	> x265-3.4
### audio libs end
```
```
[d] self	> dmenu-4.9
[d] self	> xtrlock-2.11
[d] self	> youtube-dl-2020.12.07

[d] self	> compton-5.1			(-Dconfig_file=false -Ddbus=false)
[d] alpine	>> libev-4.31

[d] self	> ffmpeg-4.3.1
[d] alpine	>> lame-3.100
[d] alpine	>> openjpeg-2.3.1

[d] alpine	> numlockx-1.2
[d] self	> mpv-0.33.0

[d] self	> mpd-0.21.10
[d] alpine	>> libcue-2.2.1
[d] alpine	>> mpg123-1.25.13
[d] self	>> libmpdclient-2.18
[d] alpine	>> libupnp-1.8.4
[d] self	>> libshout-2.4.3
[o] self	>> boost-1.75.0

[d] self	> mpc-0.33
[d] self	> ncmpcpp-0.9.1

[d] self	> maim-5.5.3
[d] self	>> slop-7.4
[r] self	>>> glm-0.9.9.6
[d] self	>>> glew-2.1.0

[d] alpine	> xclip-0.13

[d] self	> imagemagick-7.0.10.23
[d] alpine	>> lcms2-2.9

[r] self	> weechat-2.7
[d] alpine	> feh-3.3

[d] self	> mupdf-1.16.1
[d] alpine	>> jbig2dec-0.17		(without --without-libpng)

[d] alpine	> gpgme-1.13.1
[r] alpine	> mutt-1.13.3
[d] alpine	> lzip-1.21

[r] self	> apathy-browser-28.11.0
[d] alpine	>> zip-30

[d] self	> gcompat-1.0.0
[d] self	>> libucontext-0.11

[d] self	> sfeed-git			(from git.codemadness.org/sfeed)
[d] self	> vifm-0.10.1
[d] self	> fim-0.5-rc3
[d] self	> trackma-git			(20200117 snapshot)
[d] self	> slmenu-0.1
[d] self	> apathy-st-0.8.4
[d] alpine	> lz4-1.9.2
[r] self	> cwm				(from github.com/leahneukirchen/cwm)
[r] self	> lemonbar			(from github.com/krypt-n/bar)
[r] self	> wmctrl-1.07			(patches from void, recipe from alpine)
[r] self	> aria2-1.35.0
[d] self	> links-2.20.2

[d] self	> wpa_supplicant-2.9
[d] alpine	>> libnl3-3.5.0

[d] self	> lilo-24.2
[d] arch	>> bin86-0.16.21

[r] alpine	> i3wm-gaps-4.17.1
[r] alpine	>> yajl-2.1.0
[r] alpine	>> xcb-util-xrm-1.3
[r] alpine	>> startup-notification-0.12

[r] self	> i3blocks-1.4
[d] alpine	> samurai-1.2
[d] self	> dwm-6.2
[d] self	> irssi-1.2.2

[r] arch-aur	> zathura-ypb-0.0.8.2
[r] alpine	>> poppler-0.82.0

[r] self	> mawk-1.3.4-20200120
[r] self	> star-1.6
[r] self	> go-1.14.1
```
```
### llvm
[d] self	> llvm-11.0.1
[d] self	> clang-11.0.1
[d] self	> lld-11.0.1
[d] self	> polly-11.0.1
[d] self	> libunwind-11.0.1
[d] self	> libcxxabi-11.0.1
[d] self	> libcxx-11.0.1
[d] self	> compiler-rt-11.0.1
### llvm end
```
```
[d] self	> firefox-78.6.1esr
[d] self	>> nodejs-15.5.1
[d] self	>> cbindgen-0.16.0
[d] self	>>> rustc-1.49.0
[d] self	>> gtk+-3.24.24

[d] self	> sinit-1.1-apathy
[d] self	> zstd-1.4.8
[r] self	> qemu-4.2.0
[d] alpine	> cuetools-1.4.1
[d] alpine	> shntool-3.0.10
[d] self	> earlyoom-1.6.1-apathy
[d] alpine	> xdelta3-3.1.0
[d] self	> transmission-3.0
[o] self	> ruby-2.7.1
[d] self	> mkvtoolnix-48.0.0
[d] self	> pciutils-3.7.0
[d] self	> thinkfan-1.2.1
[d] self	> apulse-0f9f8487
[d] self	> isl-0.22
[d] self	> fdupes-2.1.2
[d] self	> ympd-612f8fc0

[d] self	> nfs-utils-2.5.2
[d] self	>> libtirpc-1.3.1
[d] self	>> rpcbind-1.2.5

[d] self	> openssl-1.1.1i
```
```
### busybox
[d] self	> busybox-1.33.0
[b] busybox	>> acpid
[b] busybox	>> ash
[b] busybox	>> bash
[b] busybox	>> bootchartd
[b] busybox	>> cpio
[b] busybox	>> crond
[b] busybox	>> crontab
[b] busybox	>> cttyhack
[b] busybox	>> dos2unix
[b] busybox	>> dpkg
[b] busybox	>> dpkg-deb
[b] busybox	>> fbsplash
[b] busybox	>> hdparm
[b] busybox	>> httpd
[b] busybox	>> klogd
[b] busybox	>> man
[b] busybox	>> mkdosfs
[b] busybox	>> mkfs.vfat
[b] busybox	>> mt
[b] busybox	>> ntpd
[b] busybox	>> rpm
[b] busybox	>> rpm2cpio
[b] busybox	>> sh
[b] busybox	>> syslogd
[b] busybox	>> time
[b] busybox	>> uname
[b] busybox	>> unix2dos
[b] busybox	>> unzip
[b] busybox	>> uudecode
[b] busybox	>> uuencode
[b] busybox	>> vi
[b] busybox	>> wget
[b] busybox	>> which
```
```
### base mlfs packages
[d] mlfs	> acl-2.2.53
[d] mlfs	> argp-standalone-1.3
[d] mlfs	> attr-2.4.48
[d] self	> autoconf-2.70
[d] self	> automake-1.16.3
[d] mlfs	> bc-2.4.0
[d] self	> binutils-2.35.1
[d] self	> bison-3.7.4
[d] mlfs	> bzip2-1.0.8
[d] mlfs	> check-0.12.0
[d] self	> coreutils-8.32
[d] self	> diffutils-3.7
[d] self	> e2fsprogs-1.45.6
[d] mlfs	> elfutils-0.176
[d] self	> eudev-3.2.9
[d] alpine	> expat-2.2.9
[d] mlfs	> file-5.37
[d] self	> findutils-4.8.0
[d] mlfs	> flex-2.6.4
[d] self	> gawk-5.1.0
[d] self	> gcc-10.2.1-20210116
[d] mlfs	> gdbm-1.18.1
[r] mlfs	> gettext-0.20.1
[d] self	> gmp-6.2.1
[d] mlfs	> gperf-3.1
[d] self	> grep-3.6
[d] mlfs	> groff-1.22.4
[r] mlfs	> grub-2.04
[d] mlfs	> gzip-1.10
[d] mlfs	> iana-etc-2.30
[d] mlfs	> inetutils-1.9.4
[r] mlfs	> intltool-0.51.0
[d] mlfs	> iproute2-5.4.0
[d] mlfs	> kbd-2.2.0
[d] mlfs	> kmod-26
[d] self	> less-563
[d] mlfs	> libcap-2.27
[d] mlfs	> libffi-3.2.1
[d] mlfs	> libpipeline-1.5.1
[r] self	> libressl-3.3.1
[d] mlfs	> libtool-2.4.6
[d] mlfs	> m4-1.4.18
[d] alpine	> make-4.3
[d] mlfs	> meson-0.54.1
[d] self	> mpc-1.2.1
[d] self	> mpfr-4.1.0
[d] self	> musl-1.2.2
[d] mlfs	> musl-fts-1.2.7
[d] mlfs	> musl-obstack-1.1
[d] self	> ncurses-6.2
[r] mlfs	> ninja-1.9.0
[d] mlfs	> patch-2.7.6
[d] mlfs	> perl-5.30.1
[d] mlfs	> pkg-config-0.29.2
[d] mlfs	> procps-ng-3.3.15
[d] mlfs	> psmisc-23.2
[d] self	> python-3.8.2
[d] self	> readline-8.1
[d] alpine	> sed-4.8
[d] mlfs	> shadow-4.7
[r] mlfs	> sysklogd-1.5.1
[r] mlfs	> sysvinit-2.96
[d] self	> tar-1.3.3
[r] mlfs	> texinfo-6.6
[d] mlfs	> tzdb-2019c
[d] self	> util-linux-2.35
[d] mlfs	> vim-8.2.0116
[d] mlfs	> xml-parser-2.44
[d] mlfs	> xz-5.2.4
[d] self	> yash-2.50 
[d] mlfs	> zlib-1.2.11
### base mlfs packages end
```
