### sources used:
```
# https://pkgs.alpinelinux.org
# http://linuxfromscratch.org/blfs/view/9.0
# https://github.com/rancher/buildroot
# https://github.com/dslm4515/bmlfs
# https://github.com/gentoo/libressl
```
```
[d]	> opendoas-git			--> 27-sep-2019 snapshot
[d]	> ca-certificates-20190110
[r]	> wget-1.20.3
[d]	> iptables-1.8.3
[d]	> lsof-4.93.2

[d]	> lm_sensors-3.4.0
[d]	>> which-2.21
[d]	>> sysfsutils-2.1.0

[d]	> sysstat-12.1.6
[d]	> curl-7.66.0
[d]	> ntp-4.2.8p13

[d]	> git-2.23.0
[d]	>> expat-2.2.8
[d]	>> pcre2-10.33
[d]	>>> libedit-20190324.3.1

[d]	> openssh-8.0p1
[d]	> libssh2-1.9.0

[d]	> cmake-3.15.3
[d]	>> libuv-1.32.0
[d]	>> libarchive-3.4.0

[d]	> unzip60-libre

[d]	> usbutils-012
[d]	>> libusb-1.0.23

[d]	> lua-5.3.5
[d]	> gpm-1.20.7
[d]	> tree-1.8.0

[d]	> rsync-3.1.3
[d]	>> popt-1.16

[d]	> tmux-3.0a
[d]	>> libevent-2.1.11

[d]	> htop-2.2.0
[d]	> strace-5.0		--> 5.2 fails to build, screams about v4l.
[d]	> libnl-1.1.4

[d]	> iftop-0.17
[d]	>> libpcap-1.9.0

[d]	> links-0.13-20150624
[d]	>> lua51-5.1.5
[d]	>> tre-0.8.0
[d]	>> libidn-1.35
[d]	>> js185
[d]	>>> zip30
[d]	>>> nss-3.46
[d]	>>>> nspr-4.22
[d]	>>> python-2.7.16

[d]	> gnupg-2.2.17
[d]	>> npth-1.6
[d]	>> libgpg-error-1.36
[d]	>> libassuan-2.5.3
[d]	>> libgcrypt-1.8.5
[d]	>> libksba-1.3.5
[d]	>> pinentry-1.1.0		--> depends on glib, wait for x.
[d]	>> gnutls-3.6.10
[d]	>>> libtasn1-4.14
[d]	>>> libunistring-0.9.10
[d]	>>> nettle-3.5.1
[d]	>>> p11-kit-0.23.17

[d]	> openvpn-2.4.7
[d]	>> lzo-2.10

[d]	> jq-1.6			--> binary from dev.
[d]	> dnscrypt-proxy-2.0.31		--> binary from dev.

[d]	> start-stop-daemon		--> github.com/daleobrien/start-stop-daemon
```
```
### xorg fuckery

[d]	> util-macros-1.19.2
[d]	> xorgproto-2019.2
[d]	> libxau-1.0.9 
[d]	> libxdmcp-1.1.3
[d]	> xcb-proto-1.13
[d]	> libxcb-1.13.1

# xml garbage
[d]	> libxslt-1.1.33
[d]	>> libxml2-2.9.9		--> withy python3 modules
[d]	>> docbook-xml-4.5
[d]	>>> sgml-common-0.6.3
[d]	>> docbook-xsl-1.79.2
# xml garbage end

# someone fucking shoot me
 !! freetype without harfbuzz	--> done.
 !! harfbuzz			--> done.
 !! rebuild freetype		--> done.
 !! build cairo			--> done.
 !! rebuild harfbuzz		--> done.
 !! rebuild freetype		--> done.
 !! build fontconfig		--> done.
 !! rebuild cairo		--> done.

[d]	> fontconfig-2.13.1 
[d]	>> freetype-2.10.1
[d]	>>> libpng-1.6.37
[d]	>>> harfbuzz-2.6.4
[d]		>>>> glib-2.62.0
[d]			>>>>> pcre-8.43
[d]		>>>> icu-64.2
[d]		>>>> gobject-introspection-1.62.0
[d]		>>>> shared-mime-info-1.12
[d]		>>>> desktop-file-utils-0.24
[d]		>>>> cairo-1.17.2+f93fc72c03e
[d]			>>>>> pixman-0.38.4
# someone fucking shoot me end

# xorg libs
# alias fm='./configure $XORG_CONFIG  && make && doas -- make install && echo done && cd ..'
# alias fn='./configure --prefix=/usr --sysconfdir=/etc --localstatedir=/var --disable-static && make && doas -- make install && echo done && cd ..'

[d]	> xtrans-1.4.0
[d]	> libX11-1.6.9
[d]	> libXext-1.3.4
[d]	> libFS-1.0.8
[d]	> libICE-1.0.10
[d]	> libSM-1.2.3
[d]	> libXScrnSaver-1.2.3
[d]	> libXt-1.2.0
[d]	> libXmu-1.1.3
[d]	> libXpm-3.5.12
[d]	> libXaw-1.0.13
[d]	> libXfixes-5.0.3
[d]	> libXcomposite-0.4.5
[d]	> libXrender-0.9.10
[d]	> libXcursor-1.2.0
[d]	> libXdamage-1.1.5
[d]	> libfontenc-1.1.4
[d]	> libXfont2-2.0.4
[d]	> libXft-2.3.3
[d]	> libXi-1.7.10
[d]	> libXinerama-1.1.4
[d]	> libXrandr-1.5.2
[d]	> libXres-1.2.0
[d]	> libXtst-1.2.3
[d]	> libXv-1.0.11
[d]	> libXvMC-1.0.12
[d]	> libXxf86dga-1.1.5
[d]	> libXxf86vm-1.1.4
[d]	> libdmx-1.1.4
[d]	> libpciaccess-0.16
[d]	> libxkbfile-1.1.0
[d]	> libxshmfence-1.3
# xorg libs end

[d]	> xcb-util-0.4.0
[d]	> xcb-util-image-0.4.0
[d]	> xcb-util-keysyms-0.4.0
[d]	> xcb-util-renderutil-0.3.9
[d]	> xcb-util-wm-0.4.1
[d]	> xcb-util-cursor-0.1.3

[d]	> mesa-19.3.1
[d]	>> libdrm-2.4.99
[d]	>> libvdpau-1.2
[d]	>> mako-1.0.14
[d]	>>> markupsafe-1.1.1

# xorg apps
[d]	> xbitmaps-1.1.2 
[d]	> iceauth-1.0.8
[d]	> luit-1.1.1
[d]	> mkfontdir-1.0.7
[d]	> mkfontscale-1.2.1
[d]	> sessreg-1.1.2
[d]	> setxkbmap-1.3.2
[d]	> smproxy-1.0.6
[d]	> x11perf-1.6.1
[d]	> xauth-1.1
[d]	> xbacklight-1.2.3
[d]	> xcmsdb-1.0.5
[d]	> xcursorgen-1.0.7
[d]	> xdpyinfo-1.3.2
[d]	> xdriinfo-1.0.6
[d]	> xev-1.2.3
[d]	> xgamma-1.0.6
[d]	> xhost-1.0.8
[d]	> xinput-1.6.3
[d]	> xkbcomp-1.4.2
[d]	> xkbevd-1.1.4
[d]	> xkbutils-1.0.4
[d]	> xkill-1.0.5
[d]	> xlsatoms-1.1.3
[d]	> xlsclients-1.1.4
[d]	> xmessage-1.0.5
[d]	> xmodmap-1.0.10
[d]	> xpr-1.0.5
[d]	> xprop-1.2.4
[d]	> xrandr-1.5.1.tar.xz
[d]	> xrdb-1.2.0
[d]	> xrefresh-1.0.6
[d]	> xset-1.2.4
[d]	> xsetroot-1.1.2
[d]	> xvinfo-1.1.4
[d]	> xwd-1.0.7
[d]	> xwininfo-1.1.5
[d]	> xwud-1.0.5
# xorg apps end

# xorg font
[d]	> font-util-1.3.2
[d]	> encodings-1.0.4
# xorg font end

[d]	> xkeyboard-config-2.27

[d]	> xorg-server-1.20.5
[d]	>> libunwind-1.2.1
[d]	>> libepoxy-1.5.3

# xorg drivers
[d]	> xf86-input-evdev-2.10.6
[d]	>> libevdev-1.8.0
[d]	>> mtdev-1.1.5

[d]	> xf86-input-libinput-0.29.0
[d]	>> libinput-1.14.1

[d]	> xf86-video-fbdev-0.5.0

[d]	> libva-2.5.0
[d]	> intel-vaapi-driver-2.3.0
# xorg drivers end
[d]	> xinit-1.4.1
### xorg fuckery end
```
```
### gui fuckery
[d]	> atk-2.34.1
[d]	> atkmm-2.28.0
[d]	>> glibmm-2.60.0
[d]	>>> libsigc++-2.10.2

[d]	> freeglut-3.0.0
[d]	>> glu-9.0.1

[d]	> gdk-pixbuf-2.38.2
[d]	>> libjpeg-turbo-2.0.2
[d]	>>> nasm-2.14.02
nope	>> librsvg
[d]	>>> libcroco-0.6.13
[d]	>>> pango-1.42.4
[d]	>>>> fribidi-1.0.5
[d]	>>> vala-0.44.7
[d]	>> tiff-4.0.10

[d]	> gtk+-2.24.32			--> rebuild cairo for the xlib backend
[d]	> libxkbcommon-0.8.4

[d]	> imlib2-1.5.1
[d]	>> giflib-5.2.1
[r]	>>> xmlto-0.0.28 
[d]	>> libid3tag-0.15.1b
### gui fuckery end
```
```
[r]	> rxvt-unicode-9.22
[r]	> transmission-2.94
[d]	> autoconf-2.13
[d]	> libwebp-1.0.3
[d]	> yasm-1.3.0
```
```
### audio libraries and codecs
[d]	> alsa-lib-1.1.9

[d]	> libvorbis-1.3.6
[d]	>> libogg-1.3.4

[d]	> alsa-plugins-1.1.9
[d]	>> libsamplerate-0.1.9

[d]	> alsa-utils-1.1.8
[d]	>> fftw-3.3.8

[d]	> audiofile-0.3.6 
[d]	>> flac-1.3.3

[d]	> faad2-2.9.0
[d]	> id3lib-3.8.3
[d]	> libass-0.14.0
[d]	> libmad-0.15.1b

[d]	> libmpeg2-0.5.1		dont build deps fuckhaedf

nope	> sdl-1.2.15-libre
[r]	>> libcaca-0.99.beta19
[r]	>> directfb-1.7.7

[d]	> libvpx-1.8.1 
[d]	> opus-1.3.1
nope	> sdl2-2.0.10
[d]	> taglib-1.11.1
[d]	> x264-20190815-2245
[d]	> x265-3.1.2
```
```
[r]	> i3-gaps-4.17.1
[r]	>> libev-4.27
[r]	>> yajl-2.1.0
[r]	>> xcb-util-xrm-1.3
[r]	>> startup-notification-0.12

[r]	> i3blocks-1.4
[d]	> dmenu-4.9
[d]	> xtrlock-2.11

[d]	> youtube-dl-2019.11.28

[r]	> compton-0.1_beta2
[r]	>> libconfig-1.7.2
[r]	>> libxdg-basedir-1.2.0

[d]	> ffmpeg-4.2.1
[d]	>> lame-3.100
[d]	>> openjpeg-2.3.1

[d]	> numlockx-1.2
[d]	> mpv-0.29.1

[d]	> mpd-0.21.10
[d]	>> sqlite-3.29.0
[d]	>> libcue-2.2.1
[d]	>> mpg123-1.25.12
[d]	>> libmpdclient-2.16
[d]	>> libupnp-1.8.4
[d]	>> libshout-2.4.3
[d]	>> boost-1.69.0

[d]	> mpc-0.32
[d]	> ncmpcpp-0.8.2
nope	> xdg-utils-1.1.3		--> xmlto is being racist against ash, remove both.

[d]	> maim-5.5.3
[d]	>> slop-7.4
[d]	>>> glm-0.9.9.6
[d]	>>> glew-2.1.0

[d]	> xclip-0.13

[d]	> imagemagick-7.0.8.64
[d]	>> lcms2-2.9

[d]	> weechat-2.6
[d]	> feh-3.2.1

[d]	> mupdf-1.16.1
[d]	>> jbig2dec-0.16

[d]	> gpgme-1.13.1
[d]	> mutt-1.12.1
[d]	> lzip-1.21

[d]	> apathy-browser-28.8.0

[d]	> gcompat-0.4.0
[d]	>> libucontext-0.1.3

[d]	> sfeed-git
[d]	> vifm-0.10.1
[d]	> grub-2.04
[d]	> fim-0.5-rc3
[d]	> trackma-git			--> 5 oct 2019 snapshot
[d]	> slmenu-0.1
[d]	> apathy-st-0.8.2
[d]	> lz4-1.9.2
[d]	> cwm				--> from github.com/leahneukirchen/cwm
[d]	> lemonbar			--> from github.com/krypt-n/bar
[d]	> wmctrl-1.07
[d]	> partclone-0.3.12
[d]	> aria-1.35.0
```
```
### base mlfs packages
[d]	 argp-standalone-1.3
[d]	 attr-2.4.48
[d]	 autoconf-2.69
[d]	 automake-1.16.1
[d]	 bc-2.4.0			--> from github.com/gavinhoward/bc
[d]	 binutils-2.33.1
[d]	 bison-3.4.2
[d]	 busybox-1.31.1
[d]	 bzip2-1.0.8
[d]	 check-0.12.0
[d]	 coreutils-8.31
[d]	 cpio-2.12
[d]	 diffutils-3.7
[d]	 e2fsprogs-1.45.3
[d]	 elfutils-0.176
[d]	 eudev-3.2.8
[d]	 expat-2.2.8
[d]	 file-5.37
[d]	 findutils-4.6.0
[d]	 flex-2.6.4
[d]	 gawk-5.0.1
[d]	 gcc-9.2.1-20191221
[d]	 gdbm-1.18.1
[d]	 gettext-0.20.1
[d]	 gmp-6.1.2
[d]	 gperf-3.1
[d]	 grep-3.3
[d]	 groff-1.22.4
[d]	 gzip-1.10
[d]	 iana-etc-2.30
[d]	 inetutils-1.9.4
[d]	 intltool-0.51.0
[d]	 iproute2-5.3.0
[d]	 isl-0.21
[d]	 kbd-2.2.0
[d]	 kmod-26
[d]	 less-551
[d]	 libcap-2.27
[d]	 libffi-3.2.1
[d]	 libpipeline-1.5.1
[d]	 libressl-3.0.2
[d]	 libtool-2.4.6
[d]	 linux-5.2.17
[d]	 lzip-1.21
[d]	 m4-1.4.18
[d]	 make-4.2.1
[d]	 meson-0.51.2
[d]	 mpc-1.1.0
[d]	 mpfr-4.0.2
[d]	 musl-1.1.24
[d]	 musl-fts-1.2.7
[d]	 musl-obstack-1.1
[d]	 ncurses-6.1
[d]	 ninja-1.9.0
[d]	 patch-2.7.6
[d]	 perl-5.30.0
[d]	 pkg-config-0.29.2
[d]	 procps-ng-3.3.15
[d]	 psmisc-23.2
[d]	 python-3.7.4
[d]	 readline-8.0
[d]	 sed-4.7
[d]	 shadow-4.7
[d]	 sysklogd-1.5.1
[d]	 sysvinit-2.96
[d]	 tar-1.32
[d]	 texinfo-6.6
[d]	 tzdb-2019c.tar.lz
[d]	 util-linux-2.34
[d]	 vim-8.2.23-git-2019-12-19
[d]	 xml-parser-2.44
[d]	 xz-5.2.4
[d]	 yash-2.49
[d]	 zlib-1.2.11
### base mlfs packages end
```
