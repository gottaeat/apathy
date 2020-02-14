#!/bin/sh
# create the mpd grou and user
groupadd mpd
useradd -c "mpd thingy" -d /var/lib/mpd -u 45 -g mpd -s /bin/nologin mpd

# add mpd to the audio group
gpasswd -a mpd audio

# create essential directories and hand over the ownership
mkdir /var/lib/mpd
touch /var/lib/mpd/database
chown -R mpd:mpd /var/lib/mpd

# `/etc/init.d/mpd start` won't be working, run mpd with:
doas -u mpd mpd /etc/mpd.conf

# once it errors out, do:
doas -- chown -R mpd:mpd /var/lib/mpd/log

# now `/etc/init.d/mpd start` will work properly.
