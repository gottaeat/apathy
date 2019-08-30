if [ -f "/etc/dircolors" ]; then eval $(dircolors -b /etc/dircolors); fi

alias ls='ls --color=auto'
alias grep='grep --color=auto'
