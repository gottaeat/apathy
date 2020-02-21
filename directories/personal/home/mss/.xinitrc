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
setxkbmap us,tr -option 'grp:alt_shift_toggle' &

/home/mss/.fehb.def &
cp /home/mss/.fehbg /home/mss/.fehb.def &

/mss/bin/disableaccel &
/mss/bin/switchcompositor novsync &

while true; do /home/mss/.config/scripts/bw-write; done &
dwmblocks &
while true; do dwm 2> /tmp/.dwm.log; done
