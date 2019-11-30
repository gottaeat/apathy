#!/bin/env bash
# read xresources
#xrdb .Xresources

# fonts
xset fp+ /usr/share/fonts/

# turn numlock on
numlockx on

# power management
xset s off
xset -dpms
xset s noblank

# wm
#exec i3
exec jwm
