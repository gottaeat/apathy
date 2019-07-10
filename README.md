### msslinux-pure64 build details and maintenance guide
## stuff that requires me to run periodically:
uwu i'll set a cronjob once i'm done, don't yell at me.
* `/usr/sbin/make-ca -g` --> required for the certificate stuff.
* `/usr/sbin/update-pciids` --> required for the pciutils.
* `/usr/sbin/ntpd -q -g` --> sets the clock.
* `/usr/bin/wget http://www.linux-usb.org/usb.ids -o /usr/share/hwdata/usb.ids` --> usbutils thingy.

![yes](assets/yes.jpg)

## msslinux-pure64 package+dep list
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
[d]		**** libxml2-2.9.9 --> also built python 2 module
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

[d]	* iptables-1.8.2 --> installed it, no config or init script.
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

[d]	* git-2.20.1 -> --enable-jit
[d]	** curl-7.64.0
[d]		*** c-ares-1.15.0
[d]		*** libssh2-1.8.0
[d]			**** openssh-7.9p1 --> installed it, no config or init script.
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

 !!	1. install freetype without harfbuzz ---> done
 !!	2. instal harfbuzz without cairo ---> done
 !!	3. install cairo ---> done
 !!	4. install harfbuzz with cairo ---> done
 !!	5. install freetype ---> done
 !!	6. install fontconfig ---> done

[d]	* xorg-libs
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
[d]	* xorg-apps
[d]	* font-util-1.3.1
[d]	* encodings-1.0.4

[d]	* xkeyboardconfig-2.26

[d]	* xorg-server
[d]	** libunwind-1.3.1
[d]	** libepoxy-1.5.3

	* xorg-drivers --> will use modesetting for intel
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
[d]	* cairomm-1.12.2 --> reinstalled cairo

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

 !!	1. gdk-pixbuf without librsvg --> done
 !!	2. librsvg --> done
 !!	3. gdk-pixbuf --> done

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

[d]	* firefox-60.5.2	--> esr
[d]	** autoconf-2.13
[d]	** cbindgen-0.8.0
[d]	** nodejs-10.15.1
[d]	** libwebp-1.0.2
[d]	** libproxy
[d]	** yasm
[d]	** ffmpeg-4.1.1 --> runtime
```

---------------------------------------------------------
### alsa libs and stuff:
```
[d]	* alsa-plugins-1.1.8 
[d]	** libsamplerate-0.1.9

[d]	* alsa-utils-1.1.8
[d]	** fftw-3.3.8

[d]	* alsa-tools-1.1.7.tar.bz2

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
[d]	*** directfb-1.7.7 --> recompile after sdl and v4l

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
[d]	* vim-8.1 --> xorg support
[d]	* rsync-3.1.3 --> no init or config done
[d]	** popt-1.16

[d]	* tmux

[d]	* i3
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
```
---------------------------------------------------------
#### python:
```
[d]	* pypresence
[d]	* mssrpc
```
