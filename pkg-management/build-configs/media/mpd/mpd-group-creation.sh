#!/bin/env bash
echo "[*] adding group mpd" &&
 groupadd mpd &&
echo "[*] adding user mpd"
 useradd -c "mpd thingy" -d /var/lib/mpd -u 45 -g mpd -s /bin/nologin mpd &&
echo "[*] adding user mpd to groups mss and audio"
 gpasswd -a mpd audio &&
 gpasswd -a mpd mss &&
echo "[*] creating dirs"
 mkdir /var/lib/mpd &&
 touch /var/lib/mpd/database &&
 chown -R mpd:mpd /var/lib/mpd &&
echo "[*] done"
