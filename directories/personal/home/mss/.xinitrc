#!/mss/bin/sh
# >> turn of display power management
xset s off
xset -dpms
xset s noblank

# >> turn on numlock
numlockx on

# >> start the environment
xrandr --auto --output LVDS-1 --primary
xrandr --auto --output VGA-1  --right-of LVDS-1

xkbcomp -w 0 xkbmap $DISPLAY
xset r rate 280 40

/mss/bin/switchcompositor -v

/home/mss/.fehbg
cp /home/mss/.fehbg /home/mss/.fehb.def

/home/mss/.config/scripts/statusbar x &
#while :; do xsetroot -name "$(date '+%a %d %H:%M:%S')"; sleep 1;  done &
while :; do dwm 2>&1; done
