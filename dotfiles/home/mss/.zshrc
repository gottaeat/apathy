### env variables
export ZSH="/home/mss/.oh-my-zsh"

# path and lang
export PATH="/opt/rustc/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/opt/bin:/mss/bin"
export LANG="en_US.utf8"

# stuff taken from gentoo
export GCC_SPECS=""
export LESS="-R -M --shift 5"
export OPENGL_PROFILE="xorg-x11"
export GSETTINGS_BACKEND="dconf"

# compile bits
export MAKEFLAGS="-j 3"

# default programs
export EDITOR="/usr/bin/vim"
export PAGER="/usr/bin/less"
export GPG_TTY=$(tty)

# xdg stuff
export XDG_DATA_DIRS="/usr/local/share:/usr/share"
export XDG_CONFIG_DIRS="/etc/xdg"

# from blfs book
export INFOPATH="/usr/info"
export PKG_CONFIG_PATH="/usr/lib/pkgconfig:/usr/share/pkgconfig:/usr/local/lib/pkgconfig"
export MANPATH="/usr/share/man"
export INFOPATH="/usr/share/info"
export INPUTRC="/etc/inputrc"


### oh-my-zsh customization
ZSH_THEME="mss"
ENABLE_CORRECTION="true"
COMPLETION_WAITING_DOTS="true"
HIST_STAMPS="dd.mm.yyyy"

## plugins
plugins=(git vi-mode)
source $ZSH/oh-my-zsh.sh


### aliases
# program related
alias tmux="tmux -2"
alias feh="feh --scale-down --auto-zoom"

# make verbose
alias ln="ln -v"
alias cp="cp -v"
alias mv="mv -v"
alias mkdir="mkdir -pv"
alias mount="mount -v"

# shortcuts
alias nc="ncmpcpp"
alias w="pwd"
alias cda="cd /mnt/mss/stuff/media/anime"
alias cdm="cd /mnt/mss/stuff/media/music"
alias cdg="cd /mnt/mss/stuff/techy-bits/git-repositories"
