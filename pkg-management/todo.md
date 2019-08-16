### libre rebuilds
* [done] unzip  
https://git.parabola.nu/abslibre.git/tree/libre/unzip
* [done] ruby  
https://git.parabola.nu/abslibre.git/tree/libre/ruby
* [done] sdl  
https://git.parabola.nu/abslibre.git/tree/libre/sdl

### updates:
* util-linux (2.33.1 --> 2.34)  
http://linuxfromscratch.org/lfs/view/development/chapter06/util-linux.html
* coreutils (8.30 --> 8.31)  
http://linuxfromscratch.org/lfs/view/development/chapter06/coreutils.html
* [done] sysvinit (2.93 --> 2.95)  
http://linuxfromscratch.org/lfs/view/development/chapter06/sysvinit.html
* [done] eudev (3.2.7 --> 3.2.8)  
http://linuxfromscratch.org/lfs/view/development/chapter06/eudev.html

### security
#### software listed below must be updated:
* [done] ntp >> 4.2.8p12 --> 4.2.8p13  
https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2019-8936
* [done] libpng >> 1.6.36 --> 1.6.37  
http://www.slackware.com/security/viewer.php?l=slackware-security&y=2019&m=slackware-security.369646
* [done] openjpeg >> 2.3.0 --> 2.3.1  
http://www.slackware.com/security/viewer.php?l=slackware-security&y=2019&m=slackware-security.332670
* [done] irssi >>  1.2.0 --> 1.2.1  
https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2019-13045
* [done] bzip2 >> 1.0.6 --> 1.0.8  
http://www.slackware.com/security/viewer.php?l=slackware-security&y=2019&m=slackware-security.423144
* [done] libssh2 >> 1.8.0 --> 1.9.0  
http://www.slackware.com/security/viewer.php?l=slackware-security&y=2019&m=slackware-security.378113
* [done] gnutls >> 3.6.6 --> 3.6.9  
http://www.slackware.com/security/viewer.php?l=slackware-security&y=2019&m=slackware-security.427640
* [done] curl >> 7.64 --> 7.65.3  
http://www.slackware.com/security/viewer.php?l=slackware-security&y=2019&m=slackware-security.424586
* [done] wget >> 1.20.1 --> 1.20.3
https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2019-5953

### planned to be built/set/configured
* [d] rss reader		--> built newsboat
* [d] set up iptables		--> done
* [d] mutt			--> done, ages ago

### dbus removal garbage
#### bin and lib still linked against libdbus:
```
none, as far as i can tell.
```
#### rebuilt without dbus
```
* iftop-1.0pre4
* gtk+-3.24.5
* compton-0.1_beta2
* mpd-0.21.10
* libpcap-1.9.0
```
