#!/mss/bin/sh
# >> turn of display power management
xset s off
xset -dpms
xset s noblank

# >> turn on numlock
numlockx on

# >> start the environment
xrandr --output VGA-1 --primary &
cp /home/mss/.fehbg /home/mss/.fehb.def &
setxkbmap us,tr -option 'grp:alt_shift_toggle' &
/home/mss/.fehb.def &
#/home/mss/.config/lemonbar/main &
#/mss/bin/switchcompositor novsync &
exec cwm
