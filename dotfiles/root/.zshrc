# env variables
export PATH=$PATH:$HOME/bin:/usr/local/bin:/sbin:/usr/sbin:$HOME/.local/bin
export ZSH="/root/.oh-my-zsh"
export EDITOR="vim"
export LANG="en_US.utf8"

# oh-my-zsh customization
ZSH_THEME="mss"
ZSH_DISABLE_COMPFIX="true"
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
