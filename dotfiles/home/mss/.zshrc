# env variables
export PATH=$PATH:$HOME/bin:/usr/local/bin:/sbin:/usr/sbin:$HOME/.local/bin
export ZSH="/home/mss/.oh-my-zsh"
export EDITOR="vim"
export LANG="en_US.utf8"

# oh-my-zsh customization
ZSH_THEME="mss"
ENABLE_CORRECTION="true"
COMPLETION_WAITING_DOTS="true"
HIST_STAMPS="dd.mm.yyyy"

# plugins
plugins=(
  git
)
source $ZSH/oh-my-zsh.sh

# aliases
alias tmux="tmux -2"
alias mc="mc -b"
alias nc="ncmpcpp"
alias w="pwd"
alias cda="cd /mnt/mss/stuff/media/anime"
alias cdm="cd /mnt/mss/stuff/media/music"
alias cdg="cd /mnt/mss/stuff/techy-bits/git-repositories"
alias chxg="sudo /usr/local/bin/chx -p /usr/bin/gimp -d /mnt/dev/gentoo -u mss"
alias chxs="sudo /usr/local/bin/chx -p /usr/bin/steam -d /mnt/dev/gentoo -u mss"
alias chxz="sudo /usr/local/bin/chx -p "/bin/zsh" -d /mnt/dev/gentoo -u mss"
alias feh="feh --scale-down --auto-zoom"
