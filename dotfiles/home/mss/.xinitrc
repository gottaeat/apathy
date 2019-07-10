#!/bin/sh

#fonts
xset fp+ /usr/share/fonts/

#turn numlock on
numlockx on

#power management
xset s off
xset -dpms
xset s noblank

#dbus
#dbus-launch --sh-syntax --exit-with-session

#wm
exec i3
