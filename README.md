### msslinux-pure64 build details
mssLinux is a hobby project based on lfs+blfs 8.4 books, it's the product of my negative feelings, loneliness and lack of interest in everything  but terminals.

in its current state, it's fully 64bit. i at some point tried a multilib build as well but it got out of control very fast. i don't play games therefore i don't need steam or wine so i don't really need the 32 bit garbage those two need.

this is the 3rd fully fledged linux from scratch based build i've built in the last 45 days.

**current package count**: 385

![yes](assets/fetch.png)

#### stuff that requires me to run periodically:
uwu i'll set a cronjob once i'm done, don't yell at me.
* `/usr/sbin/make-ca -g` ---> required for the certificate stuff.
* `/usr/sbin/update-pciids` ---> required for the pciutils.
* `/usr/sbin/ntpd -q -g` ---> sets the clock.
* `/usr/bin/wget http://www.linux-usb.org/usb.ids -o /usr/share/hwdata/usb.ids` ---> usbutils thingy.

### package+dep list
#### security
```
[d]	* make-ca
[d]	** p11-kit-0.23.15
[d]	*** nss-3.42.1
[d]	**** nspr-4.20
[d]	*** libtasn1-4.13
[d]	*** libxslt-1.1.33
[d]		**** libgcrypt-1.8.4
[d]			***** libgpg-error-1.35
[d]			***** pth-2.0.7
[d]		**** libxml2-2.9.9 ---> also built python 2 module
[d]			***** python-2.7.15 
[d]			****** sqlite-3.27.1
[d]		**** docbook-xml-4.5
[d]			***** sgml-common-0.6.3
[d]			***** unzip-6.0 
[d]		**** docbook-xsl-1.79.2
[d]			***** zip-3.0 
[d]			***** ruby-2.6.1
[d]			****** yaml-0.2.1
[d]			****** berkeley db-5.3.28
[d]			******* tcl-8.6.9
```
#### stuff
```
[d]	* wget-1.20.1
[d]	** pcre-8.42
[d]	** libpsl-0.20.2
[d]	*** libidn2-2.1.1
[d]		**** libunistring-0.9.10
[d]	** gnutls-3.6.6
[d]	*** nettle-3.4.1

[d]	* iptables-1.8.2 ---> installed it, no config or init script.
[d]	* dosfstools-4.1 

[d]	* lsof-4.91
[d]	** libtirpc-1.1.4

[d]	* cpio-2.12

[d]	* lm_sensors-3.4.0
[d]	** which-2.21

[d]	* unrar-5.7.2
[d]	* sysstat-12.1.2

[d]	* pciutils-3.6.2

[d]	* ntp-4.2.8p12
[d]	** io-socket-ssl-2.062
[d]	*** net-ssleay-1.86_06
[d]	*** uri-1.76

[d]	* git-2.20.1				--> --enable-jit
[d]	** curl-7.64.0
[d]		*** c-ares-1.15.0
[d]		*** libssh2-1.8.0
[d]			**** openssh-7.9p1	--> installed it, no config or init script.
[d]		*** nghttp2-1.36.0
[d]			**** boost-1.69.0
[d]			***** icu-63.1
[d]			**** jansson-2.12
[d]			**** libevent-2.1.8
[d]			**** libev-4.25-1
[d]			**** cython

[d]	* sudo-1.8.27
```
---------------------------------------------------------
### xorg stuff:
```
[d]	* util-macros-1.19.2
[d]	* xorgproto-2018.4
[d]	* libxau-1.0.9 
[d]	* libxdmcp-1.1.2
[d]	* xcb-proto-1.13
[d]	* libxcb

[d]	* fontconfig
[d]	** freetype
[d]	*** libpng
[d]	*** harfbuzz
[d]		**** cairo-1.16.0
[d]			***** pixman-0.38.0
[d]		**** glib-2.58.3
[d]	*****r gobject-introspection-1.58.3
[d]	*****r shared-mime-info-1.10
[d]	*****r desktop-file-utils-0.23

 !!	1. install freetype without harfbuzz	--> done
 !!	2. instal harfbuzz without cairo	--> done
 !!	3. install cairo			--> done
 !!	4. install harfbuzz with cairo		--> done
 !!	5. install freetype			--> done
 !!	6. install fontconfig			--> done

[d]     * xtrans-1.3.5
[d]     * libX11-1.6.7
[d]     * libXext-1.3.3
[d]     * libFS-1.0.7
[d]     * libICE-1.0.9
[d]     * libSM-1.2.3
[d]     * libXScrnSaver-1.2.3
[d]     * libXt-1.1.5
[d]     * libXmu-1.1.2
[d]     * libXpm-3.5.12
[d]     * libXaw-1.0.13
[d]     * libXfixes-5.0.3
[d]     * libXcomposite-0.4.4
[d]     * libXrender-0.9.10
[d]     * libXcursor-1.1.15
[d]     * libXdamage-1.1.4
[d]     * libfontenc-1.1.3
[d]     * libXfont2-2.0.3
[d]     * libXft-2.3.2
[d]     * libXi-1.7.9
[d]     * libXinerama-1.1.4
[d]     * libXrandr-1.5.1
[d]     * libXres-1.2.0
[d]     * libXtst-1.2.3
[d]     * libXv-1.0.11
[d]     * libXvMC-1.0.10
[d]     * libXxf86dga-1.1.4
[d]     * libXxf86vm-1.1.4
[d]     * libdmx-1.1.4
[d]     * libpciaccess-0.14
[d]     * libxkbfile-1.0.9
[d]     * libxshmfence-1.3

[d]	* xcb-util-0.4.0
[d]	* xcb-util-image-0.4.0 
[d]	* xcb-util-keysyms-0.4.0 
[d]	* xcb-util-renderutil-0.3.9
[d]	* xcb-util-wm-0.4.1 
[d]	* xcb-util-cursor-0.1.3

[d]	* mesa-18.3.6
[d]	** libdrm-2.4.97 
[d]	** libvdpau-1.1.1 
[d]	** mako-1.0.7
[d]		*** markupsafe-1.1.0

[d]	* xbitmaps-1.1.2
[d]     * iceauth-1.0.8
[d]     * luit-1.1.1
[d]     * mkfontdir-1.0.7
[d]     * mkfontscale-1.1.3
[d]     * sessreg-1.1.1
[d]     * setxkbmap-1.3.1
[d]     * smproxy-1.0.6
[d]     * x11perf-1.6.0
[d]     * xauth-1.0.10
[d]     * xbacklight-1.2.2
[d]     * xcmsdb-1.0.5
[d]     * xcursorgen-1.0.7
[d]     * xdpyinfo-1.3.2
[d]     * xdriinfo-1.0.6
[d]     * xev-1.2.2
[d]     * xgamma-1.0.6
[d]     * xhost-1.0.7
[d]     * xinput-1.6.2
[d]     * xkbcomp-1.4.2
[d]     * xkbevd-1.1.4
[d]     * xkbutils-1.0.4
[d]     * xkill-1.0.5
[d]     * xlsatoms-1.1.2
[d]     * xlsclients-1.1.4
[d]     * xmessage-1.0.5
[d]     * xmodmap-1.0.9
[d]     * xpr-1.0.5
[d]     * xprop-1.2.3
[d]     * xrandr-1.5.0
[d]     * xrdb-1.1.1
[d]     * xrefresh-1.0.6
[d]     * xset-1.2.4
[d]     * xsetroot-1.1.2
[d]     * xvinfo-1.1.3
[d]     * xwd-1.0.7
[d]     * xwininfo-1.1.4
[d]     * xwud-1.0.5

[d]	* font-util-1.3.1
[d]	* encodings-1.0.4

[d]	* xkeyboardconfig-2.26

[d]	* xorg-server-1.20.3
[d]	** libunwind-1.3.1
[d]	** libepoxy-1.5.3

[d]	* xorg-drivers			--> will use modesetting for intel
[d]	** libevdev 
[d]	** xf86-input-evdev-2.10.6
[d]	*** mtdev-1.1.5
[d]	** libinput-1.12.6
[d]	** xf86-input-libinput-0.28.2
[d]	** xf86-video-fbdev-0.5.0
[d]	** libva-2.4.0 
[d]	** intel-vaapi-driver-2.3.0

[d]	* xinit-1.4.0
```
---------------------------------------------------------
### compilers and languages:
```
[d]	* llvm-7.0.1 + clang + compiler-rt
[d]	** cmake-3.13.4
[d]	*** libuv-1.26.0
[d]	*** libarchive-3.3.3
[d]	**** lzo-2.10

[d]	* rustc-1.32.0
[d]	* lua-5.3.5
[d]	* luajit 2.0.5-2
	
[d]	* usbutils-010
[d]	** libusb-1.0.22
```
---------------------------------------------------------
### gui related stuff:
```
[d]	* atk-2.30.0
[d]	* atkmm-2.28.0
[d]	** glibmm-2.58.0
[d]	*** libsigc++-2.10.1

[d]	* at-spi2-core-2.30.0 
[d]	** dbus-1.12.12

[d]	* at-spi2-atk-2.30.0
[d]	* cairomm-1.12.2	--> reinstalled cairo

[d]	* freeglut-3.0.0 
[d]	** glu-9.0.0

[d]	* gdk-pixbuf-2.38.0
[d]	** libjpeg-turbo-2.0.2
[d]	*** nasm-2.14.02
[d]	** librsvg-2.44.12
[d]	*** libcroco-0.6.12
[d]	*** pango-1.42.4
[d]		**** fribidi-1.0.5
[d]	*** vala-0.42.5
[d]	** libtiff-4.0.10

 !!	1. gdk-pixbuf without librsvg	--> done
 !!	2. librsvg			--> done
 !!	3. gdk-pixbuf			--> done

[d]	* gtk+-2.24.32

[d]	* gtk+-3.24.5
[d]	** adwaita-icon-theme-3.30.1
[d]	** iso codes-4.1
[d]	** libxkbcommon-0.8.3

[d]	* gtksourceview

[d]	* imlib2-1.5.1 
[d]	** giflib-5.1.6
[d]		*** xmlto-0.0.28 
[d]	** libid3tag

[d]	* libnotify-0.7.7
[d]	** notification-daemon-3.20.0
[d]	*** libcanberra-0.30
[d]		**** alsa-lib-1.1.8
[d]		**** libvorbis-1.3.6
[d]		***** libogg-1.3.3

[d]	* rxvt-unicode-9.22
[d]	* transmission-2.94

[d]	* lxappearance-0.6.3
[d]	** dbus-glib-0.110

[d]	* w3m-git
[d]	** gc-8.0.2
[d]	*** libatomic_ops-7.6.8
[d]	** gpm-1.20.7

[d]	* firefox-66.5		--> /opt install
[d]	** autoconf-2.13
[d]	** cbindgen-0.8.0
[d]	** nodejs-10.15.1
[d]	** libwebp-1.0.2
[d]	** libproxy
[d]	** yasm
[d]	** ffmpeg-4.1.1		--> runtime
```

---------------------------------------------------------
### alsa libs and stuff:
```
[d]	* alsa-plugins-1.1.8 
[d]	** libsamplerate-0.1.9

[d]	* alsa-utils-1.1.8
[d]	** fftw-3.3.8

[d]	* alsa-tools-1.1.7

[d]	* audiofile-0.3.6 
[d]	** flac-1.3.2

[d]	* faad2-2.8.8
[d]	* id3lib-3.8.3
[d]	* libass-0.14.0
[d]	* libmad-0.15.1b 

[d]	* libmpeg2-0.5.1
[d]	** sdl-1.2.15
[d]	*** aalib-1.4rc5
[d]		**** slang 2.3.2
[d]	*** libcaca 0.99.beta19
[d]	*** directfb-1.7.7 	--> recompiled after sdl and v4l

[d]	* libvpx-1.8.0 
[d]	* opus-1.3
[d]	* sdl2-2.0.9
[d]	* taglib-1.11.1
[d]	* v4l-utils-1.16.5
[d]	* x264-20190209-2245
[d]	* x265-3.0
```
---------------------------------------------------------
#### random garbage i forgot to install
```
[d]	* tree-1.8.0
[d]	* vim-8.1		--> xorg support
[d]	* rsync-3.1.3		--> no init or config done
[d]	** popt-1.16

[d]	* tmux

[d]	* ~~ i3 ~~		--> replaced with i3-memegaps.
[d]	** yajl
[d]	** xcb-util-xrm

[d]	* i3blocks
[d]	* dmenu

[d]	* nitrogen
[d]	** gtkmm-2.24.5
[d]	*** pangomm-2.42.0

[d]	* scrot
[d]	** giblib

[d]	* xtrlock

[d]	* apulse
[d]	* discord
[d]	* discord-rpc
[d]	* youtube-dl

[d]	* compton
[d]	** libconfig
[d]	** asciidoc2

[d]	* mc-4.8.22

[d]	* ffmpeg-4.1.1
[d]	** lame-3.100
[d]	** OpenJPEG-2.3.0

[d]	* neofetch
[d]	* numlockx

[d]	* mpv

[d]	* mpd
[d]	** libcue
[d]	** mpg123
[d]	** libmpdclient
[d]	** libupnp
[d]	** shout

[d]	* mpc
[d]	* ncmpcpp

[d]	* htop
[d]	** strace
[d]	** libnl

[d]	* iftop
[d]	** libpcap-1.9.0

[d]	* xdg-utils-1.1.3 

[d]	* elinks	--> binary from arch
[d]	** tre
[d]	** liblua5.1.5	--> binary from arch
[d]	** libidn-1.35

[d]	* zsh-5.7.1
[d]	* expect-5.45.4 
[d]	* lz4

[d]	* libnetfilter_queue
[d]	** libmnl
[d]	** libnfnetlink

[d]	* feh

[d]	* maim
[d]	** slop
[d]	*** glm 	
[d]	*** glew

[d]	* xclip

[d]	* imagemagick-7.0.8-27
[d]	** little-cms-2.9

[d]	* irssi
```
---------------------------------------------------------
#### python:
```
[d]	* pypresence
[d]	* mssrpc
```
---------------------------------------------------------
#### lfs-8.4 base
```
[d] man-pages-4.16
[d] glibc-2.29
[d] zlib-1.2.11
[d] file-5.36
[d] readline-8.0
[d] m4-1.4.18
[d] bc-1.07.1
[d] binutils-2.32
[d] gmp-6.1.2
[d] mpfr-4.0.2
[d] mpc-1.1.0
[d] shadow-4.6
[d] gcc-8.2.0
[d] bzip2-1.0.6
[d] pkg-config-0.29.2
[d] ncurses-6.1
[d] attr-2.4.48
[d] acl-2.2.53
[d] libcap-2.26
[d] sed-4.7
[d] psmisc-23.2
[d] iana-etc-2.30
[d] bison-3.3.2
[d] flex-2.6.4
[d] grep-3.3
[d] bash-5.0
[d] libtool-2.4.6
[d] gdbm-1.18.1
[d] gperf-3.1
[d] expat-2.2.6
[d] inetutils-1.9.4
[d] perl-5.28.1
[d] xml::parser-2.44
[d] intltool-0.51.0
[d] autoconf-2.69
[d] automake-1.16.1
[d] xz-5.2.4
[d] kmod-26
[d] gettext-0.19.8.1
[d] libelf from elfutils-0.176
[d] libffi-3.2.1
[d] openssl-1.1.1a
[d] python-3.7.2
[d] ninja-1.9.0
[d] meson-0.49.2
[d] coreutils-8.30
[d] check-0.12.0
[d] diffutils-3.7
[d] gawk-4.2.1
[d] findutils-4.6.0
[d] groff-1.22.4
[d] less-530
[d] gzip-1.10
[d] iproute2-5.0.0
[d] kbd-2.0.4
[d] libpipeline-1.5.1
[d] make-4.2.1
[d] patch-2.7.6
[d] man-db-2.8.5
[d] tar-1.31
[d] texinfo-6.5
[d] vim-8.1
[d] procps-ng-3.3.15
[d] util-linux-2.33.1
[d] e2fsprogs-1.44.5
[d] sysklogd-1.5.1
[d] sysvinit-2.93
[d] eudev-3.2.7
```
