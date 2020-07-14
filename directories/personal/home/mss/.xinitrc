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

/mss/bin/disableaccel
/home/mss/.fehbg
cp /home/mss/.fehbg /home/mss/.fehb.def

dwmblocks &
while true; do dwm 2> /tmp/.dwm.log; done
