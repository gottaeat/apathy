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

/home/mss/.fehbg &
cp /home/mss/.fehbg /home/mss/.fehb.def &

/mss/bin/disableaccel &
#/mss/bin/switchcompositor &

while true; do /home/mss/.config/scripts/bw-write; done &
dwmblocks &
#oneko -neko -time 100000 -speed 30 -bg white -fg black &
while true; do dwm 2> /tmp/.dwm.log; done
