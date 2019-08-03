### env variables
export ZSH="/home/mss/.oh-my-zsh"
export ZSH_DISABLE_COMPFIX="true"

# path and lang
export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/opt/bin:/mss/bin"
export ROOTPATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/opt/bin"
export LANG="en_US.utf8"

# stuff taken from gentoo
export GCC_SPECS=""
export LESS="-R -M --shift 5"
export OPENGL_PROFILE="xorg-x11"
export GSETTINGS_BACKEND="dconf"

# compile bits
export MAKEFLAGS="V=0 -j 3"

# default programs
export EDITOR="/usr/bin/vim"
export PAGER="/usr/bin/less"
export GPG_TTY=$(tty)

# security stuff
umask 022
unset ROOTPATH

# xdg stuff
export XDG_DATA_DIRS="/usr/local/share:/usr/share"
export XDG_CONFIG_DIRS="/etc/xdg"

# from blfs book
export INFOPATH="/usr/info"
export PKG_CONFIG_PATH="/usr/lib/pkgconfig:/usr/share/pkgconfig:/usr/local/lib/pkgconfig"
export MANPATH="/usr/share/man"
export INFOPATH="/usr/share/info"
export INPUTRC="/etc/inputrc"

# xorg compiling
export XORG_PREFIX="/usr"
export XORG_CONFIG="--prefix=$XORG_PREFIX --sysconfdir=/etc --localstatedir=/var --disable-static"

### oh-my-zsh customization
ZSH_THEME="mss"
ENABLE_CORRECTION="true"
COMPLETION_WAITING_DOTS="true"
HIST_STAMPS="dd.mm.yyyy"

## plugins
plugins=(vi-mode)
source $ZSH/oh-my-zsh.sh


### aliases
## program related
alias tmux="tmux -2"
alias feh="feh -d --scale-down --auto-zoom"

## make verbose
alias ln="ln -v"
alias cp="cp -v"
alias mv="mv -v"
alias mkdir="mkdir -pv"
alias mount="mount -v"

## shortcuts
##a literal shortcuts
alias nc="ncmpcpp"
alias w="pwd"
alias l="ls -Askh --color=tty"
alias ll="ls -Askhw1 --color=tty"
alias lll="ls -la"
##b tmux
alias td="tmux detach"
alias ta="tmux attach"
alias tk="tmux kill-session"
##c sound
alias atog="amixer set Master toggle"
alias mtog="mpc toggle"
##d transmission
alias trs="transmission-remote -n mss:mss -l"
alias tra="transmission-remote -n mss:mss -a"
##e dirs
alias cda="cd /mnt/mss/stuff/media/anime"
alias cdm="cd /mnt/mss/stuff/media/music"
alias cdg="cd /mnt/mss/stuff/techy-bits/git-repositories"
alias cdw="cd /mss/work"
alias cdr="cd /mss/repo"
