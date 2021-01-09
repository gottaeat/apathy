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

/mss/bin/switchcompositor -v &

#/mss/bin/disableaccel
/home/mss/.fehbg
cp /home/mss/.fehbg /home/mss/.fehb.def

xnput --set-prop "SynPS/2 Synaptics TouchPad" \
 "Synaptics Noise Cancellation" 20 20

/home/mss/.config/scripts/statusbar x &
while :; do dwm 2>&1; done
